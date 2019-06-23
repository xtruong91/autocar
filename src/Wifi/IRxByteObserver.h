/*
 * File: IRxByteObserver.h
 * File Created: Saturday, 22nd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: Interface for supporting received data from arduino module
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _IRX_BYTE_OBSERVER_H_
#define _IRX_BYTE_OBSERVER_H_

#include "RingBuffer.h"

struct IRxByteObserver
{
    virtual void update(RingBuffer& buffer) = 0;
};


#endif
