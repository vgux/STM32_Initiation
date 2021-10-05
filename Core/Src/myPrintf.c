#include <myPrintf.h>

void myPrintf(uint8_t * text)
{
	HAL_UART_Transmit(&huart2, text, strlen(text), 1000);
}
