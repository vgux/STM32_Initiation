#include <myPrintf.h>

/**
  * @brief  Implementation de la fonction printf pour le STM32
  * @param  text: texte a afficher
  * @retval None
  */
void myPrintf(uint8_t * text)
{
	HAL_UART_Transmit(&huart2, text, strlen(text), 1000);
}
