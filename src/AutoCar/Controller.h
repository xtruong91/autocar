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

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "ControllerConfig.h"

//#define DEBUG
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
    Controller(const ControllerConfig& config);
    // Initialize all components;
    void init();
    void run();

private:
    /**
     * @param1: pwmx with range 0-1023 corresponding x axis;
     * @param2: pwmy with range 0-1023 corresponding y axis;
     * @param3: threadhold which detect original coordination;
     * @return: direction;
    */    
    Moving determineDirect(int pwmx, int pwmy, int threshold = 512);
    /**
     * @param: pwm value range 0 - 255, divide into three sub-range
     * @return: low, medium, quick level
    */
    Speed convertPWM2Speed(int pwm, int threshold);

    void controlHBridge(Moving way, Speed speed);
    void controlHBridge(Moving way);

    double computePID(double input);    
private:
    JoyStick m_joyStick;
    HBridge m_hBridge;
    JStickData joyStickData;

    Speed speed;
    Moving way;
    int thresholdPWM;    
    const int offset = 10;
    
    static const double kp = 2;
    static const double ki = 5;
    static const double kd = 1;

    unsigned long currentTime, previousTime;
    double elapsedTime;
    double error;
    double lastError;
    double input, output, setPoint = 0;
    double cumError, rateError;
};

#endif