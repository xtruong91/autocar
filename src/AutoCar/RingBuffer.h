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
    class Iterator
    {
    public:
        char get();
        char operator*();
        Iterator operator++();
        Iterator operator--();

        bool operator==(const Iterator &other);
        bool operator!=(const Iterator &other);
    private:
        RingBuffer *prbuffer;
        unsigned int index;
        Iterator(RingBuffer *rBuffer, unsigned int i = 0);
        bool isValid() const;
        unsigned int getIndex() const;

        friend class RingBuffer;
    };
    static const unsigned int DEFAULT_SIZE = 1024; // set 1MB size
    RingBuffer(unsigned int bufLength = DEFAULT_SIZE);
    ~RingBuffer();

    Iterator begin();
    Iterator end();

    /**
     * Get current size of data in buffer (in bytes)
    */
    int getDataSize();
    /*
    * Method: push one byte into buffer;
    * Returns:
    *  0 - Success
    * -1 - Out of space
    */
    int push(char data);

    /**
     * Append data to buffer
     * Returns:
     * 0 - Success
     * -1 if data length is bigger than available space in buffer
     * -2 if data is NULL or len is zero;
    */
    int push(const char *data, unsigned int len);

    /*
    * Method: pop one from front size buffer;
    * Returns:
    *  0 - Success
    * -1 - Empty
    */
    int pop(char *data);

    /**
     * Get a data segment at the begin of buffer, with length, then remove that segment from buffer
     * @param: data pointer to buffer which will receive data. The buffer must have enough size for
     * output data. Notee: this is not null-terminated
     * 
     * @return: number of bytes outputed. If error occurs, -1 return;
     * 
     * 
    */
    int pop(char *data, unsigned int len);

    /*
    * Method: get available space in buffer
    * Returns: number of bytes available
    */
    unsigned int getAvailableSpace();

private:
    char  *cbuffer;
    RingBuffer_t *psRingBuffer;   
};

#endif