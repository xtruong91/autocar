/*
 * File: ControllerConfig.h
 * File Created: Saturday, 22nd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _CONTROLLER_CONFIG_H_
#define _CONTROLLER_CONFIG_H_

#include "JoyStick.h"
#include "HBridge.h"
#include "Utils.h"

#define VRXPIN     A0
#define VRYPIN     A1
#define SWPIN      A2

#define WHEELLEFTPIN1   5
#define WHEELLEFTPIN2   6

#define WHEELRIGHTPIN1  9
#define WHEELRIGHTPIN2  10


class ControllerConfig
{
public:
    HBridgePinConfig hBridgeCfg;
    JoyStickPinConfig joyStickCfg;

    static ControllerConfig *instance();            
private:
    static ControllerConfig *m_instance;
     ControllerConfig();   
};



#endif