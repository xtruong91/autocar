/*
 * File: RingBuffer.cpp
 * File Created: Thursday, 20th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#include "RingBuffer.h"
#include "Utils.h"
#include "Arduino.h"

 char
RingBuffer::Iterator::get()
{
    return prbuffer->cbuffer[index];
}

char 
RingBuffer::Iterator::operator*()
{
    return get();
} 

RingBuffer::Iterator
RingBuffer::begin()
{
    Iterator beginIt(this, psRingBuffer->tail);
    return beginIt;    
}

RingBuffer::Iterator
RingBuffer::end()
{
    Iterator endIt(this, psRingBuffer->head);
    return endIt;    
}

RingBuffer::Iterator
RingBuffer::Iterator::operator++()
{
    index = (index % prbuffer->psRingBuffer->maxlen) + 1;
    if(index > prbuffer->psRingBuffer->head)
        index = prbuffer->psRingBuffer->head;
    Iterator newIt(prbuffer, index);
    return newIt;
}

RingBuffer::Iterator
RingBuffer::Iterator::operator--()
{
    index = ((index) % prbuffer->psRingBuffer->maxlen) - 1;
    if(index <= prbuffer->psRingBuffer->tail)
        index = prbuffer->psRingBuffer->tail;
    Iterator newIt(prbuffer, index);
    return newIt;
}

bool
RingBuffer::Iterator::operator==(const RingBuffer::Iterator &other)
{
    return (index == other.index);
}

bool
RingBuffer::Iterator::operator!=(const RingBuffer::Iterator &other)
{
    return (index != other.index);
}

RingBuffer::Iterator::Iterator(RingBuffer *buffer, unsigned int i)
{
    this->prbuffer = buffer;
    this->index = i;
}

RingBuffer::RingBuffer(unsigned int bufLength)
    : cbuffer(NULL) 
{
    cbuffer = new char[bufLength + 1];
    psRingBuffer = new RingBuffer_t{ cbuffer, 0, 0, bufLength + 1};
}

RingBuffer::~RingBuffer() 
{
    if(cbuffer != NULL)
    {
        delete[] cbuffer;
    }

    if(psRingBuffer != NULL)
    {
        delete psRingBuffer;
    }

}

int 
RingBuffer::push(char data)
{
    int next;

    next = psRingBuffer->head + 1;  // next is where head will point to after this write.
    if (next >= psRingBuffer->maxlen)
        next = 0;

    // if the head + 1 == tail, circular buffer is full. Notice that one slot
    // is always left empty to differentiate empty vs full condition
    if (next == psRingBuffer->tail)
        return -1;

    psRingBuffer->buffer[psRingBuffer->head] = data;  // Load data and then move
    psRingBuffer->head = next;             // head to next data offset.
    return 0; // return success to indicate successful push.
}

int
RingBuffer::push(const char *data, unsigned int len)
{
    if(data == NULL || len == 0)
        return -2;
    
    if(len > getAvailableSpace())
        return -1;
    int i;
    for(i = 0; i < len; i++)
    {
        if(push(data[i]) < 0)
            break;        
    }

    return i;
} 

int 
RingBuffer::pop(char *data)
{
    int next;

    if (psRingBuffer->head == psRingBuffer->tail)  // if the head == tail, we don't have any data
        return -1;

    next = psRingBuffer->tail + 1;  // next is where tail will point to after this read.
    if(next >= psRingBuffer->maxlen)
        next = 0;

    *data = psRingBuffer->buffer[psRingBuffer->tail];  // Read data and then move
    psRingBuffer->tail = next;              // tail to next offset.
    return 0; // return success to indicate successful push.
}

int
RingBuffer::pop(char *data, unsigned int len)
{
    if(len == 0)
        return -2;
    
    int  i = 0;
    for(int i = 0; i < len; i++)
    {
        if(pop(&data[i]) < 0)
            break;
    }
    return i;
}

unsigned int
RingBuffer::getAvailableSpace()
{
    int freeSpace;
    freeSpace = psRingBuffer->tail - psRingBuffer->head;
    if (freeSpace <= 0)
        freeSpace += psRingBuffer->maxlen;
    return freeSpace - 1; // -1 to account for the always-empty slot.
}

int 
RingBuffer::getDataSize()
{
    return psRingBuffer->maxlen - getAvailableSpace();
}


