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

WebGateway::WebGateway(const WebGatewayConfig& config)
   : m_config(config),
    m_webSocket(m_config.WebServerPort)
{
    
    
}

RetVal 
WebGateway::init()
{

}

RetVal 
WebGateway::run()
{

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

}
/**
 * Start the mDNS responder;
*/
void 
WebGateway::startMDNS()
{

}

/**
 * Start a HTTP Server with a file read handler and upload handler
*/
void 
WebGateway::startServer()
{

}