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
#include "udp.h"
#include"lwip/ip_addr.h"
#include "lwip/udp.h"
#include "lwip/pbuf.h"
#include "lwip/opt.h"
#include "string.h"
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

void udpServer_init(void)
{
    struct udp_pcb *upcb;
    err_t err;

    /* 1. Create a new UDP control block */
    upcb = udp_new();

    /* 2. Bind the upcb to the STM32 static IP and port 7 */
    ip_addr_t myIPADDR;
    IP_ADDR4(&myIPADDR, 192, 168, 1, 100);

    err = udp_bind(upcb, &myIPADDR, 3333);

    /* 3. Register the receive callback if bind succeeded */
    if(err == ERR_OK)
    {
        udp_recv(upcb, udp_receive_callback, NULL);
    }
    else
    {
        udp_remove(upcb);
    }
}

//void udpServer_init(void){
//	struct udp_pcb *upcb;
//	err_t err;
//
//
//	upcb = udp_new();
//
////	ip_addr_t myIPADDR;
////	IP_ADDR4(&myIPADDR, 192, 168, 1, 100);
//
//	err = udp_bind(upcb, IP_ADDR_ANY, 3333);
//
//
//	if (err == ERR_OK) {
//	        udp_recv(upcb, udp_receive_callback, NULL);
//	        printf("UDP Server listening on port 3333\r\n");
//	    } else {
//	        printf("UDP Bind Error: %d\r\n", (int)err);
//	        udp_remove(upcb);
//	    }
//
//
//
//}
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
void udp_receive_callback(void *arg, struct udp_pcb *upcb,
                           struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    struct pbuf *txBuf;

    /* Build the reply string using the received payload */
    char buf[100];
    int len = sprintf(buf, "Hello %s MOI BAG PUNGI\n", (char *)p->payload);

    /* Allocate a pbuf for the reply */
    txBuf = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);

    /* Copy the reply data into the pbuf */
    pbuf_take(txBuf, buf, len);

    /* Set the client as the destination and send */
    udp_connect(upcb, addr, port);
    udp_send(upcb, txBuf);

    /* Disconnect so the server is ready for the next client */
    udp_disconnect(upcb);

    /* Free both buffers — never skip this */
    pbuf_free(txBuf);
    pbuf_free(p);
}


/////////////
//void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
//{
//
//    printf("UDP RX: %d bytes from port %u\r\n", (int)p->len, (unsigned int)port);
//
//    char buf[100];
//    int len = snprintf(buf, sizeof(buf), "Hello %.*s from Radu Adrian Mario\r\n", (int)p->len, (char *)p->payload);
//
//    if (len > 0) {
//        struct pbuf *txBuf = pbuf_alloc(PBUF_TRANSPORT, (u16_t)len, PBUF_RAM);
//        if (txBuf != NULL) {
//            pbuf_take(txBuf, buf, (u16_t)len);
//            err_t err = udp_sendto(upcb, txBuf, addr, port);
//            printf("UDP TX: err=%d, len=%d\r\n", (int)err, len);
//            pbuf_free(txBuf);
//        }
//    }
//
//    pbuf_free(p);
//}





//udp_connect(upcb, addr, port);
//udp_send(upcb, txBuf);
//
//udp_disconnect(upcb);







//void udpClient_connect(void){
//	err_t err;
//
//	upcb = udp_new();
//
//	ip_addr_t myIPADDR;
//	IP_ADDR4(&myIPaddr, 192, 168, 1, 100);
//	udp_bind(upcb, &myIPADDR, 8);
//
//	ip_addr_t DestIPaddr;
//	IP_ADDR4(&DesrIPaddr, 192, 168, 1 ,50);
//	err = udp_connect(upcb, &DestIPaddr, 7);
//
//	if(err = ERR_OK){
//udpClient_send();
//
//udp_recv(upcb, udp_receive_callback, NULL);
//
//	}
//
//}
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in cmsis_os2.c) */

  /* Start scheduler */

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

//void udp_receive_callback(void*arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port){
//
//	strncpy(buffer, (char*)p->payload, p->len);
//
//	counter++;
//
//	pbuf_free(p);
//
//
//}

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
//static void udpClient_send(void){
//struct pbuf *txBuf;
//chat data[100];
//
//int len = sprintf(data, "*sending UDP client message %d", counter);
//
//txBuf = pbuf_alloc (PBUF_TRANSPORT, len, PBUF_RAM);
//
//if(txBuf != NULL){
//	pbuf_take(txBuf, data, len);
//
//	udp_send(upcb, txbuf);
//
//	pbuf_free(txBuf);
//}
//
//}

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
