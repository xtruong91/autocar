/*
 * File: WifiConfig.cpp
 * File Created: Sunday, 23rd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "WifiConfig.h"

WifiConfig* WifiConfig::m_instance = NULL;

WifiConfig*
WifiConfig::instance()
{
    if(m_instance == NULL)
        m_instance = new WifiConfig();
    return m_instance;
}


WifiConfig::WifiConfig()
{
    mqtttClientConfig.ssid = ssid;
    mqtttClientConfig.password = password;
    mqtttClientConfig.MQTTServer = mqtt_server;
    mqtttClientConfig.MQTTPort = mqtt_port;

    uartConfig.uartPort = uartPort;
    uartConfig.baudrate = baudrate;
}

MQTTClientConfig 
WifiConfig::getMQTTClientConfig() const
{
    return mqtttClientConfig;
}

UARTConfig       
WifiConfig::getUARTConfig() const
{
   return uartConfig;
}