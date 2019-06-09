/*
 * File: IObserverRxData.h
 * File Created: Sunday, 9th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef IOBSERVER_RX_DATA_H
#define IOBSERVER_RX_DATA_H

class IObserverRxData
{
public:
    virtual void Update(char *buffer, int length) = 0;
};

#endif