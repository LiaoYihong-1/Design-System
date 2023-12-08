/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <string.h>
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
 UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART6_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t codes[8];
uint8_t pointer_read = 0;
uint8_t pointer_write = 0;
uint8_t mode = 'i';
_Bool received = 0;
_Bool changed = 0;
void delay_analog(uint32_t duration)
  {
    uint32_t startTime = HAL_GetTick();
    while ((HAL_GetTick() - startTime) < duration)
    {
    }
  }
void blink_short(uint8_t time){
	while(time > 0){
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
        HAL_Delay(100);
		time = time - 1;
	}
}
void blink_long(uint8_t time){
	while(time > 0){
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
        HAL_Delay(1000);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
        HAL_Delay(1000);
		time = time - 1;
	}
}
//after receiving code will play it
void blink_code(uint32_t code){
	char string[5] = {0};
	itoa(code,string,10);
	int len = strlen(string);
	int p = 0;
	while(len > 0){
		char c = string[p];
		//change mode between interrupt and polling
		if(c=='3'){
			changed = 1;
		}else if(c=='1'){
			blink_long(1);
		}else if(c=='2'){
			blink_short(1);
		}
		len = len - 1;
		p = p + 1;
	}
}
void send_char(uint8_t* c){
	if(mode == 'p'){
		HAL_UART_Transmit(&huart6,c,1,10);
	}
	else if(mode == 'i'){
		HAL_UART_Transmit_IT(&huart6,c,1);
	}
}
void send(uint32_t code){
		// 2-short, 1-long
	    switch(code){
	    case 21:
	    	send_char((uint8_t*)"a");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"a",1);
	        break;
	    case 1222:
	    	send_char((uint8_t*)"b");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"b",1);
	        break;
	    case 1212:
	    	send_char((uint8_t*)"c");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"c",1);
	        break;
	    case 122:
	    	send_char((uint8_t*)"d");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"d",1);
	        break;
	    case 2:
	    	send_char((uint8_t*)"e");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"e",1);
	        break;
	    case 2212:
	    	send_char((uint8_t*)"f");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"f",1);
	        break;
	    case 112:
	    	send_char((uint8_t*)"g");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"g",1);
	        break;
	    case 2222:
	    	send_char((uint8_t*)"h");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"h",1);
	        break;
	    case 22:
	    	send_char((uint8_t*)"i");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"i",1);
	        break;
	    case 2111:
	    	send_char((uint8_t*)"j");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"j",1);
	        break;
	    case 121:
	    	send_char((uint8_t*)"k");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"k",1);
	        break;
	    case 2122:
	    	send_char((uint8_t*)"l");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"l",1);
	        break;
	    case 11:
	    	send_char((uint8_t*)"m");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"m",1);
	        break;
	    case 12:
	    	send_char((uint8_t*)"n");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"n",1);
	        break;
	    case 111:
	    	send_char((uint8_t*)"o");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"o",1);
	        break;
	    case 2112:
	    	send_char((uint8_t*)"p");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"p",1);
	        break;
	    case 1121:
	    	send_char((uint8_t*)"q");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"q",1);
	        break;
	    case 212:
	    	send_char((uint8_t*)"r");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"r",1);
	        break;
	    case 222:
	    	send_char((uint8_t*)"s");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"s",1);
	        break;
	    case 1:
	    	send_char((uint8_t*)"t");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"t",1);
	        break;
	    case 221:
	    	send_char((uint8_t*)"u");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"u",1);
	        break;
	    case 2221:
	    	send_char((uint8_t*)"v");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"v",1);
	        break;
	    case 211:
	    	send_char((uint8_t*)"w");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"w",1);
	        break;
	    case 1221:
	    	send_char((uint8_t*)"x");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"x",1);
	        break;
	    case 1211:
	    	send_char((uint8_t*)"y");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"y",1);
	        break;
	    case 1122:
	    	send_char((uint8_t*)"z");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"z",1);
	        break;
	    default:
	    	send_char((uint8_t*)"-");
	    	//HAL_UART_Transmit_IT(&huart6,(uint8_t*)"-",1);
	    	break;
	    }
 }
