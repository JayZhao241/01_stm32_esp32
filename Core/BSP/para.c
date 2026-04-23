#include "para.h"
#include "main.h"
#include "tim.h"
#include <stdint.h>

BASE_T led;
KEY_T key[4];

/*--------------------一些底层函数------------------*/
void delay_us(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim7, 0);
    while (__HAL_TIM_GET_COUNTER(&htim7)<us);
}
