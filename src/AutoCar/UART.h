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

#ifndef _UART_H_
#define _UART_H_

#include  "Vector.h"
#include  "IRxUartObserver.h"
#include "RingBuffer.h"
#include "Utils.h"

#define BAURATE     9600

struct UartConfig
{
    int baudrate;
    int bufferLength;
    String portname;
};

class UART
{

public:
    static UART *instance();
    
    RetVal init(UartConfig &config);
    int send(const char* data, int length);

    void registerRxObs(IRxUartObserver *obs);
    void unregisterRxObs(IRxUartObserver *obs);
    void notify();
    /**
     * Push data into buffer
     * 
    */
    static RingBuffer m_rbBuffer;
private:        
    UART(){};
    Vector<IRxUartObserver*> m_pRxObservers;
    static UART *inst;

};

#endif