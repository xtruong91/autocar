/*
 * File: MessageParser.h
 * File Created: Wednesday, 19th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _MESSAGE_PARSER_H_
#define _MESSAGE_PARSER_H_

#include "Message.h"
#include "RingBuffer.h"

class MessageParser
{
public:
    /**
     * Consume data in buffer and return a message object.
     *
     * @param buffer ByteBuffer
     *
     * @return Pointer to dynamically allocated Message object. Returned message
     * must be deleted manually. When no complete message available from buffer,
     * NULL will be returned.
     */
    virtual Message* parse(RingBuffer& buffer);

    /**
     * Encode message and push to buffer.
     *
     * @param msg Pointer to Message object
     * @param buffer ByteBuffer
     *
     * @return Non-negative value when success. When error occurs, a negative
     * value will be returned.
     */
    virtual int push(const Message *msg,
                     RingBuffer& buffer);
private:
    static const unsigned int MAX_MSG_SIZE = 40960; // Must bigger than 16
    static const unsigned int MAX_PAYLOAD_SIZE = MAX_MSG_SIZE - 16;
};

#endif
