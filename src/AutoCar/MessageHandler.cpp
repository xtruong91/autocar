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

MessageHandler::MessageHandler()
    : m_pMessage(NULL)
{

}

void 
MessageHandler::registerObs(IMessageObserver* obs)
{
    m_pMsgObservers.push_back(obs);
}

void 
MessageHandler::unregisterObs(IMessageObserver* obs)
{
    // TODO;
}

// Monitor data from RX UART
void 
MessageHandler::rcvRawData(RingBuffer &buffer)
{
    // Parser message then notify;
#ifdef DEBUG    
    for(RingBuffer::Iterator it = buffer.begin(); it != buffer.end(); ++it)
    {
        Serial.print(*it);
    }
#endif
    m_pMessage = m_msgParser.parse(buffer);
    if(m_pMessage != NULL)
    {
        notify();
    }
    // Parse message here!
}

void
MessageHandler::notify()
{
    // publisher broadcasts
    for(int i = 0; i < m_pMsgObservers.size(); i++)
    {
        m_pMsgObservers[i]->rcvMessage(*m_pMessage);
    }
}