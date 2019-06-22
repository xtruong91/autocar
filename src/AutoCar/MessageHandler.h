/*
 * File: MessageHandler.h
 * File Created: Wednesday, 19th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _MESSAGE_HANDLER_H_
#define _MESSAGE_HANDLER_H_

#include "MessageParser.h"
#include "IMessageObserver.h"
#include "IRxByteObserver.h"
#include "Vector.h"

class MessageHandler : public IRxByteObserver
{
public:
    void registerObs(IMessageObserver* obs);
    void unregisterObs(IMessageObserver* obs);

    // Monitor data from RX UART
    void rcvRawData(RingBuffer &buffer);

private:
    void notify(); 
    Vector<IMessageObserver*> m_pMsgObservers;
    Message m_message;
    //MessageParser m_msgParser;

};

#endif