/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "string.h"

TIM_HandleTypeDef htim6;

void SystemClock_Config(void);
static void MX_TIM6_Init(void);
void GPIO_Init(void);
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_TIM6_Init();
  GPIO_Init();

  HAL_TIM_Base_Start_IT(&htim6);
  while(1);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef OSC_Init;
	RCC_ClkInitTypeDef CLK_Init;

	memset(&OSC_Init, 0, sizeof(OSC_Init));
	memset(&CLK_Init, 0, sizeof(CLK_Init));

	OSC_Init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	OSC_Init.HSIState = RCC_HSI_ON;
	OSC_Init.HSICalibrationValue = 16;

	if (HAL_RCC_OscConfig(&OSC_Init) != HAL_OK) {
		Error_Handler();
	}

	CLK_Init.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|	\
						 RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	CLK_Init.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	CLK_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	CLK_Init.APB1CLKDivider = RCC_HCLK_DIV1;
	CLK_Init.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&CLK_Init, FLASH_ACR_LATENCY_0WS) != HAL_OK) {
		Error_Handler();
	}

	//HSI can not be stopped if it is used as system clock source.
	__HAL_RCC_HSI_DISABLE();

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{
	htim6.Instance = TIM6;
	htim6.Init.Prescaler = 4999;
	htim6.Init.Period = 3200-1;

	if (HAL_TIM_Base_Init(&htim6) != HAL_OK) {
		Error_Handler();
	}
}

void GPIO_Init(void) {
	GPIO_InitTypeDef gpio5;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	gpio5.Mode = GPIO_MODE_OUTPUT_PP;
	gpio5.Pin = GPIO_PIN_5;
	gpio5.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOA, &gpio5);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
