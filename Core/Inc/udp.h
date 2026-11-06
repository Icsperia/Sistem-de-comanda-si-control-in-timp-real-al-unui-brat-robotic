#ifndef __UDP__
#define __UDP__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "udp.h"
#include"lwip/ip_addr.h"
#include "lwip/pbuf.h"
#include "lwip/opt.h"
#include "lwip/udp.h"
/* USER CODE BEGIN Includes */

void udpServer_init(void);
void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
//void udpClient_connect(void);
//
//void udp_receive_callback(void*arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
//
//void HALT_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
//
//static void udpClient_send(void);
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */



/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */
