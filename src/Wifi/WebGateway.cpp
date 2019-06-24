/*
 * File: WebGateway.cpp
 * File Created: Monday, 24th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "WebGateway.h"

WebGateway *WebGateway::m_instance = NULL;

WebGateway*
WebGateway::instance(const WebGatewayConfig& config)
{
    if(m_instance == NULL)
    {
        m_instance = new WebGateway(config);
    }
    return webGateway;
}


WebGateway::WebGateway(const WebGatewayConfig& config)
   : m_config(config),
    m_webSocket(m_config.WebSocketPort),
    m_server(m_config.WebServerPort)
{
    
    
}

RetVal 
WebGateway::init()
{
    // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
    startWifi();

    // Start the OTA service
    startOTA();

    // Start the SPIFFS and list all contents
    startSPIFFS();

    // Start a WebSocket server
    startWebSocket();

    // Start the mDNS responder
    startServer();

     // Start a HTTP server with a file read handler and an upload handler
    startServer(); 
}

RetVal 
WebGateway::run()
{
    // constantly check for websocket events
    m_webSocket.loop();

    // run the server
    m_server.handleClient();

    // listen for OTA events
    ArduinoOTA.handle();


}


/**
 * Start a wifi access point,  and try to connect to some given access point
 * Then wait for either an AP or STA connection;
*/
void 
WebGateway::startWifi()
{
    WiFi.softAP(m_config.ssid, m_config.password);

    m_wifiMulti.addAP(m_config.ssidAP.c_str(), m_config.passwordAP.c_str());

    while (m_wifiMulti.run() != WL_CONNECTED && 
                WiFi.softAPgetStationNum() < 1) 
    {  // Wait for the Wi-Fi to connect
        delay(250);
        //Serial.print('.');
    }
}
/**
 * Start the OTA service
*/
void 
WebGateway::startOTA()
{
    ArduinoOTA.setHostname(m_config.OTAName.c_str());
    ArduinoOTA.setPassword(m_config.OTAPassword.c_str());

    ArduinoOTA.onStart([]() 
    {
        Serial.println("Start");
        // digitalWrite(LED_RED, 0);    // turn off the LEDs
        // digitalWrite(LED_GREEN, 0);
        // digitalWrite(LED_BLUE, 0);
    });

    ArduinoOTA.onEnd([]() 
    {
        Serial.println("\r\nEnd");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) 
    {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });

    ArduinoOTA.onError([](ota_error_t error) 
    {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

    ArduinoOTA.begin();
}
/**
 * Start the SPIFFS and list all contents
*/
void 
WebGateway::startSPIFFS()
{
    SPIFFS.begin(); // Start the SPI Flash File System (SPIFFS)
    Serial.println("SPIFFS started. Contents:");
    {
        Dir dir = SPIFFS.openDir("/");
        while (dir.next()) 
        {                      // List the file system contents
            String fileName = dir.fileName();
            size_t fileSize = dir.fileSize();
            //Serial.printf("\tFS File: %s, size: %s\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
        }
        Serial.printf("\n");
    }
}
/**
 * Start a websocket server
*/
void 
WebGateway::startWebSocket()
{
    m_webSocket.begin();  // start the websocket server
    m_webSocket.onEvent(onWebSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
    Serial.println("WebSocket server started.");
}
/**
 * Start the mDNS responder;
*/
void 
WebGateway::startMDNS()
{
    MDNS.begin(m_config.mdnsName);                        // start the multicast domain name server
    Serial.print("mDNS responder started: http://");
    Serial.print(m_config.mdnsName);
    Serial.println(".local");
}

/**
 * Start a HTTP Server with a file read handler and upload handler
*/
void 
WebGateway::startServer()
{
    m_server.on("/edit.html",  HTTP_POST, onSendOK, onHandleFileUpload);                       // go to 'handleFileUpload'

    m_server.onNotFound(onHandleNotFound);          // if someone requests any other file or page, go to function 'handleNotFound'
                                                // and check if the file exists
    m_server.begin();                             // start the HTTP server
    Serial.println("HTTP server started.");
}

void 
WebGateway::onSendOK()
{
   webGateway->m_server.send(200, "text/plain", ""); 
}

void 
WebGateway::onHandleNotFound()
{
    if(!onHandleFileRead(webGateway->m_server.uri()))
    {          // check if the file exists in the flash memory (SPIFFS), if so, send it
        webGateway->m_server.send(404, "text/plain", "404: File Not Found");
    }
}

bool 
WebGateway::onHandleFileRead(String path)
{
    Serial.println("handleFileRead: " + path);
    if (path.endsWith("/")) path += "index.html";          // If a folder is requested, send the index file
    
    String contentType = getContentType(path);             // Get the MIME type
    String pathWithGz = path + ".gz";
    
    if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) 
    { // If the file exists, either as a compressed archive, or normal
    
        if (SPIFFS.exists(pathWithGz))                         // If there's a compressed version available
            path += ".gz";                                         // Use the compressed verion
        
        File file = SPIFFS.open(path, "r");                    // Open the file
        size_t sent = webGateway->m_server.streamFile(file, contentType);    // Send it to the client
        
        file.close();                                          // Close the file again
        
        Serial.println(String("\tSent file: ") + path);
        
        return true;
    }

    Serial.println(String("\tFile Not Found: ") + path);   // If the file doesn't exist, return false
    
    return false;
}

void 
WebGateway::onHandleFileUpload()
{
    HTTPUpload& upload = webGateway->m_server.upload();
    String path;

    if(upload.status == UPLOAD_FILE_START)
    {
        path = upload.filename;

        if(!path.startsWith("/")) path = "/"+path;
        
        if(!path.endsWith(".gz")) 
        {                          // The file server always prefers a compressed version of a file 
            String pathWithGz = path+".gz";                    // So if an uploaded file is not compressed, the existing compressed
            
            if(SPIFFS.exists(pathWithGz))                      // version of that file must be deleted (if it exists)
                SPIFFS.remove(pathWithGz);
        }

        Serial.print("handleFileUpload Name: "); Serial.println(path);
    
        webGateway->fsUploadFile = SPIFFS.open(path, "w");            // Open the file for writing in SPIFFS (create if it doesn't exist)
        
        path = String();
    } 
    else if(upload.status == UPLOAD_FILE_WRITE)
    {
        if(webGateway->fsUploadFile)
            webGateway->fsUploadFile.write(upload.buf, upload.currentSize); // Write the received bytes to the file
    } 
    else if(upload.status == UPLOAD_FILE_END)
    {
        if(webGateway->fsUploadFile) 
        {                                    // If the file was successfully created
            webGateway->fsUploadFile.close();                               // Close the file again
            Serial.print("handleFileUpload Size: "); 
            Serial.println(upload.totalSize);
            webGateway->m_server.sendHeader("Location","/success.html");      // Redirect the client to the success page
            webGateway->m_server.send(303);
        } else 
        {
            webGateway->m_server.send(500, "text/plain", "500: couldn't create file");
        }
    }
}

void 
WebGateway::onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght)
{
    switch (type) 
    {
    case WStype_DISCONNECTED:             // if the websocket is disconnected
        Serial.printf("[%u] Disconnected!\n", num);
        break;
    case WStype_CONNECTED: 
    {              // if a new websocket connection is established
        IPAddress ip = webGateway->m_webSocket.remoteIP(num);
        //Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        //rainbow = false;                  // Turn rainbow off when a new connection is established
    }
        break;
    case WStype_TEXT:                     // if new text data is received
        Serial.printf("[%u] get Text: %s\n", num, payload);
        if (payload[0] == '#') 
        {            // we get RGB data
            uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);   // decode rgb data
            int r = ((rgb >> 20) & 0x3FF);                     // 10 bits per color, so R: bits 20-29
            int g = ((rgb >> 10) & 0x3FF);                     // G: bits 10-19
            int b =          rgb & 0x3FF;                      // B: bits  0-9

            // analogWrite(LED_RED,   r);                         // write it to the LED output pins
            // analogWrite(LED_GREEN, g);
            // analogWrite(LED_BLUE,  b);
        } 
        else if (payload[0] == 'R') 
        {                      // the browser sends an R when the rainbow effect is enabled
            //rainbow = true;
        } else if (payload[0] == 'N') 
        {                      // the browser sends an N when the rainbow effect is disabled
            //rainbow = false;
        }
        break;
    }
}

