# CharRing

Doxygen documentation can be found [here](http://thefekete.github.io/CharRing/).

CharRing is a simple character ring/circular buffer designed for microcontrollers.

This was designed with microcontrollers in mind, but it might be useful for other purposes as well.

## Installation
The fastest way to get started is to run this in your project directory:
```sh
wget https://raw.githubusercontent.com/thefekete/CharRing/v1.0/charring.c \
https://raw.githubusercontent.com/thefekete/CharRing/v1.0/charring.h
```
Then just include the charring.h file in your project and add charring.o to the objects in your makefile.

## Basic Usage
```c
#include <stdio.h>
#include "charring.h"  // include the header

int main()
{
    // Create a buffer (64 chars here)
    CharRingBuf *my_buf = CharRing_new(64);

    // Add some chars to it
    CharRing_putchar(my_buf, 'A');
    CharRing_putchar(my_buf, 'B');
    CharRing_putchar(my_buf, 'C');

    // Read them back
    while (CharRing_available(my_buf)) {
        putchar(CharRing_getchar(my_buf));
    }
    putchar('\n');

    // Don't forget this!
    CharRing_free(my_buf);
}
```
