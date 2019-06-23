/*
 * File: Message.h
 * File Created: Sunday, 23rd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "Utils.h"

class Payload;

class Message
{
public:
    Message();
    Message(MsgId_t id, MsgCode_t code);
    Message(MsgId_t id, MsgCode_t code, Payload *pl);
    virtual ~Message();

        MsgId_t getId() const;
    void setId(MsgId_t id);

    MsgCode_t getCode() const;
    void setCode(MsgCode_t code);

    const Payload* getPayload() const;
    /**
     * Set payload object to message.
     * Payload object must be dynamically allocated. It will be deleted by
     * Message object when not be used anymore.
     */
    void setPayload(Payload *pl);

    void setBytePayload(const char *pl){}


private:
    MsgId_t id;
    MsgCode_t code;
    Payload *payload;
};

class Payload
{
public:
    virtual ~Payload() {}
};

#endif