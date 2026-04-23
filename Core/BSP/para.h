#ifndef PARA_H
#define PARA_H

#include <stdint.h>
#include <stdio.h>

typedef struct
{
    uint32_t tick;
}BASE_T;
extern BASE_T led;

// KEY
typedef struct
{
    uint8_t judge;
    uint8_t state;
    uint8_t press;
}KEY_T;
extern KEY_T key[4];

/*--------------------一些底层函数------------------*/
void delay_us(uint16_t us);

#endif // !PARA_H
