/*
 * File: Debug.cpp
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */

#include "Debug.h"

Debug::Debug(UART *uart)
{
    puart = uart;
}

void Debug::Init()
{
    puart->Init();
    Serial.println("-------------------------");
    Serial.println("Debug is loading....");
}


int Debug::Printf(const char* format, ...)
{
    va_list arg;
    va_start(arg, format);
    char temp[100];
    char* buffer = temp;
    size_t len = vsprintf(temp, format, arg);
    va_end(arg);
    int index;
    for(index = 0; index < len; index++)
    {
        Serial.print(buffer[index]);
    }
    return len;
}

