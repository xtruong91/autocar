/*
 * File: JoyStick.h
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: Joystick use  variable resistor to change voltage
 * It has three output pins: VRx, VRy, SW
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include "Arduino.h"
#include "Utils.h"

typedef struct 
{
    /* data */
    int axisX;
    int axisY;
    int sw;
}JStickData;

struct JoyStickPinConfig
{
    unsigned int VRxPin;
    unsigned int VRyPin;
    unsigned int SWPin;
};

class JoyStick
{
public:
    JoyStick(const JoyStickPinConfig& config);
    RetVal init();
    RetVal read(JStickData* data);
    JoyStickPinConfig getConfig() const
    {
        return m_config;
    }
private:
    JoyStickPinConfig m_config;    
};

#endif