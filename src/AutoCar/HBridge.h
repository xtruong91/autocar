/*
 * File: HBridge.h
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */

#ifndef _HBRIDGE_H_
#define _HBRIDGE_H

// #define WHEELLEFTPIN1   5
// #define WHEELLEFTPIN2   6
// #define WHEELRIGHTPIN1  10
// #define WHEELRIGHTPIN2  11

typedef enum
{
    SLOW,
    MEDIUM,
    QUICK
}Speed;

/**
 * HBridge circuit which contain L298 IC,
 * have four output pin
*/
struct HBridgeConfig
{
    unsigned int Pin1;
    unsigned int Pin2;
    unsigned int Pin3;
    unsigned int Pin4;
};

class HBridge
{
public:
    void init(const HBridgeConfig& config);
    // spin clockwise
    void moveUp();
    // turn clockwise along with specific level
    void moveUp(Speed level);
    // spin anticlockwise
    void moveDown();
    void moveDown(Speed level);

    void moveLeft();
    void moveLeft(Speed speed);

    void moveRight();
    void moveRight(Speed speed);

    void stop();
private:
    HBridgeConfig &m_config;
    static int speed2PWM(Speed speed); 
    static const int threshold;
};

#endif