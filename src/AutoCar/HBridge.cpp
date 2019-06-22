/*
 * File: HBridge.cpp
 * File Created: Saturday, 8th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "HBridge.h"
#include "Arduino.h"

const int HBridge::threshold = 128;

HBridge::HBridge(const HBridgePinConfig &config)
    : m_config(config)
{

}

void 
HBridge::init()
{
    pinMode(m_config.Pin1, OUTPUT);
    pinMode(m_config.Pin2, OUTPUT);

    pinMode(m_config.Pin3, OUTPUT);
    pinMode(m_config.Pin4, OUTPUT);
}

void 
HBridge::moveUp()
{
    digitalWrite(m_config.Pin1, LOW);
    digitalWrite(m_config.Pin2, HIGH);

    digitalWrite(m_config.Pin3, HIGH);
    digitalWrite(m_config.Pin4, LOW);
}

void 
HBridge::moveUp(Speed speed)
{
    int pwm = speed2PWM(speed);
    analogWrite(m_config.Pin1, 0);
    analogWrite(m_config.Pin2, pwm);

    analogWrite(m_config.Pin3, pwm);
    analogWrite(m_config.Pin4, 0);
}

void 
HBridge::moveDown()
{
    digitalWrite(m_config.Pin1, HIGH);
    digitalWrite(m_config.Pin2, LOW);

    digitalWrite(m_config.Pin3, LOW);
    digitalWrite(m_config.Pin4, HIGH);
}

void 
HBridge::moveDown(Speed speed)
{
    int pwm = speed2PWM(speed);
    analogWrite(m_config.Pin1, pwm);
    analogWrite(m_config.Pin2, 0);

    analogWrite(m_config.Pin3, 0);
    analogWrite(m_config.Pin4, pwm);
}

void 
HBridge::moveLeft()
{
    digitalWrite(m_config.Pin1, LOW);
    digitalWrite(m_config.Pin2, HIGH);

    digitalWrite(m_config.Pin3, LOW);
    digitalWrite(m_config.Pin4, LOW);
}

void 
HBridge::moveLeft(Speed speed)
{
    int pwm = speed2PWM(speed);
    analogWrite(m_config.Pin1, pwm);
    analogWrite(m_config.Pin2, 0);

    analogWrite(m_config.Pin3, pwm);
    analogWrite(m_config.Pin4, 0);
}

void 
HBridge::moveRight()
{
    //detect left/right wheels.
    digitalWrite(m_config.Pin1, LOW);
    digitalWrite(m_config.Pin2, LOW);

    digitalWrite(m_config.Pin3, LOW);
    digitalWrite(m_config.Pin4, HIGH);
}

void 
HBridge::moveRight(Speed speed)
{
    int pwm = speed2PWM(speed);
    analogWrite(m_config.Pin1, 0);
    analogWrite(m_config.Pin2, 0);

    analogWrite(m_config.Pin3, pwm);
    analogWrite(m_config.Pin4, 0);
}

int 
HBridge::speed2PWM(Speed speed)
{
    if(speed == SLOW)
    {
        return threshold/3;
    }
    else if(speed = MEDIUM)
    {
        return (2*threshold/3);
    }
    else
    {
        return threshold;
    }    
}

void 
HBridge::stop()
{
    digitalWrite(m_config.Pin1, LOW);
    digitalWrite(m_config.Pin2, LOW);

    digitalWrite(m_config.Pin3, LOW);
    digitalWrite(m_config.Pin4, LOW);
}