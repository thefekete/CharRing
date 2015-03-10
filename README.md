# CharRing

Documentation can be found [here](http://thefekete.github.io/CharRing/).

CharRing is a simple character ring/circular buffer designed for microcontrollers.

This was designed with microcontrollers in mind, but it might be useful for other purposes as well.

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
