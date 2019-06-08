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
#ifndef DEBUG_H
#define DEBUG_H

#include "Arduino.h"
#include "UART.h"


class Debug 
{
public:
    Debug(UART* uart);
    void Init();
    int Printf(const char* format, ...);
private:
    UART* puart;    
};

#endif