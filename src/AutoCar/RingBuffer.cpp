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

RingBuffer::RingBuffer(unsigned int bufLength) : 
    bufLength(bufLength) , buffers(NULL) 
{
    buffers = new char[bufLength + 1];
    m_pBuffer = new RingBuffer_t{ buffers, 0, 0, bufLength + 1};
}

RingBuffer::~RingBuffer() 
{
    if(buffers != NULL)
    {
        delete buffers;
    }

    if(m_pBuffer != NULL)
    {
        delete m_pBuffer;
    }

}

int 
RingBuffer::push(char data)
{
    int next;

    next = m_pBuffer->head + 1;  // next is where head will point to after this write.
    if (next >= m_pBuffer->maxlen)
        next = 0;

    // if the head + 1 == tail, circular buffer is full. Notice that one slot
    // is always left empty to differentiate empty vs full condition
    if (next == m_pBuffer->tail)
        return -1;

    m_pBuffer->buffer[m_pBuffer->head] = data;  // Load data and then move
    m_pBuffer->head = next;             // head to next data offset.
    return 0; // return success to indicate successful push.
}

int 
RingBuffer::pop(char *data)
{
    int next;

    if (m_pBuffer->head == m_pBuffer->tail)  // if the head == tail, we don't have any data
        return -1;

    next = m_pBuffer->tail + 1;  // next is where tail will point to after this read.
    if(next >= m_pBuffer->maxlen)
        next = 0;

    *data = m_pBuffer->buffer[m_pBuffer->tail];  // Read data and then move
    m_pBuffer->tail = next;              // tail to next offset.
    return 0; // return success to indicate successful push.
}

int 
RingBuffer::free_space()
{
    int freeSpace;
    freeSpace = m_pBuffer->tail - m_pBuffer->head;
    if (freeSpace <= 0)
        freeSpace += m_pBuffer->maxlen;
    return freeSpace - 1; // -1 to account for the always-empty slot.
}

int 
RingBuffer::length()
{
    return m_pBuffer->maxlen - free_space();
}
