/*
 * File: Controller.cpp
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */

#include "Controller.h"

void Controller::Init()
{
    joyStick.Init();
    hBridge.Init();
}
Speed Controller::DetectSpeed(int pwm, int threshold)
{
    Speed result;
    if(pwm < threshold)
    {
        if(pwm < threshold/3)
        {
            result = QUICK;
        }else if (pwm >= threshold/3 && pwm < (2*threshold)/3)
        {
            result = MEDIUM;
        }else
        {
            result = SLOW;
        }        
    }else
    {
        if(pwm < 2*threshold/3)
        {
            result = SLOW;
        }else if(pwm >= 2*threshold/3 && pwm > 4*threshold/3)
        {
            result = MEDIUM;
        }else
        {
            result = QUICK;
        }            
    }
    return result;       
}

Moving Controller::DetectNavigation(int pwmx, int pwmy, int threshold)
{
    Moving direction;
    if(pwmx < (threshold - offset))
    {
        direction = Left;
    } else if(pwmx >(threshold + offset))
    {
        direction = Right;
    } else if (pwmy < (threshold - offset))
    {
        direction = Up;
    } else if (pwmy > (threshold + offset))
    {
        direction = Down;
    }else
    {
        direction = Stop;
    }
    return direction;    
}

void Controller::ControlHBridge(Moving way)
{
    switch (way)
    {
    case Up:
        hBridge.MoveUp();
        break;
    case Down:
        hBridge.MoveDown();
        break;        
    case Left:
        hBridge.MoveLeft();
        break;
    case Right:
        hBridge.MoveLeft();
        break;            
    default:
        break;
    }
}
void Controller::ControlHBridge(Moving way, Speed speed)
{
    switch (way)
    {
    case Up:
        hBridge.MoveUp(speed);
        break;
    case Down:
        hBridge.MoveDown(speed);
        break;        
    case Left:
        hBridge.MoveLeft(speed);
        break;
    case Right:
        hBridge.MoveLeft(speed);
        break;            
    default:
        break;
    }
}


void Controller::Run()
{
    // Read joystick
    joyStick.Read(&jsData);
    // calculate Navigation and speed ;
    way = DetectNavigation(jsData.axisX, jsData.axisY, thresholdPWM);
    speed = DetectSpeed(jsData.axisX, thresholdPWM);
    // controll;
    ControlHBridge(way);    
}