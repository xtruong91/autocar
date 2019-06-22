/*
 * File: MessageHandler.cpp
 * File Created: Thursday, 20th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */

#include "MessageHandler.h"
#include "Arduino.h"
void 
MessageHandler::registerObs(IMessageObserver* obs)
{

}

void 
MessageHandler::unregisterObs(IMessageObserver* obs)
{

}

// Monitor data from RX UART
void 
MessageHandler::rcvRawData(RingBuffer &buffer)
{
    for(RingBuffer::Iterator it = buffer.begin(); it != buffer.end(); ++it)
    {
        Serial.print(*it);
    }

    Serial.println();
    char rawData;
    while(buffer.pop(&rawData) >= 0)
    {
        Serial.print(rawData);
    }
    //Serial.print(data);
    // Parse message here!
}

void
MessageHandler::notify()
{

}