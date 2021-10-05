/*
 * myPrintf.h
 *
 *  Created on: Sep 21, 2021
 *      Author: user
 */
#ifndef INC_STDIO_H_
#include <stdio.h>
#endif

#ifndef INC_STRING_H_
#include <string.h>
#endif

#ifndef INC_STM32F4XX_HAL_H_
#include <stm32f4xx_hal.h>
#endif

extern UART_HandleTypeDef huart2;

void myPrintf(uint8_t * text);