String 
WebGateway::formatBytes(size_t bytes)
{
    if (bytes < 1024) 
    {
        return String(bytes) + "B";
    } 
    else if (bytes < (1024 * 1024)) 
    {
        return String(bytes / 1024.0) + "KB";
    } else if (bytes < (1024 * 1024 * 1024)) 
    {
        return String(bytes / 1024.0 / 1024.0) + "MB";
    }
}

String 
WebGateway::getContentType(String filename)
{
    if (filename.endsWith(".html")) return "text/html";
    else if (filename.endsWith(".css")) return "text/css";
    else if (filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".ico")) return "image/x-icon";
    else if (filename.endsWith(".gz")) return "application/x-gzip";
    return "text/plain";
}

void 
WebGateway::setHue(int hue)
{
    hue %= 360;                   // hue is an angle between 0 and 359°
    float radH = hue*3.142/180;   // Convert degrees to radians
    float rf, gf, bf;

    if(hue>=0 && hue<120)
    {        // Convert from HSI color space to RGB              
        rf = cos(radH*3/4);
        gf = sin(radH*3/4);
        bf = 0;
    } 
    else if(hue>=120 && hue<240)
    {
        radH -= 2.09439;
        gf = cos(radH*3/4);
        bf = sin(radH*3/4);
        rf = 0;
    } else if(hue>=240 && hue<360)
    {
        radH -= 4.188787;
        bf = cos(radH*3/4);
        rf = sin(radH*3/4);
        gf = 0;
    }
    int r = rf*rf*1023;
    int g = gf*gf*1023;
    int b = bf*bf*1023;

    // analogWrite(LED_RED,   r);    // Write the right color to the LED output pins
    // analogWrite(LED_GREEN, g);
    // analogWrite(LED_BLUE,  b);
}