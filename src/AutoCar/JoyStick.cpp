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

void 
JoyStick::init(const JoyStickConfig &config)
{
    m_config = config;
    pinMode (m_config.VRxPin, INPUT) ;
    pinMode (m_config.VRyPin, INPUT) ;
    pinMode (m_config.SWPin, INPUT) ;
}

void 
JoyStick::read(JStickData* data)
{
    if(data != NULL)
        return;
    data->axisX = analogRead (m_config.VRxPin) ; //
    data->axisY = analogRead (m_config.VRxPin) ;
    if(analogRead(m_config.SWPin) >= 1023)
    {
         data->sw = true;
    }
    else
    {
        data->sw = false;
    }
    
       
}