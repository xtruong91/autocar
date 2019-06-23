/*
 * File: IMessageObserver.h
 * File Created: Sunday, 23rd June 2019
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
    virtual void update(Message& msg) = 0;
};

#endif