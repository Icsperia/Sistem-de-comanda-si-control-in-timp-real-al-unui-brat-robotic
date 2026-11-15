#ifndef __INVERSE_KINEMATIC__
#define __INVERSE_KINEMATIC__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include <stdint.h>
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
typedef struct{
float base;
float shoulder;
float elbow;
uint32_t tick;

} joint_angles;
/* USER CODE END Private defines */



/* USER CODE BEGIN Prototypes */
joint_angles inverse_kinematic(float pi,float h_base, float offset, float h_vertical_articulation, float h_horizontal_articulation, float x_coordonate, float y_coordonate, float z_coordonate);

uint16_t deg_to_pulse(float angle);

float map (float in, float in_min, float in_max, float out_min, float out_max);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */
