/*
 * File: ES8266.h
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: send/received to ESP8266 module
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _ESP8266_H_
#define _ESP8266_H_

#include "IMessageObserver.h"

class ESP8266 : public IMessageObserver
{
public:
    int send(const char*buffer, unsigned int length);
    // Inherite from MesageObserver interface;
    virtual void rcvMessage(Message& msg);
    virtual void onDisconnect();  
};

#endif