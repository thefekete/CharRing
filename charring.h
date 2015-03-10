/*! \file ********************************************************************
 *
 *  \brief      Simple char ring buffer for microcontrollers
 *  \author     Dan Fekete <thefekete@gmail.com>
 *  \date       March 10, 2015
 *
 *  \copyright  Copyright 2015, Dan Fekete <thefekete@gmail.com>
 *              LICENSE
 *
 *  CharRing is a simple character ring/circular buffer designed for
 *  microcontrollers.
 *
 *****************************************************************************/
#ifndef _CHARING_H_
#define _CHARING_H_

#include <stdint.h>

/**  Returns the number of available chars in CharRing buffer B */
#define CharRing_available(B)    ((B)->count)

/**  Returns the number of free slots in CharRing buffer B */
#define CharRing_free_space(B)   ((B)->len - (B)->count)

/**  Returns whether CharRing buffer B is full or not */
#define CharRing_full(B)         ((B)->count == (B)->len)

/**  Returns whether CharRing buffer B is empty or not */
#define CharRing_empty(B)        ((B)->count == 0)


/** \brief Holds all data for a buffer
 *
 *  \warning    Don't mess with this directly, use the functions and macros to
 *              manipulate the buffers!
 */
typedef struct {
    char *buf;  /**< \brief Pointer to buffer chars */
    int16_t head;  /**< \brief Write offset */
    int16_t tail;  /**< \brief Read offset */
    int16_t count;  /**< \brief Number of chars in buffer */
    int16_t len;  /**< \brief Total buffer length */
} CharRingBuf;

CharRingBuf *CharRing_new(int16_t);
void CharRing_free(CharRingBuf *);
void CharRing_putchar(CharRingBuf *, char);
char CharRing_getchar(CharRingBuf *);

#endif /* _CHARING_H_ */
