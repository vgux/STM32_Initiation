/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int __io_putchar(int ch) {
	HAL_UART_Transmit(&huart2, &ch, 1, 1000);
}

void ledBlinker(void);
void varSizePrint(void);
void pointerIncrementPrint(void);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  struct noeud* arbreHuffman[256];
  struct noeud* racine;
  uint8_t 	texte[]="aaaabbbccd";
  uint8_t 	texteCompress[TAILLE_MAX_COMPRESS] = {0};
  uint32_t 	tabCaractere[256] = {0};
  uint32_t	nbrCaractereTotal = 0;
  uint32_t	nbrCaractereDifferent = 0;

  uint8_t tabEntete[256] = {0};

  uint16_t tailleTableauHuffman = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */





  /*****************************************************************************************
   * 									Partie 2 TP										   *
   *****************************************************************************************/

	  occurence(texte, tabCaractere);
	  occurencePrint(tabCaractere);

	  tailleTableauHuffman = creerFeuille(arbreHuffman, tabCaractere);
	  triArbre(arbreHuffman, tailleTableauHuffman);
	  afficherTabArbreHuffman (arbreHuffman, tailleTableauHuffman);

	  printf("\nCreation racine\n");

	  racine = creerRacine(arbreHuffman, tailleTableauHuffman);

	  printf("\nParcours arbre : Affichage caractere et occurence\n");
	  parcourirArbre(racine);
	  //free(arbreHuffman); // a corriger 2.3.6

	  printf("\n");
	  creerCode(racine, 0, 0);

	  nbrCaractereTotal = strlen((unsigned char*) texte);
	  printf("\n\n\nnbrCaractereTotal = %d\n", nbrCaractereTotal);

	  nbrCaractereDifferent = obtenirNbCarDifferent(tabCaractere);
	  printf("\nnbrCaractereDifferent = %d\n", nbrCaractereDifferent);

	  uint16_t tailleTexteCompresse = textCompressor(racine, texte, texteCompress);
	  printf("\nTaille texte compresse = %d\n\n", tailleTexteCompresse);

	  generateurEntete(tabEntete, racine, tailleTexteCompresse, nbrCaractereTotal, tabCaractere);


	  //HAL_UART_Receive_IT(&huart2, pData, Size);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

	  /*****************************************************************************************
	   * 									Partie 1 TP										   *
	   *****************************************************************************************/

	  /*ledBlinker();

	  uint8_t str[15];

	  uint32_t i = 888;
	  sprintf(str, "%d\n", i);
	  myPrintf(str);

	  printf(str);

	  varSizePrint();
	  pointerIncrementPrint();*/


    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void ledBlinker(void) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
	HAL_Delay(500);
}

void varSizePrint(void) {
	  //Affichage de la taille de chaque type de variable
	  printf("char size = %d\n", sizeof(char));
	  printf("int size = %d\n", sizeof(int));
	  printf("unsigned int size = %d\n", sizeof(unsigned int));
	  printf("long int size = %d\n", sizeof(long int));
	  printf("unsigned long int size = %d\n", sizeof(unsigned long int));
	  printf("uint8_t size = %d\n", sizeof(uint8_t));
	  printf("int8_t size = %d\n", sizeof(int8_t));
	  printf("uint16_t size = %d\n", sizeof(uint16_t));
	  printf("int16_t size = %d\n", sizeof(int16_t));
	  printf("uint32_t size = %d\n", sizeof(uint32_t));
	  printf("int32_t size = %d\n", sizeof(int32_t));
	  printf("uint64_t size = %d\n", sizeof(uint64_t));
	  printf("int64_t size = %d\n", sizeof(int64_t));
	  printf("float size = %d\n", sizeof(float));
	  printf("double size = %d\n", sizeof(double));
	  printf("long double size = %d\n", sizeof(long double));


}
void pointerIncrementPrint(void) {
	  //Op??rations sur les pointeurs pour observer le changement dans les adresses point??es
	  uint8_t *pUint8 = 0;
	  uint8_t tabUint8[3] = {0};
	  pUint8 = &tabUint8;

	  printf("pUint8 = %d\n", pUint8);
	  pUint8++;
	  printf("pUint8 + 1 = %d\n", pUint8);

	  uint16_t *pUint16 = 0;
	  uint16_t tabUint16[3] = {0};
	  pUint16 = &tabUint16;

	  printf("pUint16 = %d\n", pUint16);
	  pUint16++;
	  printf("pUint16 + 1 = %d\n", pUint16);

	  uint32_t *pUint32 = 0;
	  uint32_t tabUint32[3] = {0};
	  pUint32 = &tabUint32;

	  printf("pUint32 = %d\n", pUint32);
	  pUint32++;
	  printf("pUint32 + 1 = %d\n", pUint32);


	  uint64_t *pUint64 = 0;
	  uint64_t tabUint64[3] = {0};
	  pUint64 = &tabUint64;

	  printf("pUint64 = %d\n", pUint64);
	  pUint64++;
	  printf("pUint64 + 1 = %d\n", pUint64);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
