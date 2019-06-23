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

static const char* ssid = "....";
static const char* password = "...";
static const char* mqtt_server = "broker.mqtt-dashboard.com";
static const unsigned mqtt_port = 1833;
static const unsigned char uartPort = 0;
static const unsigned char baudrate = 115200;

class WifiConfig
{
public:
    static WifiConfig *instance();
    
    MQTTClientConfig getMQTTClientConfig() const;
    UARTConfig       getUARTConfig() const;
private:
    MQTTClientConfig mqtttClientConfig;
    UARTConfig uartConfig;
    explicit WifiConfig();
    static WifiConfig *m_instance;
};

#endif