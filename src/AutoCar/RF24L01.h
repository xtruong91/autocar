/*
 * File: RF24L01.h
 * File Created: Sunday, 9th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef RF24L01_H
#define RF24L01_H

#include <SPI.h>
#include <RF24.h>

#define CSPIN           9
#define CSNPIN         10

RF24 radio(CSPIN, CSNPIN); // CE, CSN
byte address [][2] = {"000001", "000002"};

class RF24L01
{
public:
    void Init();
    void Send(const char *buffer, int length);
    void Receive(char *buffer, int length);    
};

#endif