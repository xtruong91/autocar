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

CallBackRX UART::cbReceiveData;

UART *UART::inst = '\0';

UART *UART::Instance()
{
    if(inst == '\0')
    {
        inst = new UART();
    }
    return inst;
}

void UART::Init()
{
    Serial.begin(BAURATE);
    while (!Serial);
}

int UART::Send(const char* data, int length)
{

}
void UART::Attach(CallBackRX subscribeRX)
{
    cbReceiveData = subscribeRX;
}

int index = 0;
char buffer[BUFF_LENGTH];

void serialEvent() {
  while (Serial.available()) 
  {
    // get the new byte
    char rawChar = (char) Serial.read();
    buffer[index++] = rawChar;
    if(rawChar == '\n')
    {
        memset(buffer + index, '\0', BUFF_LENGTH - index);
        UART::Instance()->NotifyOb(buffer,index-1);
        index = 0;
    }
  }


}

void UART::RegisterOb(IObserverRxData* observer)
{
    observers.push_back(observer);
}
void UART::NotifyOb(char *data, int length)
{
    // publisher broadcasts
    for(int i = 0; i < observers.size(); i++)
    {
        observers[i]->Update(data, length);
    }
}
