/*
 * File: JsonParser.cpp
 * File Created: Sunday, 23rd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "JsonParser.h"

JsonParser::JsonParser()
    : m_doc(capacity)
{

}

RetVal 
JsonParser::decode(const char* data, Message& msgOutput)
{
      // Parse JSON object
    DeserializationError error = deserializeJson(m_doc, data);
    if(error)
    {
        return RET_FAIL;
    }

    JsonObject root = m_doc.as<JsonObject>();

    MsgId_t id = root["Id"].as<MsgId_t>();
    MsgCode_t code = root["Code"].as<MsgCode_t>();
    String msg =  root["Payload"].as<char*>();

    msgOutput.setId(id);
    msgOutput.setCode(code);
    msgOutput.setBytePayload(data);

    return RET_SUCCESS;
}

RetVal 
JsonParser::encode(const Message &msg, String& outputJson)
{
    JsonObject root = m_doc.to<JsonObject>();

    root["Id"] = msg.getId();
    root["Code"] = msg.getId();

    serializeJsonPretty(root, outputJson);
    return RET_SUCCESS;
}