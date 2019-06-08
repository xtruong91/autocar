/*
 * File: JoyStick.h
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Arduino.h"

#define VRXPIN     A0
#define VRYPIN     A1
#define SWPIN      A2

typedef struct 
{
    /* data */
    int axisX;
    int axisY;
    int sw;
}JStickData;

class JoyStick
{
public:
    void Init();
    void Read(JStickData* data);
};

#endif