/*
 * File: MessageParser.cpp
 * File Created: Thursday, 20th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * |2 byte preamble| 2 byte ID| 2 byte Code Message| 2 byte Length| Payload | 2 byte CRC|
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "MessageParser.h"

Message* 
MessageParser::parse(RingBuffer& buffer)
{
    // Minimal size is 10 byte;
    if(buffer.getDataSize() < 10) return NULL;

    // Check preamble of packet;

    // check CRC

    // get ID message

    // get Code Message

    // get length of payload

    // get payload


}