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



extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart3;
extern ADC_HandleTypeDef hadc3;
extern ETH_HandleTypeDef heth;
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
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 1024);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of ADC_Readings */
  osThreadDef(ADC_Readings, StartAdcReadings, osPriorityNormal, 0, 1024);
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
  /* 1. Task-ul a pornit */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET); // LED Rosu aprins


  MX_LWIP_Init();
  printf("tasks: %u | free heap: %u | min free: %u\r\n",
         (unsigned)uxTaskGetNumberOfTasks(),
         (unsigned)xPortGetFreeHeapSize(),
         (unsigned)xPortGetMinimumEverFreeHeapSize());

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);  // LED Verde aprins

  /* USER CODE BEGIN StartDefaultTask */



  osDelay(2000);
  Joysticks test;

  for(;;)
  {
	  uint32_t cnt = 0;
	    for(;;)
	    {
	      HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);   // LED albastru
	      osDelay(400);

	      if (++cnt >= 5)
	      {
	        cnt = 0;
	        printf("rxISR=%lu rxPkts=%lu txCalls=%lu txOk=%lu MMCtx=%lu MMCcrcErr=%lu\r\n",
	               (unsigned long)dbg_rx_isr,  (unsigned long)dbg_rx_pkts,
	               (unsigned long)dbg_tx_calls, (unsigned long)dbg_tx_ok,
	               (unsigned long)heth.Instance->MMCTGFCR,
	               (unsigned long)heth.Instance->MMCRFCECR);

	   if(xQueuePeek(QueueJoysticks, &test,0)==pdTRUE){
		   printf("X1=%.2f Y1=%.2f X2=%.2f Y2=%.2f\r\n",
		         test.x1, test.y1, test.x2, test.y2);
		  osDelay(200);

	   }

	      }
	    }
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
  /* Prioritate mica, ca sa nu intarzie thread-urile LwIP/Ethernet */
  osThreadSetPriority(NULL, osPriorityLow);

  Joysticks joysticks;

  /* Infinite loop */
  for(;;)
  {
    joysticks.x1  = Read_Analogic_Pin(&hadc1, ADC_CHANNEL_3);
    joysticks.y1 = Read_Analogic_Pin(&hadc1, ADC_CHANNEL_10);
    joysticks.x2  = Read_Analogic_Pin(&hadc3, ADC_CHANNEL_13);
    joysticks.y2  = Read_Analogic_Pin(&hadc3, ADC_CHANNEL_9);
    joysticks.ts = xTaskGetTickCount();

//    printf("A0 (PA3): %.2f V | A1 (PC0): %.2f V | A3 (PF3): %.2f V\r\n",
//           voltaj, voltaj1, voltaj2);

    xQueueOverwrite(QueueJoysticks, &joysticks);
    osDelay(10);


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
