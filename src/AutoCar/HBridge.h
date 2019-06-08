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

#ifndef HBRIDGE_H
#define HBRIDGE_H

#define WHEELLEFTPIN1   5
#define WHEELLEFTPIN2   6
#define WHEELRIGHTPIN1  10
#define WHEELRIGHTPIN2  11

typedef enum
{
    SLOW,
    MEDIUM,
    QUICK
}Speed;

class HBridge
{
public:
    void Init();
    void MoveUp();
    void MoveUp(Speed level);
    void MoveDown();
    void MoveDown(Speed level);
    void MoveLeft();
    void MoveLeft(Speed speed);
    void MoveRight();
    void MoveRight(Speed speed);
    void Stop();
private:
    static int ConvertSpeed2PWM(Speed speed); 
    static const int threshold;
};

#endif