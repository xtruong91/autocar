/*
 * File: RingBuffer.h
 * File Created: Sunday, 9th June 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */
#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

typedef struct {
    char * const buffer;
    int head;
    int tail;
    const int maxlen;
} RingBuffer_t;


class RingBuffer
{
public:
    RingBuffer(unsigned int bufLength);
    ~RingBuffer();
    /*
    * Method: circ_buf_push
    * Returns:
    *  0 - Success
    * -1 - Out of space
    */
    int push(char data);

    /*
    * Method: circ_buf_pop // pop each byte
    * Returns:
    *  0 - Success
    * -1 - Empty
    */
    int pop(char *data);

    /*
    * Method: circ_bbuf_free_space
    * Returns: number of bytes available
    */
    int free_space();

    int length();
private:
    unsigned int bufLength;
    char  *buffers;
    RingBuffer_t *m_pBuffer;     
};

#endif