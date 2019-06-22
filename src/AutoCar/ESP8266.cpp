/*
 * File: ESP8266.cpp
 * File Created: Sunday, 9th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "ESP8266.h"
#include "Arduino.h"

int 
ESP8266::send(const char* buffer, unsigned int length)
{
    if(buffer == NULL || length == 0)
        return;
    return Serial.write(buffer, length);
}

void 
ESP8266::rcvMessage(Message& msg)
{
    // only handle with message code is ESP8266;
}

void 
ESP8266::onDisconnect()
{

}
