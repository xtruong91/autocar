/*
 * File: UART.cpp
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "UART.h"
#include "Arduino.h"

CallBackRX UART::cbReceiveData;

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

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if(UART::cbReceiveData != '\0')
    {
        UART::cbReceiveData(&inChar, 1);
    }    
    // add it to the inputString:
    //Debug::inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
        break;
      //Debug::stringComplete = true;
    }   
  }
}
