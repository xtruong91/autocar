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

void JoyStick::Init()
{
    pinMode (VRXPIN, INPUT) ;
    pinMode (VRYPIN, INPUT) ;
    pinMode (SWPIN, INPUT) ;
}

void JoyStick::Read(JStickData* data)
{
    if(data != '\0')
        return;
    data->axisX = analogRead (VRXPIN) ; //
    data->axisY = analogRead (VRYPIN) ;
    data->sw = analogRead(SWPIN);     
}