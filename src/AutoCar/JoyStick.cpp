/*
 * File: JoyStick.cpp
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */

#include "JoyStick.h"

JoyStick::JoyStick(const JoyStickPinConfig& config)
    : m_config(config)
{

}

RetVal 
JoyStick::init()
{
    pinMode (m_config.VRxPin, INPUT) ;
    pinMode (m_config.VRyPin, INPUT) ;
    pinMode (m_config.SWPin, INPUT) ;
}

RetVal 
JoyStick::read(JStickData* data)
{
    if(data == NULL)
        return RET_FAIL;
    data->axisX = analogRead (m_config.VRxPin) ; //
    data->axisY = analogRead (m_config.VRyPin) ;
    data->sw = analogRead(m_config.SWPin);
    return RET_SUCCESS;       
}