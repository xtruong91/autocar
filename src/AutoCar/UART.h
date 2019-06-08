/*
 * File: UART.h
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */

#ifndef UART_H
#define UART_H

#define BAURATE     9600

typedef void (*CallBackRX)(char *buffer, int length);

class UART
{
public:
    void Init();
    int Send(const char* data, int length);
    static void Attach(CallBackRX subscribeRX);
public:
    static CallBackRX cbReceiveData;
    static bool RXComplete;  // whether the string is complete    
};

#endif