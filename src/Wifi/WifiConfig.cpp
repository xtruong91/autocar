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
    {
        m_instance = new WifiConfig();
    }
    return m_instance;
}


WifiConfig::WifiConfig()
{
    mqtttClientConfig.ssid          = "...";
    mqtttClientConfig.password      = "...";
    mqtttClientConfig.MQTTServer    = "broker.mqtt-dashboard.com";
    mqtttClientConfig.MQTTPort      = 1883;

    uartConfig.uartPort             = 0;
    uartConfig.baudrate             = 115200;
}

