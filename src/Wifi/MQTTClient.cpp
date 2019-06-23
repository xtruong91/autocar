/*
 * File: MQTTClient.cpp
 * File Created: Sunday, 23rd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "MQTTClient.h"

MQTTClient* MQTTClient::m_instance = NULL;

MQTTClient* 
MQTTClient::instance()
{
    if(m_instance == NULL)
    {
        m_instance = new MQTTClient();
    }
    return m_instance;
}

MQTTClient::MQTTClient() 
    : m_pMessageObserver(NULL),
     m_pMqttClient(NULL),
     m_pWifiClient(NULL),
     m_pJsonParser(NULL)
{
    m_pWifiClient = new WiFiClient ();
    m_pMqttClient = new PubSubClient();
    m_pMqttClient->setClient(*m_pWifiClient);
}

MQTTClient::~MQTTClient()
{
    if(m_pMqttClient != NULL)
        delete m_pMqttClient;
    
    if(m_pWifiClient != NULL)
        delete m_pWifiClient;    
}

RetVal 
MQTTClient::init(const MQTTClientConfig& config)
{
    WiFi.begin(config.ssid.c_str());
    while (WiFi.status() != WL_CONNECTED);

    m_pMqttClient->setServer(config.MQTTServer.c_str(), config.MQTTPort);
    m_pMqttClient->setCallback(onRcvCallback);
}

void 
MQTTClient::onRcvCallback(char *topic, byte* payload, unsigned int length)
{
    if(m_instance == NULL)
        return;   
    // Parser json data;

    //m_instance->m_RingBuffer.push(payload, lenght);
}

RetVal 
MQTTClient::run()
{
    if(!m_pMqttClient->loop())
    {
        reconnect();
        return RET_FAIL;
    }
    else
    {
        return RET_SUCCESS;
    }
    
}

RetVal 
MQTTClient::stop()
{

}

void 
MQTTClient::addSubscribe(const char* topic)
{
    m_pMqttClient->subscribe(topic);
}

void 
MQTTClient::removeSubscribe(const char* topic)
{
     m_pMqttClient->unsubscribe(topic);
}

// set/remove observer MQTT Client;
void 
MQTTClient::setObserver(IMessageObserver* obs)
{
    if(m_pMessageObserver != NULL)
        delete m_pMessageObserver;

    m_pMessageObserver = obs;
}

void 
MQTTClient::removeObserver()
{
    if(m_pMessageObserver != NULL)
        delete m_pMessageObserver;
    m_pMessageObserver = NULL;
}

void 
MQTTClient::notify()
{

}

bool
MQTTClient::reconnect()
{
    while(!m_pMqttClient->connected())
    {
        // Create a random client ID
        String clientId = "MQTTCient-";
        clientId += String(random(0xffff), HEX);
        if(m_pMqttClient->connect(clientId.c_str()))
        {
            return true;
        }
    }
}