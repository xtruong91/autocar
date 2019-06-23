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

class WifiConfig
{
public:
    static WifiConfig *instance();

    MQTTClientConfig mqtttClientConfig;
    UARTConfig uartConfig;

private:
    WifiConfig();    
    static WifiConfig *m_instance;
};

#endif