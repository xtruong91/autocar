/*
 * File: ControllerConfig.cpp
 * File Created: Saturday, 22nd June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "ControllerConfig.h"

ControllerConfig::ControllerConfig()
{
    joyStickCfg.VRxPin = VRXPIN;
    joyStickCfg.VRyPin = VRYPIN;
    joyStickCfg.SWPin = SWPIN;

    hBridgeCfg.Pin1 =  WHEELLEFTPIN1;
    hBridgeCfg.Pin2 =  WHEELLEFTPIN2;
    hBridgeCfg.Pin3 = WHEELRIGHTPIN1;
    hBridgeCfg.Pin4 = WHEELRIGHTPIN2;
}

ControllerConfig* 
ControllerConfig::m_instance = NULL;

ControllerConfig* 
ControllerConfig::instance()
{
    if(m_instance == NULL)
        m_instance = new ControllerConfig();
    return m_instance;
}
            