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
void Controller::DetectNavigation(int pwmx, int pwmy)
{
    
}