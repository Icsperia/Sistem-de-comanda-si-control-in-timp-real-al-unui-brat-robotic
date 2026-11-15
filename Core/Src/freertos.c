/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lwip/netif.h"
#include "lwip/ip4_addr.h"
#include "ethernetif.h"
#include "netif/etharp.h"
#include "adc.h"
#include <stdio.h>
#include "udp.h"
#include "lwip.h"
#include "constants.h"
#include "inverse_kinematic.h"
#include "ssd1306.h"
#include "i2c.h"
extern struct netif gnetif;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct{
float x1, y1, x2,y2;
uint32_t ts;
}Joysticks;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
QueueHandle_t QueueJoysticks;
QueueHandle_t QueueIK;



extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart3;
extern ADC_HandleTypeDef hadc3;
extern ETH_HandleTypeDef heth;
extern I2C_HandleTypeDef hi2c1;
extern volatile uint32_t dbg_rx_isr, dbg_rx_pkts, dbg_tx_calls, dbg_tx_ok;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId ADC_ReadingsHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
float Read_Analogic_Pin(ADC_HandleTypeDef *hadc, uint32_t channel);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartAdcReadings(void const * argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	 QueueJoysticks = xQueueCreate(1, sizeof(Joysticks));
	 QueueIK = xQueueCreate(1, sizeof(joint_angles));
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 1024);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of ADC_Readings */
  osThreadDef(ADC_Readings, StartAdcReadings, osPriorityNormal, 0, 512);
  ADC_ReadingsHandle = osThreadCreate(osThread(ADC_Readings), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for LWIP */
  MX_LWIP_Init();
  /* USER CODE BEGIN StartDefaultTask */
  osDelay(2000);
 udpServer_init();
 printf("SUCCES: OLED inițializat cu succes!\r\n");
 uint8_t init_res = ssd1306_Init(&hi2c1);
   if (init_res != 0) {
       printf("EROARE I2C: ssd1306_Init a eșuat (Cod: %d)\r\n", init_res);
   } else {
       printf("SUCCES: OLED inițializat cu succes!\r\n");

       ssd1306_Fill(Black);
       ssd1306_SetCursor(0, 0);
       ssd1306_WriteString("OLED Ready", Font_7x10, White);
       ssd1306_UpdateScreen(&hi2c1);
   }
	  for(;;)
	    {
	    	// MX_LWIP_Process();
	    	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);   // LED albastru
	      osDelay(200);

	      Joysticks test;
	      joint_angles test1;
//	      if (++cnt >= 5)
//	      {
//	        cnt = 0;
//	        printf("rxISR=%lu rxPkts=%lu txCalls=%lu txOk=%lu MMCtx=%lu MMCcrcErr=%lu\r\n",
//	               (unsigned long)dbg_rx_isr,  (unsigned long)dbg_rx_pkts,
//	               (unsigned long)dbg_tx_calls, (unsigned long)dbg_tx_ok,
//	               (unsigned long)heth.Instance->MMCTGFCR,
//	               (unsigned long)heth.Instance->MMCRFCECR);

//	   if(xQueuePeek(QueueJoysticks, &test,0)==pdTRUE){
//		   printf("X1=%.2f Y1=%.2f X2=%.2f Y2=%.2f\r\n",
//		         test.x1, test.y1, test.x2, test.y2);
//	   }
////
//		   if( xQueuePeek(QueueIK, &test1, 0)==pdTRUE){
//			   printf("base=%.2f elbow=%.2f shoulder=%.2f\r\n",
//					   test1.base, test1.elbow, test1.shoulder);
//}

		   osDelay(200);

	   //


	    //}


  /* USER CODE END StartDefaultTask */
}
}
/* USER CODE BEGIN Header_StartAdcReadings */
/**
* @brief Function implementing the ADC_Readings thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAdcReadings */
void StartAdcReadings(void const * argument)
{
  /* USER CODE BEGIN StartAdcReadings */

  osThreadSetPriority(NULL, osPriorityLow);

  Joysticks joysticks;
  joint_angles joint;
 // joint_angles  angles;
  /* Infinite loop */
  for(;;)
  {

	 float b_x1 =  Read_Analogic_Pin(&hadc1, ADC_CHANNEL_3);
	 float b_y1 =  Read_Analogic_Pin(&hadc1, ADC_CHANNEL_10);
	 float b_x2 =  Read_Analogic_Pin(&hadc3, ADC_CHANNEL_13);
	 float b_y2 =  Read_Analogic_Pin(&hadc3, ADC_CHANNEL_9);

//
//
//	joysticks.x1  = Read_Analogic_Pin(&hadc1, ADC_CHANNEL_3);
//    joysticks.y1 = Read_Analogic_Pin(&hadc1, ADC_CHANNEL_10);
//    joysticks.x2  = Read_Analogic_Pin(&hadc3, ADC_CHANNEL_13);
//    joysticks.y2  = Read_Analogic_Pin(&hadc3, ADC_CHANNEL_9);

	     joysticks.x1  = map(b_x1, 0.0f, 3.3f, -82.0f, 82.0f);
	     joysticks.y1  = map(b_y1, 0.0f, 3.3f, -128.0f, 128.0f);
	     joysticks.x2  = map(b_x2, 0.0f, 3.3f, -138.0f,138.0f );
	     joysticks.y2  = map(b_y2, 0.0f, 3.3f, -138.0f,138.0f );
	 joysticks.ts = xTaskGetTickCount();



    joint = inverse_kinematic(PI, arm_base, v_offset, vertical_articulation, horizontal_articulation, joysticks.x1,  joysticks.y1,  joysticks.x2);
    joint.tick = xTaskGetTickCount();
    osDelay(200);
//    printf("A0 (PA3): %.2f V | A1 (PC0): %.2f V | A3 (PF3): %.2f V\r\n",
//    voltaj, voltaj1, voltaj2);

//
//joint.base = joints.base_angle;
//joint.shoulder = joints.shoulder_angle;
//joint.elbow = joints.elbow_angle;
//joint.tick = xTaskGetTickCount();

    xQueueOverwrite(QueueIK, &joint);
    xQueueOverwrite(QueueJoysticks, &joysticks);
    osDelay(200);


  }
  /* USER CODE END StartAdcReadings */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
float Read_Analogic_Pin(ADC_HandleTypeDef *hadc, uint32_t channel){
  ADC_ChannelConfTypeDef sConfig = {0};
  uint32_t raw_value = 0;
  float voltage = 0.0f;
  sConfig.Channel = channel;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
  if(HAL_ADC_ConfigChannel(hadc, &sConfig) != HAL_OK){
    return -1.0f;
  }
  HAL_ADC_Start(hadc);
  if(HAL_ADC_PollForConversion(hadc, 10) == HAL_OK){
    raw_value = HAL_ADC_GetValue(hadc);
    voltage = ((float)raw_value * 3.3f) / 4095.0f;
  }
  HAL_ADC_Stop(hadc);
  return voltage;
}

int _write(int file, char *ptr, int len)
{
  HAL_UART_Transmit(&huart3, (uint8_t *)ptr, len, HAL_MAX_DELAY);
  return len;
}
/* USER CODE END Application */

