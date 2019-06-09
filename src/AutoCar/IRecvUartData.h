/*
 * File: IRecvUartData.h
 * File Created: Sunday, 9th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: the data subject, when receving event occurred it notify to all subscribe; 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef RCV_UART_DATA_H
#define RCV_UART_DATA_H

#include "IObserverRxData.h"

class IRecvUartData
{
public:
    virtual void RegisterOb(IObserverRxData* ob) = 0;
    // length
    virtual void NotifyOb(char *data, int length) = 0;
};

#endif