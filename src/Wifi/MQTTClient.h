/*
 * File: MQTTClient.h
 * File Created: Sunday, 23rd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: subscribe/ publish message upon the server
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _MQTT_CLIENT_H_
#define _MQTT_CLIENT_H_

#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#include "RingBuffer.h"
#include "IMessageObserver.h"
#include "Utils.h"
#include "JsonParser.h"

struct MQTTClientConfig
{
    String ssid; // wifi identity
    String password; 
    String MQTTServer;
    unsigned int MQTTPort;
};

class MQTTClient
{
public:
    static MQTTClient *instance();
    virtual ~MQTTClient();
    RetVal init(const MQTTClientConfig& config);
    RetVal run();
    RetVal stop();

    void addSubscribe(const char* topic);
    void removeSubscribe(const char* topic);

    // set/remove observer MQTT Client;
    void setObserver(IMessageObserver* obs);
    void removeObserver();
 
private:
    RingBuffer m_RingBuffer;
    void notify();
    bool reconnect();
    static void onRcvCallback(char *topic, byte* payload, unsigned int lenght);
    WiFiClient *m_pWifiClient;
    PubSubClient *m_pMqttClient;
    IMessageObserver *m_pMessageObserver;
    JsonParser *m_pJsonParser;   
private:
    static MQTTClient *m_instance;
    MQTTClient();    
};

#endif