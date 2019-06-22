/*
 * File: RF24L01.cpp
 * File Created: Sunday, 9th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "RF24L01.h"

RingBuffer RF24L01::m_rbuffer;

RF24L01* RF24L01::m_instance = NULL;

RF24L01*
RF24L01::instance()
{
    if(m_instance == NULL)
        m_instance = new RF24L01();
    return m_instance;
}


void 
RF24L01::init(const RF24Config& config,bool masterMode)
{
    m_config = config;
    // radio.begin(); //Starting the radio communication
    // radio.openWritingPipe(address[0]); // setting the address at which we will send the data;
    // radio.openReadingPipe(1, address[1]);// setting the address at which we will receive the data;
    // radio.setPALevel(RF24_PA_MIN);/// setting minimum or maximum depending on the distance between the transmitter and receiver.
    SPI.begin(); // Begins the SPI communication;

    if(masterMode)
    {
        SPI.setClockDivider(SPI_CLOCK_DIV8); //Sets clock for SPI communication at 8 (16/8=2Mhz)
        digitalWrite(m_config.CEPin, HIGH);
    }
    else
    {
        pinMode(m_config.MISOPin,OUTPUT);                   //Sets MISO as OUTPUT (Have to Send data to Master IN 
        SPCR |= _BV(SPE);                       //Turn on SPI in Slave Mode
    }
    
    SPI.attachInterrupt();
}
 
// handle interrupt routine
ISR (SPI_STC_vect)                        //Inerrrput routine function 
{
  char receivedSPI = SPDR;         // Value received from master if store in variable slavereceived
  RF24L01::m_rbuffer.push(receivedSPI);
  if(receivedSPI == RF24L01::endFrame)
  {
      RF24L01::instance()->notify();
  }  
}

void 
RF24L01::registerObs(IRxByteObserver *obs)
{
    m_pRxSPIObservers.push_back(obs);
}

void 
RF24L01::unregisterObs(IRxByteObserver *obs)
{
    //m_pRxObservers.push_back(obs)
}

void 
RF24L01::notify()
{
    // publisher broadcasts
    for(int i = 0; i < m_pRxSPIObservers.size(); i++)
    {
        m_pRxSPIObservers[i]->rcvRawData(RF24L01::m_rbuffer);
    }
}

int 
RF24L01::send(const char *data, unsigned int length)
{
    if(data == NULL || length == 0)
        return -1;
    
    digitalWrite(m_config.CEPin, LOW); //starts communication with savel
    int i;
    for(i = 0; i < length; i++)
    {
        SPI.transfer(data[i]); 
    }
    return i;
}
