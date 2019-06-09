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

#include "IRecvUartData.h"
#include  "Vector.h"

#define BAURATE     9600
#define BUFF_LENGTH 100

typedef void (*CallBackRX)(char *buffer, int length);

class UART : public IRecvUartData
{
public:
    static UART *Instance();
    void Init();
    int Send(const char* data, int length);
    static void Attach(CallBackRX subscribeRX);

    friend void serialEvent();
    void RegisterOb(IObserverRxData* ob);
    void NotifyOb(char *data, int length);
public:
    static CallBackRX cbReceiveData;
    static bool RXComplete;  // whether the string is complete
private:
    UART(){};
    Vector<IObserverRxData*> observers;
    static UART *inst;
};

#endif