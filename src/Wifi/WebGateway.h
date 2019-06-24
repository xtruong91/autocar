/*
 * File: WebGateway.h
 * File Created: Sunday, 23rd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _WEB_GATEWAY_H_
#define _WEB_GATEWAY_H_

#include "Utils.h"
#include "Arduino.h"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <WebSocketsServer.h>

struct WebGatewayConfig
{
    String ssid;
    String password;

    String ssidAP;
    String passwordAP;

    String OTAName; // A name and a password for the OTA service
    String OTAPassword;

    String mdnsName; // Domain name for the mDNS responder

    unsigned int WebServerPort;
    unsigned int WebSocketPort;
};

class WebGateway
{
public:
    static WebGateway *instance(const WebGatewayConfig& config);
    RetVal init();
    RetVal run();

private:
    WebGateway(const WebGatewayConfig& config);
    static WebGateway *m_instance;

    WebGatewayConfig m_config;

    ESP8266WiFiMulti m_wifiMulti;

    ESP8266WebServer m_server; // create a web sever on port 80
    WebSocketsServer m_webSocket; // create a web socket server on port 81
    File fsUploadFile; 
private:
    /**
     * Start a wifi access point,  and try to connect to some given access point
     * Then wait for either an AP or STA connection;
    */
    void startWifi();
    /**
     * Start the OTA service
    */
    void startOTA();
    /**
     * Start the SPIFFS and list all contents
    */
    void startSPIFFS();
    /**
     * Start a websocket server
    */
    void startWebSocket();
    /**
     * Start the mDNS responder;
    */
    void startMDNS();

    /**
     * Start a HTTP Server with a file read handler and upload handler
    */
    void startServer();

    /**
     * if the requested file or page doesn't exist, return a 404 not found error
     * 
    */
    static void onHandleNotFound();

    /**
     * send the right file to the client (if it exists)
     * */
    static bool onHandleFileRead(String path);

    /**
     *  upload a new file to the SPIFFS
     * 
    */
    static void onHandleFileUpload();

    /**
     * When a WebSocket message is received
    */
    static void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght);

    /**
     * convert sizes in bytes to KB and MB
    */
    static String formatBytes(size_t bytes);

    /**
     * determine the filetype of a given filename, based on the extension
    */
    static String getContentType(String filename);
    /**
     *  Set the RGB LED to a given hue (color) (0° = Red, 120° = Green, 240° = Blue)
    */
    static void setHue(int hue);

    static void onSendOK();

};

// !!! Important. have to declare here. 
WebGateway *webGateway;

#endif