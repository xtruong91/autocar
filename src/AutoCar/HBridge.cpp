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

void HBridge::Init()
{
    pinMode(WHEELLEFTPIN1, OUTPUT);
    pinMode(WHEELLEFTPIN2, OUTPUT);
    pinMode(WHEELRIGHTPIN1, OUTPUT);
    pinMode(WHEELRIGHTPIN2, OUTPUT);
}
void HBridge::MoveUp()
{
    digitalWrite(WHEELLEFTPIN1, LOW);
    digitalWrite(WHEELLEFTPIN2, HIGH);
    digitalWrite(WHEELRIGHTPIN1, LOW);
    digitalWrite(WHEELRIGHTPIN2, HIGH);
}
void HBridge::MoveUp(Speed speed)
{
    int pwm = ConvertSpeed2PWM(speed);
    analogWrite(WHEELLEFTPIN1, 0);
    analogWrite(WHEELLEFTPIN2, pwm);
    analogWrite(WHEELRIGHTPIN1, 0);
    analogWrite(WHEELRIGHTPIN2, pwm);
}
void HBridge::MoveDown()
{
    digitalWrite(WHEELLEFTPIN1, HIGH);
    digitalWrite(WHEELLEFTPIN2, LOW);
    digitalWrite(WHEELRIGHTPIN1, HIGH);
    digitalWrite(WHEELRIGHTPIN2, LOW);
}
void HBridge::MoveDown(Speed speed)
{
    int pwm = ConvertSpeed2PWM(speed);
    analogWrite(WHEELLEFTPIN1, pwm);
    analogWrite(WHEELLEFTPIN2, 0);
    analogWrite(WHEELRIGHTPIN1, pwm);
    analogWrite(WHEELRIGHTPIN2, 0);
}
void HBridge::MoveLeft()
{
    digitalWrite(WHEELLEFTPIN1, LOW);
    digitalWrite(WHEELLEFTPIN2, LOW);
    digitalWrite(WHEELRIGHTPIN1, LOW);
    digitalWrite(WHEELRIGHTPIN2, HIGH);
}
void HBridge::MoveLeft(Speed speed)
{
    int pwm = ConvertSpeed2PWM(speed);
    analogWrite(WHEELLEFTPIN1, pwm);
    analogWrite(WHEELLEFTPIN2, 0);
    analogWrite(WHEELRIGHTPIN1, pwm);
    analogWrite(WHEELRIGHTPIN2, 0);
}
void HBridge::MoveRight()
{
    digitalWrite(WHEELLEFTPIN1, LOW);
    digitalWrite(WHEELLEFTPIN2, LOW);
    digitalWrite(WHEELRIGHTPIN1, LOW);
    digitalWrite(WHEELRIGHTPIN2, HIGH);
}
void HBridge::MoveRight(Speed speed)
{
    int pwm = ConvertSpeed2PWM(speed);
    analogWrite(WHEELLEFTPIN1, 0);
    analogWrite(WHEELLEFTPIN2, 0);
    analogWrite(WHEELRIGHTPIN1, pwm);
    analogWrite(WHEELRIGHTPIN2, 0);
}

int HBridge::ConvertSpeed2PWM(Speed speed)
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