/*
 * File: Debug.h
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "Arduino.h"


class Debug 
{
public:
    void init();
    int printf(const char* format, ...);  
};

#endif