/*
 * File: UART.cpp
 * File Created: Sunday, 23rd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "UART.h"
#include "HardwareSerial.h"
#include "Arduino.h"



void 
UART::init(const UARTConfig& config)
{
    if(config.uartPort == 0)
    {
        Serial.begin(config.baudrate);
    }
    else
    {
        Serial1.begin(config.baudrate);
    }    
}


void 
UART::run()
{
    if(Serial.available() > 0)
    {
        char c = Serial.read();
        m_RingBuffer.push(c);
        if(c == '\n')
        {
            notify();
        }
    }
}

void 
UART::setObserver(IRxByteObserver *observer)
{
    if(m_pObserver != NULL)
    {
        delete m_pObserver;
        m_pObserver = NULL;
    }
    m_pObserver = observer;
}

void 
UART::removeObserver()
{
    if(m_pObserver != NULL)
    {
        delete m_pObserver;
        m_pObserver = NULL;
    }
}
    // notify for observer;
void 
UART::notify()
{
    if(m_pObserver != NULL)
    {
        m_pObserver->update(m_RingBuffer);
    }
    
}