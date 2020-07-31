#ifndef LIB_GUVA_C32SM_H
#define LIB_GUVA_C32SM_H
#ifdef _cplusplus
extern "C"	{
#endif

#include "stm32f4xx_hal.h"

typedef struct _GUVAC32SM{

} GUVAC32SM;

HAL_StatusTypeDef Start_GUVA_C32 (I2C_HandleTypeDef * hi2c);
HAL_StatusTypeDef Mode_GUVA_C32 (I2C_HandleTypeDef * hi2c, uint8_t MODE, uint8_t PMODE);
HAL_StatusTypeDef Resolution_GUVA_C32 ();
HAL_StatusTypeDef Range_GUVA_C32 ();
HAL_StatusTypeDef Sleep_GUVA_C32 ();
HAL_StatusTypeDef Reset_GUVA_C32 ();
HAL_StatusTypeDef Receive_GUVA_C32 ();

#ifdef _cplusplus
}
#endif
#endif// LIB_GUVA_C32SM_H
