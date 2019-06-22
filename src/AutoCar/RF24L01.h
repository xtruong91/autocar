/*
 * File: RF24L01.h
 * File Created: Sunday, 9th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: send/receive data via RF;
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _RF24L01_H_
#define _RF24L01_H_

#include <SPI.h>
#include "RingBuffer.h"
#include "IRxByteObserver.h"
#include "Vector.h"

#define CSPIN           9
#define CSNPIN         10

struct RF24Config
{
    unsigned int MISOPin; // master in slave output
    unsigned int MOSIPin; // master output slave input
    unsigned int SCKPin;      // serial clock pin 
    unsigned int CEPin;// Chip enable, which used to enable SPI communication;
    unsigned int CSNPin;// Ship select not, this pin has to kept high aways else it will disable the SPI
    unsigned int IRQPin;// interrupt pin, It is an active low pin and is used only if interrupt is required
};



class RF24L01
{
public:
    static RF24L01 *instance();
    void init(const RF24Config& config, bool masterMode);
    
    // subscribe/ unsubscribe received data from SPI port
    void registerObs(IRxByteObserver* obs);
    void unregisterObs(IRxByteObserver *obs);
    
    //broadcase to all subscribe
    void notify();

    int send(const char *data, unsigned int length);    

private:            
    RF24Config m_config;
    RF24L01(){};

public:
    static RF24L01 *m_instance;
    static const char endFrame = '\n';    
    static RingBuffer m_rbuffer;
    Vector<IRxByteObserver*> m_pRxSPIObservers;
    //const static char address [][2] = {"000001", "000002"};
    
};

#endif