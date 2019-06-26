/*
 * File: MessageDispatcher.cpp
 * File Created: Sunday, 23rd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "MessageDispatcher.h"

#define DEBUG

WebService *webService = NULL;

MessageDispatcher::MessageDispatcher()
    :m_pMQTTClient(NULL),
    m_pWifiConfig(NULL),
    m_pUART(NULL)
{    
    m_pMQTTClient = MQTTClient::instance();
    m_pWifiConfig = WifiConfig::instance();
    m_pUART = new UART();
}

RetVal 
MessageDispatcher::init()
{
    // initialize for UART and establish observer.
    m_pUART->init(m_pWifiConfig->uartConfig);
    m_pUART->setObserver(this);

    m_pMQTTClient->init(m_pWifiConfig->mqtttClientConfig);
   
    // run webservice;
    webService = WebService::instance(m_pWifiConfig->webServiceConfig);
    webService->init();
}

RetVal 
MessageDispatcher::run()
{
    m_pUART->run();
    
    RetVal ret =  m_pMQTTClient->run();
    m_pMQTTClient->addSubscribe("xuantruong/test");
    
    webService->run();
    return ret;    
}

void
MessageDispatcher::update(RingBuffer& buffer)
{
    char data;
    while(buffer.pop(&data) >= 0)
    {
        Serial.print(data);
    }

}
