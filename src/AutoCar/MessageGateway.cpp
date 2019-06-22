/*
 * File: MessageGateway.cpp
 * File Created: Saturday, 22nd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "MessageGateway.h"

MessageGateway* 
MessageGateway::m_instance = NULL;

MessageGateway*
MessageGateway::instance()
{
    if(m_instance == NULL)
    {
        m_instance = new MessageGateway();
    }
    return m_instance;
}

RetVal 
MessageGateway::init()
{
    m_pUart = UART::instance();
    m_pMsgHandler = new MessageHandler();
    // attach
    m_pUart->registerRxObs(m_pMsgHandler);
    
    return RET_SUCCESS;
}


RetVal 
MessageGateway::stop()
{
    if(m_pUart != NULL)
        delete m_pUart;

    if(m_pMsgHandler != NULL)
        delete m_pUart;
    
}