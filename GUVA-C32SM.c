#include "GUVA-C32SM.h"


static const uint8_t REG_GUVA = 0x62 << 1;
static const uint8_t REG_ID_GUVA = 0x00;
static const uint8_t MODE_GUVA = 0x01;
static const uint8_t RES_GUVA = 0x04;
static const uint8_t RANGE_GUVA = 0x05;
static const uint8_t MODE_CTL_GUVA = 0x0A;
static const uint8_t SOFT_RESET_GUVA = 0x0B;
static const uint8_t UVA_LSB_GUVA = 0x15;
static const uint8_t UVA_MSB_GUVA = 0x16;


// Sensor modes
#define No_op 0b00000000;
#define UVA_op 0b00010000;
#define Not_use 0b00100000;
#define Normal_mode 0b00000000;
#define Low_powermode 0b00000001;
#define Auto_shutdow_mode 0b0000010;
#define Shutdown_mode 0b00000011;

// Sensor Resolutions
#define Res_800 0b00000000
#define Res_400 0b00000001
#define Res_200 0b00000010
#define Res_100 0b00000011


//===========================================================================
//							Initialization of Sensor
//===========================================================================

HAL_StatusTypeDef Start_GUVA_C32 (I2C_HandleTypeDef * hi2c){
	uint8_t buf[1];
	HAL_StatusTypeDef ret;
	buf[0] = REG_ID_GUVA;

	ret = HAL_I2C_Master_Transmit(hi2c, REG_GUVA, buf, 1, 10);
	if(ret != HAL_OK){
		return ret;
	}else{
		ret = HAL_I2C_Master_Receive(hi2c, REG_GUVA, buf, 1, 10);
		if(ret != HAL_OK || buf[0] != REG_ID_GUVA){
			return HAL_ERROR;
		}
	}
	return HAL_OK;
}

//===========================================================================
//								Sensor Mode
//===========================================================================

HAL_StatusTypeDef Mode_GUVA_C32 (I2C_HandleTypeDef * hi2c, uint8_t MODE, uint8_t PMODE){
	uint8_t buf[2];
	HAL_StatusTypeDef ret;
	buf [0] = MODE_GUVA;
	buf [1] = MODE + PMODE;

	ret = HAL_I2C_Master_Transmit(hi2c, REG_GUVA, buf, 2, 10);
	if (ret != HAL_OK){
		return ret;
	}
	return HAL_OK;
}

//===========================================================================
//								Sensor Resolution
//===========================================================================

HAL_StatusTypeDef Resolution_GUVA_C32 (I2C_HandleTypeDef * hi2c, uint8_t RES){
	uint8_t buf[2];
	HAL_StatusTypeDef ret;
	buf [0] = RES_GUVA;
	buf [1] = RES;

	ret = HAL_I2C_Master_Transmit(hi2c, REG_GUVA, buf, 2, 10);
	if (ret != HAL_OK){
		return ret;
	}
	return HAL_OK;
}




