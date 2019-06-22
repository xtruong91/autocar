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
#include "Debug.h"

Controller::Controller(const ControllerConfig& config)
    : m_hBridge(config.hBridgeCfg),
     m_joyStick(config.joyStickCfg),
     thresholdPWM(0)
{

}

void 
Controller::init()
{
    m_joyStick.init();
#ifdef DEBUG
        Debug::instance()->printf("PinVx:%d, PinVRy:%d, PinSW:%d\n", 
                            m_joyStick.getConfig().VRxPin,m_joyStick.getConfig().VRyPin,
                            m_joyStick.getConfig().SWPin);
#endif
    // wait for calib;
    m_joyStick.read(&joyStickData);
    thresholdPWM = (joyStickData.axisX + joyStickData.axisY) /2; 

    m_hBridge.init();

    m_pGateway = MessageGateway::instance();
    m_pGateway->init();
}

Speed 
Controller::convertPWM2Speed(int pwm, int threshold)
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

Moving 
Controller::determineDirect(int pwmx, int pwmy, int threshold)
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

void 
Controller::controlHBridge(Moving way)
{
    switch (way)
    {
    case Up:
        m_hBridge.moveUp();
        break;
    case Down:
        m_hBridge.moveDown();
        break;        
    case Left:
        m_hBridge.moveLeft();
        break;
    case Right:
        m_hBridge.moveRight();
        break;            
    default:
        m_hBridge.stop();
        break;
    }
}

void 
Controller::controlHBridge(Moving way, Speed speed)
{
    switch (way)
    {
    case Up:
        m_hBridge.moveUp(speed);
        break;
    case Down:
        m_hBridge.moveDown(speed);
        break;        
    case Left:
        m_hBridge.moveLeft(speed);
        break;
    case Right:
        m_hBridge.moveLeft(speed);
        break;            
    default:
        break;
    }
}


void 
Controller::run()
{
    // Read joystick
    m_joyStick.read(&joyStickData);
    
    //Debug::instance()->printf("Result: %d \n", );
    // calibration threshold = average(x, y);
    // Press Sw to calibrate
    way = determineDirect(joyStickData.axisX, joyStickData.axisY, thresholdPWM);    
    //speed = convertPWM2Speed(jsData.axisX, thresholdPWM);
#ifdef DEBUG
    Debug::instance()->printf("VRx:%d, VRy:%d, SW:%d, Way:%d \n", 
                            joyStickData.axisX, joyStickData.axisY, joyStickData.sw ,way);
#endif    
    // controll;
    controlHBridge(way);    
}

double Controller::computePID(double input)
{
    currentTime = millis();                //get current time
    elapsedTime = (double)(currentTime - previousTime);        //compute time elapsed from previous computation
    
    error = setPoint - input;                                // determine error
    cumError += error * elapsedTime;                // compute integral
    rateError = (error - lastError)/elapsedTime;   // compute derivative

    double out = kp*error + ki*cumError + kd*rateError;                //PID output               

    lastError = error;                                //remember current error
    previousTime = currentTime;                        //remember current time

    return out; 
}