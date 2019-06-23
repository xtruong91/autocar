/*
 * File: JsonParser.h
 * File Created: Saturday, 22nd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _JSON_PARSER_H_
#define _JSON_PARSER_H_

#include "Utils.h"
#include "Message.h"
#include <String>
#include <ArduinoJson.h>

class JsonParser
{
public:
    explicit JsonParser();

    /**
     * decode from serial byte into message
     * @param: data is string byte;
     * @param: msgOutput is result output;
     * @return: if serialize successful-> return RET_SUCCESS, else return RET_FAIL 
    */
    RetVal decode(const char* data, Message& msgOutput);

    /**
     * decode from serial byte into message
     * @param: msg is message input
     * @param: JsonOutput is string output;
     * @return: if serialize successful-> return RET_SUCCESS, else return RET_FAIL 
    */
    RetVal encode(const Message &msg, String& outputJson);

private:
    static const unsigned int capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
    DynamicJsonDocument m_doc;

};

#endif