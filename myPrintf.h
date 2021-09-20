#include <string.h>
#include <stdio.h>
#include <stm32f4xx_hal.h>

extern UART_HandleTypeDef huart2;

void myPrintf(uint8_t * text);
