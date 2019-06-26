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
    mqtttClientConfig.ssid          = ssid;
    mqtttClientConfig.password      = password;
    mqtttClientConfig.MQTTServer    = MQTTServer;
    mqtttClientConfig.MQTTPort      = MQTTPort;

    uartConfig.uartPort             = uartPort;
    uartConfig.baudrate             = uartBaudRate;

    webServiceConfig.ssid       = ssid;
    webServiceConfig.password   = password;

    webServiceConfig.ssidAP     = ssidAP;
    webServiceConfig.passwordAP = passwordAP;

    webServiceConfig.OTAName    = OTAName;
    webServiceConfig.OTAPassword = OTAPassword;

    webServiceConfig.mdnsName       = mdnsName;
    webServiceConfig.WebServerPort  = WebServerPort;
    webServiceConfig.WebClientPort  = WebClientPort;
}
