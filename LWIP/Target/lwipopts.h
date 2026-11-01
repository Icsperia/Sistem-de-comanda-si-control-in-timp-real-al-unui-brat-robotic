#ifndef __LWIPOPTS__H__
#define __LWIPOPTS__H__

#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* STM32CubeMX Specific Parameters */
#define WITH_RTOS 1
#undef LWIP_PROVIDE_ERRNO

/* Dezactivează checksum-ul hardware pentru a preveni aruncarea pachetelor ICMP de către Windows */
#define CHECKSUM_BY_HARDWARE 0

#define MEM_ALIGNMENT 4

/* LwIP folosește heap-ul intern din BSS alocat de linker */
// #define LWIP_RAM_HEAP_POINTER 0x20048000

#define LWIP_ETHERNET 1
#define LWIP_ARP 1
#define LWIP_ICMP 1
#define LWIP_RAW 1

#define LWIP_DNS_SECURE 7
#define TCP_SND_QUEUELEN 9
#define TCP_SNDLOWAT 1071
#define TCP_SNDQUEUELOWAT 5
#define TCP_WND_UPDATE_THRESHOLD 536
#define LWIP_NETIF_LINK_CALLBACK 1

#define TCPIP_THREAD_STACKSIZE 1024
#define TCPIP_THREAD_PRIO osPriorityNormal
#define TCPIP_MBOX_SIZE 6

#define SLIPIF_THREAD_STACKSIZE 1024
#define SLIPIF_THREAD_PRIO 3

#define DEFAULT_THREAD_STACKSIZE 1024
#define DEFAULT_THREAD_PRIO 3
#define DEFAULT_UDP_RECVMBOX_SIZE 6
#define DEFAULT_TCP_RECVMBOX_SIZE 6
#define DEFAULT_ACCEPTMBOX_SIZE 6
#define RECV_BUFSIZE_DEFAULT 2000000000

#define LWIP_STATS 0

/* Generare și verificare software pentru toate protocoalele */
#define CHECKSUM_GEN_IP    0
#define CHECKSUM_GEN_UDP   0
#define CHECKSUM_GEN_TCP   0
#define CHECKSUM_GEN_ICMP  0
#define CHECKSUM_GEN_ICMP6 0

#define CHECKSUM_CHECK_IP   0
#define CHECKSUM_CHECK_UDP  0
#define CHECKSUM_CHECK_TCP  0
#define CHECKSUM_CHECK_ICMP 0
#define CHECKSUM_CHECK_ICMP6 0

/* USER CODE BEGIN 1 */
#undef MEM_SIZE
#define MEM_SIZE (16*1024)
/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /* __LWIPOPTS__H__ */
