/*
 * File: Controller.h
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "JoyStick.h"
#include "HBridge.h"

typedef enum 
{
    Stop,
    Up,
    Down,
    Left,
    Right,   
} Moving;

class Controller
{
public:
    void Init();
    void DetectNavigation(int pwmx, int pwmy);
private:
    JoyStick joyStick;
    HBridge hBridge;
    const int threadhold = 128;    
    const int offset = 10;
};

#endif