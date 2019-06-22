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
#include "Debug.h"

#define DEBUG

Message* 
MessageParser::parse(RingBuffer& buffer)
{
    // Minimal size is 10 byte;
    if(buffer.getDataSize() < 10) return NULL;

    RingBuffer::Iterator it;
#ifdef DEBUG
    Debug::instance()->printf("handling message: %d \n", buffer.getDataSize());
    for(it = buffer.begin(); it != buffer.end(); it++)
    {
        Debug::instance()->printf("%c", *it);
    }
#else        
    // Check two byte preamble of packet "!!";
    if(*it != '!' || *(++it) != '!')
        return NULL;
    // check CRC
    // get two byte ID message
    unsigned short id = 0;
    id = *(++it); 
    id = (id << 8) | *(++it);

    // get  two bytes Code Messag
    unsigned short code = 0;
    code = *(++it); 
    code = (code << 8) | *(++it);
    
    // get two length bytes of payload;
    unsigned short payloadSize = 0;

    payloadSize = *(++it); 
    payloadSize = (payloadSize << 8) | *(++it);

    // get payload
    char *payload;
    if(payloadSize  > 0)
    {
        payload = new char[payloadSize];
        for(int i = 0; i < payloadSize; i++)
        {
            if(it == buffer.end())
            {
                break;
            }
            payload[i] = *it;
            ++it;
        }
    }
#endif    
    // Create message object;
    //Message *msg = new Message(id, code);
    return NULL;
}

int
MessageParser::push(const Message *msg, RingBuffer& buffer)
{
    if(msg == NULL)
        return -1;
    // Preamble;
    char preamble = '!';
    buffer.push(preamble);
    buffer.push(preamble);

    //ID
    buffer.push((char)(msg->getId() << 8) & 0xff);
    buffer.push(msg->getId() & 0xff);

    // Code;
    buffer.push((char)(msg->getCode() << 8) & 0xff);
    buffer.push(msg->getCode() & 0xff);

    // caculate size;
    unsigned short length = 0;
    buffer.push((char)(length << 8) & 0xff);
    buffer.push(length & 0xff);     
}