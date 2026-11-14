/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "clamp.h"
#include <arm_math.h>
#include <math.h>
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

  /* USER CODE BEGIN 1 */
float minss(float a , float b){
__mm_store_ss(&a, _mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));

return a;

}

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/


  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
;

  /* Enable D-Cache---------------------------------------------------------*/
  //SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */


  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */


  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  /* USER CODE BEGIN 2 */

float maxss(float a, float b){

	_mm_store_ss(&a, _mm_max_ss(_mm_set_ss(a),_mm_set_ss(b)));

	return a;
}






  /* USER CODE END 2 */

  /* Call init function for freertos objects (in cmsis_os2.c) */

  /* Start scheduler */

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

float clamp(float value , float a , float b){
_mm_store_ss(&val, _mm_min_ss(_mm_max_ss(_mm_set_ss(val),_mm_set_ss(minval))));


	return val;
}

  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */


  /** Configure LSE Drive Capability


  /** Configure the main internal regulator output voltage
  */

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */


  /** Activate the Over-Drive mode
  */

  /** Initializes the CPU, AHB and APB buses clocks
  */


/* USER CODE BEGIN 4 */
//void HALT_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
//	udpClient_send();
//
//}


/* USER CODE END 4 */

/* USER CODE BEGIN 5 */

/* USER CODE END 5 */

 /* MPU Configuration */


  /* Disables the MPU */


  /** Initializes and configures the Region and the memory to be protected
  */

  /* Enables the MPU */


/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */

  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */

  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */

  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */


  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
 /* USE_FULL_ASSERT */
