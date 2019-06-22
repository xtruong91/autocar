/*
 * File: MessageGateway.h
 * File Created: Saturday, 22nd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _MESSAGE_GATEWAY_H_
#define _MESSAGE_GATEWAY_H_

#include "UART.h"
#include "MessageHandler.h"

class MessageGateway
{
public:
    static MessageGateway *instance();
    
    RetVal init();
    RetVal stop();
private:
    UART *m_pUart;
    MessageHandler *m_pMsgHandler;

    MessageGateway(){};
    static MessageGateway* m_instance;

};

#endif