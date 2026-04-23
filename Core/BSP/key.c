#include "key.h"
#include "stm32f407xx.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>
#include <stdio.h>

void KEY_Time()
{
    key[0].state=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);
    key[1].state=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3);
    key[2].state=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);
    key[3].state=HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

    for (uint8_t i = 0; i < 4; i++)
    {
        switch (key[i].judge) {
            case 0:
                if (key[i].state==0) {
                    key[i].judge=1;
                }
                break;
            case 1:
                if (key[i].state==0) {
                    key[i].judge=2;
                }
                break;
            case 2:
                if (key[i].state==1) {
                    key[i].press=1;
                    key[i].judge=0;
                }
                break;
            default:
                break;
        }
    }
}
void KEY_Proc()
{
    if (key[0].press==1)
    {
        printf("key0 pressed\r\n");
        key[0].press=0;
    }
}
