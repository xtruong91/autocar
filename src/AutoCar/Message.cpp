/*
 * File: Message.cpp
 * File Created: Wednesday, 19th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */

#include "Message.h"

Message::Message()
    : id(0), code(0), payload(NULL)
{}

Message::Message(MsgId_t id,
                 MsgCode_t code)
    : id(id), code(code), payload(NULL)
{
}

Message::Message(MsgId_t id,
                 MsgCode_t code,
                 Payload *pl)
    : id(id), code(code), payload(pl)
{
}

Message::~Message()
{
    if (payload != NULL) delete payload;
}

MsgId_t 
Message::getId() const
{
    return id;
}

void 
Message::setId(MsgId_t id)
{
    this->id = id;
}

MsgCode_t
Message::getCode() const
{
    return code;
}

void 
Message::setCode(MsgCode_t code)
{
    this->code = code;
}

const Payload *
Message::getPayload() const
{
    const Payload *p = payload;
    return p;
}

void
Message::setPayload(Payload *pl)
{
    if (payload != NULL) delete payload;
    payload = pl;
}

void
Message::setBytePayload(const char *pl)
{

}