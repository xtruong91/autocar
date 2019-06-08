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

#define PWM_WIDTH       255

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
    void Run();
private:    
    Moving DetectNavigation(int pwmx, int pwmy, int threshold);
    // Range PWM 255
    /*
        threshold = 128 in range 255
    */
    Speed DetectSpeed(int pwm, int threshold);
    void ControlHBridge(Moving way, Speed speed);
    void ControlHBridge(Moving way);
private:
    JoyStick joyStick;
    HBridge hBridge;
    JStickData jsData;
    Speed speed;
    Moving way;
    static const int thresholdPWM = 128;    
    const int offset = 10;
};

#endif