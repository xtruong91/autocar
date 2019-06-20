/*
 * File: IRxUartObserver.h
 * File Created: Sunday, 9th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */

#ifndef _IRX_UART_OBSERVER_H_
#define _IRX_UART_OBSERVER_H_

#include "RingBuffer.h"

struct IRxUartObserver
{
    virtual void rcvRawData(RingBuffer &ringBuffer) = 0;
};

#endif