//encrypt received code
uint32_t encrypt(uint8_t c){
	uint32_t result = 0;
    switch(c){
    case 'a':
        result = 21;
        break;
    case 'b':
        result = 1222;
        break;
    case 'c':
        result = 1212;
        break;
    case 'd':
        result=122;
        break;
    case 'e':
        result=2;
        break;
    case 'f':
        result=2212;
        break;
    case 'g':
    	result=112;
        break;
    case 'h':
    	result=2222;
        break;
    case 'i':
    	result=22;
        break;
    case 'j':
    	result=2111;
        break;
    case 'k':
    	result=121;
        break;
    case 'l':
    	result=2212;
        break;
    case 'm':
    	result=11;
        break;
    case 'n':
    	result=12;
        break;
    case 'o':
    	result=111;
        break;
    case 'p':
    	result=2112;
        break;
    case 'q':
    	result=1121;
        break;
    case 'r':
    	result=212;
        break;
    case 's':
    	result=222;
        break;
    case 't':
    	result=1;
        break;
    case 'u':
    	result=221;
        break;
    case 'v':
    	result=2221;
        break;
    case 'w':
    	result=211;
        break;
    case 'x':
    	result=1221;
        break;
    case 'y':
    	result=1211;
        break;
    case 'z':
    	result=1122;
        break;
    case '+':
    	result=3;
    	break;
    default:
    	result='0';
    	break;
    }
    return result;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	received = 1;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  void morse(const uint8_t *code_morse)
  {
	uint32_t code = 0;
	uint32_t short_code = 2;
	uint32_t long_code = 1;
	uint32_t k = 1;
	for (uint8_t i = 0; code_morse[i] != 2; i++)
	{
	  //long Morse code
	  if (code_morse[i])
	  {
		code = code*k + long_code;
		blink_long(1);
	  }
	  //short Morse code
	  else
	  {
		code = code*k + short_code;
		blink_short(1);
	  }
	  delay_analog(2000);
	  k = k * 10;
	}
//	char s[] = "hello world\n";
//	HAL_UART_Transmit(&huart6,(uint8_t*)s,sizeof(s),10);
	send(code);
 }
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
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
  void delay_analog(uint32_t duration)
   {
	  uint32_t startTime = HAL_GetTick();
	  while ((HAL_GetTick() - startTime) < duration)
	  {
	  }
   }
  void received_chars(){
	  if(received){
		received = 0;
		int len = sizeof(codes)/sizeof(uint8_t);
		int i = 0;
		while(i<len){
			blink_code(encrypt(codes[i]));
			i = i + 1;
		}
		HAL_UART_Receive_IT(&huart6,codes,1);
	}
  }
  void mode_changed(){
	  if(changed){
		changed = 0;
		if(mode == 'i'){
			mode = 'p';
			char s [] = "Turning to poling\r\n";
			HAL_UART_Abort_IT(&huart6);
			HAL_NVIC_DisableIRQ(USART6_IRQn);
			HAL_UART_Transmit(&huart6,(uint8_t*)s,sizeof(s),10);
		}else{
			mode = 'i';
			char s [] = "Turning to interrupt\r\n";
			HAL_UART_Abort_IT(&huart6);
			HAL_NVIC_EnableIRQ(USART6_IRQn);
			HAL_UART_Transmit(&huart6,(uint8_t*)s,sizeof(s),100);
			HAL_UART_Receive_IT(&huart6,codes,1);
		}
	}
  }
	uint8_t code_morse[50];
	uint8_t last_morse_index = 0;
	uint32_t duration = 5000;
	uint32_t log_pressed_time = 2000;
	uint32_t last_time_pressed = 0;
	_Bool pressed_flag = 0;
	_Bool long_pressed_flag = 0;
	HAL_UART_Receive_IT(&huart6,codes,1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  	received_chars();
	  	mode_changed();
	  	if(mode=='p'){
			// If received 8 codes in 5s, then we can read them, else read again
			while(mode == 'p'){
				if(HAL_UART_Receive(&huart6,codes,1,1000)==HAL_OK){
					uint8_t k = 0;
					uint8_t n = sizeof(codes)/sizeof(uint8_t);
					while(k<n){
						blink_code(encrypt(codes[k]));
						k = k + 1;
					}
				}
			  	mode_changed();
			}
		}
		uint32_t time_start = HAL_GetTick();
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_RESET)
		{
		  pressed_flag = 1;
		  if (HAL_GetTick() - time_start > log_pressed_time)
		  {
			long_pressed_flag = 1;
		  }
		}
		if (pressed_flag)
		{
		  code_morse[last_morse_index] = long_pressed_flag;
		  if (long_pressed_flag)
		  {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
			delay_analog(1000);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
			delay_analog(1000);
		  }
		  else
		  {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
			delay_analog(1000);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			delay_analog(1000);
		  }
		  last_morse_index++;
		  last_time_pressed = time_start;
		  pressed_flag = 0;
		  long_pressed_flag = 0;
		}
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_SET && HAL_GetTick() - last_time_pressed > duration)
		{
		  if (last_morse_index > 0)
		  {
			code_morse[last_morse_index] = 2;
			morse(code_morse);
			last_morse_index = 0;
		  }
		}
    /* USER CODE END WHILE */

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, green_Pin|red_Pin|yellow_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : button_Pin */
  GPIO_InitStruct.Pin = button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : green_Pin red_Pin yellow_Pin */
  GPIO_InitStruct.Pin = green_Pin|red_Pin|yellow_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
