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

    unsigned int WebServerPort;
};

class WebGateway
{
public:
    WebGateway(const WebGatewayConfig& config);
    RetVal init();
    RetVal run();

private:
    WebGatewayConfig m_config;

    ESP8266WiFiMulti m_wifiMulti;

    ESP8266WebServer m_server;
    WebSocketsServer m_webSocket;
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

};

#endif