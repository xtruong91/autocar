/*
 * File: ES8266.h
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef ESP8266_H
#define ESP8266_H

#include "UART.h"
#include "IRecvUartData.h"

class ESP8266 : public IObserverRxData
{
public:
    ESP8266(UART* uartSubject);
    void Send(const char* buffer, int length);
    void Update(char *buffer, int length);
private:
    UART *pSubject;    
};

#endif