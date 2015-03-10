/*! \file ********************************************************************
 *
 *  \brief      Simple char ring buffer for microcontrollers
 *  \author     Dan Fekete <thefekete@gmail.com>
 *  \date       March 10, 2015
 *
 *  \copyright  Copyright 2015, Dan Fekete <thefekete@gmail.com>
 *              Released under the GNU GPL version 3
 *
 *  CharRing is a simple character ring/circular buffer designed for
 *  microcontrollers.
 *
 *****************************************************************************/
#include "charring.h"
#include <stdlib.h>


/** \brief  Allocates and returns a pointer to a new CharRingBuf buffer object.
 *
 *  \warning    A call to CharRing_free() is required to properly free
 *  allocated memory.
 *
 *  \param len  size of buffer to be created
 *  \return a new CharRingBuf buffer struct
 */
CharRingBuf *CharRing_new(int16_t len)
{
    CharRingBuf *buffer = calloc(1, sizeof(*buffer));
    buffer->len = len;
    buffer->buf = calloc(buffer->len, sizeof(buffer->buf));

    return buffer;
}


/** \brief  Destroys a character ring buffer
 *
 *  Properly frees all memory that was allocated in the creation of CharRingBuf
 *  b.
 *
 *  \param b  CharRingBuf buffer to be destroyed
 */
void CharRing_free(CharRingBuf *b)
{
    free(b->buf);
    free(b);
}


/** \brief  Writes a character to buffer
 *
 *  \warning    If the buffer is full, it will discard the oldest char in the
 *  buffer to make room.
 *
 *  If losing data is unacceptable then you need to check on the buffer before
 *  writing to it. CharRing_free_space() will give you the free space in the
 *  buffer and you can check to see if the buffer is full with CharRing_full():
 *
 *  \code
 *  while (CharRing_full(my_buf));  // wait for buffer to open up
 *  \endcode
 *
 *  \param b  CharRingBuf buffer to write
 *  \param c  character to write
 */
void CharRing_putchar(CharRingBuf *b, char c)
{
    if (CharRing_full(b)) {
        /* buffer is full, read out char to make room */
        CharRing_getchar(b);
    }
    b->buf[b->head] = c;
    b->head++;
    b->head %= b->len;
    b->count++;
}


/** \brief  Reads a character from buffer
 *
 *  If there are no chars available in the buffer, this will always return '\0'
 *  (null char). But thats what CharRing_available() and CharRing_empty() are
 *  for:
 *
 *  \code
 *  if (CharRing_available(my_buf)) {
 *      // do stuff
 *  }
 *
 *  if (!CharRing_empty(my_buf)) {
 *      // do stuff
 *  }
 *  \endcode
 *
 *  \param b    CharRingBuf buffer to read
 *  \return     Next char from buffer ('\0' if buffer empty)
 */
char CharRing_getchar(CharRingBuf *b)
{
    char c = 0;
    if (CharRing_available(b)) {
        c = b->buf[b->tail];
        b->tail++;
        b->tail %= b->len;
        b->count--;
    }
    return c;
}
