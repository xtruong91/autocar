/*
 * File: MessageObserver.h
 * File Created: Sunday, 9th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _IMESSAGE_OBSERVER_H_
#define _IMESSAGE_OBSERVER_H_

#include "Message.h"

struct IMessageObserver
{
    virtual void rcvMessage(Message& msg) = 0;
    virtual void onDisconnect() = 0;
};

#endif