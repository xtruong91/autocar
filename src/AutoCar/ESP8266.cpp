/*
 * File: ESP8266.cpp
 * File Created: Sunday, 9th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "ESP8266.h"

ESP8266::ESP8266(UART* uartSubject)
{
    pSubject = uartSubject;
}

void ESP8266::Send(const char* buffer, int length)
{

}

void ESP8266::Update(char *buffer, int length)
{
    Serial.println(buffer);
    Serial.println("Length:");
    Serial.print(length);
    Serial.println();
}
