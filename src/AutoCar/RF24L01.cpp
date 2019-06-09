/*
 * File: RF24L01.cpp
 * File Created: Sunday, 9th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "RF24L01.h"

void RF24L01::Init()
{
    radio.begin(); //Starting the radio communication
    radio.openWritingPipe(address[0]); // setting the address at which we will send the data;
    radio.openReadingPipe(1, address[1]);// setting the address at which we will receive the data;
    radio.setPALevel(RF24_PA_MIN);/// setting minimum or maximum depending on the distance between the transmitter and receiver.
}

void RF24L01::Send(const char*buffer, int length)
{
    radio.stopListening(); // this sets the module as transmitter.
    radio.write(buffer, length);
}

void RF24L01::Receive(char* buffer, int length)
{
    radio.startListening(); // this sets the module as receiver.
    while(!radio.available()); // waiting for the incoming data
    radio.read(buffer, length);
}