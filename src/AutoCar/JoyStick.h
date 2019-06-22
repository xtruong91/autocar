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

// #define VRXPIN     A0
// #define VRYPIN     A1
// #define SWPIN      A2

typedef struct 
{
    /* data */
    int axisX;
    int axisY;
    bool sw;
}JStickData;

struct JoyStickConfig
{
    unsigned int VRxPin;
    unsigned int VRyPin;
    unsigned int SWPin;
};

class JoyStick
{
public:
    void init(const JoyStickConfig& config);
    void read(JStickData* data);
private:
    JoyStickConfig& m_config;    
};

#endif