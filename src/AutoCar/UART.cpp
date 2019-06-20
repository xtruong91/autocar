/*
 * File: UART.cpp
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: used vector at: https://github.com/mike-matera/ArduinoSTL
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "UART.h"
#include "Arduino.h"


UART*UART::inst = NULL;

RingBuffer UART::m_rbBuffer(BUFFLEN);

UART *UART::instance()
{
    if(inst == NULL)
    {
        inst = new UART();
    }
    return inst;
}



RetVal
UART::init(UartConfig &config)
{
    //TODO
    Serial.begin(config.baudrate);
    while (!Serial);

#ifdef DEBUG
    Serial.println("Initialize UART module");
#endif
    return RET_SUCCESS;
}

int 
UART::send(const char* data, int length)
{
    return Serial.write(data, length);
}

void 
UART::registerRxObs(IRxUartObserver *obs)
{
    m_pRxObservers.push_back(obs);
}

void
UART::unregisterRxObs(IRxUartObserver *obs)
{
    //TODO
}

void
UART::notify()
{
    // publisher broadcasts
    for(int i = 0; i < m_pRxObservers.size(); i++)
    {
        m_pRxObservers[i]->rcvRawData(UART::m_rbBuffer);
    }
}


void serialEvent() {
  while (Serial.available()) 
  {
    // get the new byte
    char rawChar = (char) Serial.read();
    UART::m_rbBuffer.push(rawChar);
    if(rawChar == '\n')
    { 
        UART::instance()-> notify();
    }
  }
}