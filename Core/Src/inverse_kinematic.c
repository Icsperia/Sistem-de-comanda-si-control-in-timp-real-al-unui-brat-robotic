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
#include "inverse_kinematic.h"
#include "clamp.h"
#include <math.h>
#include <stdio.h>
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
joint_angles inverse_kinematic(float pi, float h_base, float offset, float h_vertical_articulation, float h_horizontal_articulation, float x_coordonate, float y_coordonate, float z_coordonate){

	joint_angles angles;
float x = x_coordonate;
float y = y_coordonate;
float z = z_coordonate;

float  squared_x = x*x;
float squared_y = y*y;

float radius =  squared_x+squared_y;

float base_angle  = atan2f(y,x)*(180/pi);
float horizontal_radius = sqrtf(radius)- offset;

float h_vertical = z - h_base;

float squared_horizontal_radius = horizontal_radius*horizontal_radius;
float  squared_h_vertical = h_vertical * h_vertical;

float squared_direct_distance = squared_horizontal_radius + squared_h_vertical;

float direct_distance = sqrtf(squared_direct_distance);

//if(direct_distance<0.001f){
//
//	return angles;
//}

float difference_vertical_horizontal = h_vertical_articulation - h_horizontal_articulation;

//if(direct_distance > (h_vertical_articulation+h_horizontal_articulation)||direct_distance<fabsf(difference_vertical_horizontal)){
//
////daca depaseste limitele sa-si pastreze pozitia
//
//}

float cos_angle_horizontal_vertical = ((h_vertical_articulation * h_vertical_articulation +h_horizontal_articulation*h_horizontal_articulation - squared_direct_distance) /(2*h_vertical_articulation*h_horizontal_articulation));
float cos_vertical_distance =((h_vertical_articulation*h_vertical_articulation + squared_direct_distance-h_horizontal_articulation*h_horizontal_articulation)/(2*h_vertical_articulation*direct_distance));

float clamped_angle_horizontal_vertical = clampf(cos_angle_horizontal_vertical, -1 ,1);
float clamped_angel_vertical_distance = clampf(cos_vertical_distance, -1 ,1);

float elbow_angle = acosf(clamped_angle_horizontal_vertical)*(180/pi);
float h_vertical_articulation_target = acosf(clamped_angel_vertical_distance)*(180/pi);
float horizontal_target_elevation = atan2f(h_vertical,horizontal_radius)*(180/pi);


float target_shoulder = 90 -( h_vertical_articulation_target+horizontal_target_elevation);
float target_elbow = 90 - elbow_angle;



angles.base = base_angle;
angles.elbow = target_elbow;
angles.shoulder = target_shoulder;
//printf("X: %.1f, Y: %.1f, Z: %.1f | Dist: %.1f | Base: %.1f, Shoul: %.1f, Elbow: %.1f\r\n",
//       x, y, z, direct_distance, base_angle, target_shoulder, target_elbow);
return angles;


}

uint16_t deg_to_pulse(float angle){

	return(uint16_t)(500.0f*(angle * (500.0f/90.0f)));

}

float map (float in, float in_min, float in_max, float out_min, float out_max){

	float value = (in-in_min)*(out_max-out_min)/(in_max-in_min)+out_min;
	return value;


}

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/


  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/


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






  /* USER CODE END 2 */

  /* Call init function for freertos objects (in cmsis_os2.c) */

  /* Start scheduler */

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



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
