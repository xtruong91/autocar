/*
 * File: WifiConfig.h
 * File Created: Sunday, 23rd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _WIFI_CONFIG_H_
#define _WIFI_CONFIG_H_

#include "MQTTClient.h"
#include "UART.h"
#include "WebService.h"

static const char* ssid          = "IoT";
static const char* password      = "123456a@";
static const char* MQTTServer    = "broker.mqtt-dashboard.com";
static unsigned int MQTTPort     = 1883;

static unsigned int uartPort    = 0;
static unsigned int uartBaudRate = 115200;

static const char* OTAName            = "ESP8266";
static const char* OTAPassword        = "esp8266";

static const char* mdnsName           = "esp8266";

static const unsigned int WebServerPort = 80;
static const unsigned int WebClientPort = 81;

static const char *ssidAP = "XT";
static const char *passwordAP = ""; // must define empty;


class WifiConfig
{
public:
    static WifiConfig *instance();
    // MQTT Setting 
    MQTTClientConfig mqtttClientConfig;
    // uart setting
    UARTConfig uartConfig;
    // setting for web service;
    WebServiceConfig webServiceConfig;

private:
    WifiConfig();    
    static WifiConfig *m_instance;
};

#endif
