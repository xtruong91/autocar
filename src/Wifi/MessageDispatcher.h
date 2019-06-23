/*
 * File: MessageDispatcher.h
 * File Created: Saturday, 22nd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _MESSAGE_DISPATCHER_H_
#define _MESSAGE_DISPATCHER_H_

#include "IRxByteObserver.h"
#include "MQTTClient.h"
#include "WifiConfig.h"

class MessageDispatcher : public IRxByteObserver
{
public:
    MessageDispatcher();

    RetVal init();
    RetVal run();
    RetVal stop();
    // inherite from RxByteObserver;
    virtual void update(RingBuffer& buffer);

private:
    MQTTClient *m_pMQTTClient;
    WifiConfig *m_pWifiConfig;
    UART* m_pUART;
};

#endif