#include "led.h"
#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>

uint8_t led_control;

void LED_Sync()
{
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOF, (led_control<<9), GPIO_PIN_RESET);
}

void LED_Disp(uint8_t led_num, uint8_t led_state)
{
    if (led_state==1) {
        led_control|=(0x01<<(led_num-1));
    }
    else if (led_state==0) {
        led_control&=~(0x01<<(led_num-1));
    }

    LED_Sync();
}

void LED_Toggle(uint8_t led_num)
{
    if (HAL_GetTick()-led.tick<100)
    {
        return;
    }
    led.tick=HAL_GetTick();
    led_control^=(0x01<<(led_num-1));

    LED_Sync();
}

void LED_Proc()
{
    LED_Toggle(1);
}
