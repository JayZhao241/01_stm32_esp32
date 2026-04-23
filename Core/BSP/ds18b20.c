#include "ds18b20.h"
#include "para.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>

#define DS18B20_Pin_Port GPIOG
// __HAL_RCC_GPIOX_CLK_ENABLE();
#define DS18B20_Pin GPIO_PIN_9 // 接ds18b20的引脚，自行修改


/************************************************************ 最底层驱动***************************************************************************/

// 初始化输出
void DS18B20__DQ_Out()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // __HAL_RCC_GPIOX_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    
    GPIO_InitStruct.Pin = DS18B20_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;   // 开漏输出
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(DS18B20_Pin_Port, &GPIO_InitStruct);
}

// 初始化输入，释放DQ
void DS18B20_DQ_In()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // __HAL_RCC_GPIOX_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    
    GPIO_InitStruct.Pin = DS18B20_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;   // 输入
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(DS18B20_Pin_Port, &GPIO_InitStruct);
}

// 拉低
void DS18B20_DQ_Low()
{
    HAL_GPIO_WritePin(DS18B20_Pin_Port, DS18B20_Pin, GPIO_PIN_RESET);
}

// 读取DQ状态
uint8_t DS18B20_DQ_Read()
{
    uint8_t state=HAL_GPIO_ReadPin(DS18B20_Pin_Port, DS18B20_Pin);

    return state;
}

/*-------------------------进入正题---------------------*/
/*
@brief 让主机识别到设备
*/
uint8_t DS18B20_Reset()
{
    uint8_t presence;

    // 以下根据时序图
    DS18B20__DQ_Out(); // 主机准备驱动总线
    DS18B20_DQ_Low(); // 先拉低
    delay_us(500); // 等待500μs
    DS18B20_DQ_In(); // 释放
    delay_us(70); // 等待ds18b20拉低总线，表示存在

    presence=(DS18B20_DQ_Read()==0)? 1:0; // 拉低表示存在，返回1
    DS18B20_DQ_Low(); // 先拉低
    delay_us(200); // 等待200
    DS18B20_DQ_In(); // 释放

    delay_us(430); // 等待结束

    return presence;
}
