/*
 * File: UART.h
 * File Created: Saturday, 22nd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: Handle received data from UART base on interrupt routine
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _UART_H_
#define _UART_H_

#include "IRxByteObserver.h"
#include "RingBuffer.h"

struct UARTConfig
{
    unsigned int uartPort;
    unsigned int baudrate;
};

class UART
{
public:
    void init(const UARTConfig& config);
    void run();
    void setObserver(IRxByteObserver *observer);
    void removeObserver();
    // notify for observer;
    void notify();
    RingBuffer m_RingBuffer;       
private:   
    IRxByteObserver* m_pObserver;   
};

#endif
