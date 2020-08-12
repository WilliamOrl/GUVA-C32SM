#include <GUVA-C32SMB.h>

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
#define No_op 0b00000000
#define UVA_op 0b00010000
#define Not_use 0b00100000
#define Normal_mode 0b00000000
#define Low_powermode 0b00000001
#define Auto_shutdow_mode 0b0000010
#define Shutdown_mode 0b00000011

// Sensor Resolutions
#define Res_800 0b00000000
#define Res_400 0b00000001
#define Res_200 0b00000010
#define Res_100 0b00000011


//Sensor Range
#define Range_x1 0b00000000
#define Range_x2 0b00000001
#define Range_x4 0b00000010
#define Range_x8 0b00000011
#define Range_x16 0b00000100
#define Range_x32 0b00000101
#define Range_x64 0b00000110
#define Range_x128 0b00000111

//sleep duration
#define Time_2 0b00000000
#define Time_4 0b00000001
#define Time_8 0b00000010
#define Time_16 0b00000011
#define Time_32 0b00000100
#define Time_64 0b00000101
#define Time_128 0b00000110
#define Time_256 0b00000111

//reset
#define RESET 0xA5


//===========================================================================
//							Sensor Initialization
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


//===========================================================================
//								Sensor Range
//===========================================================================

HAL_StatusTypeDef Range_GUVA_C32 (I2C_HandleTypeDef * hi2c, uint8_t RANGE){


	return HAL_OK;
}


//===========================================================================
//						Sensor Sleep Duration
//===========================================================================

HAL_StatusTypeDef Sleep_GUVA_C32(I2C_HandleTypeDef * hi2c, uint8_t TIME){

	uint8_t buf[2];
	HAL_StatusTypeDef ret;

	buf [0] = MODE_CTL_GUVA;
	buf [1] = TIME;

	ret = HAL_I2C_Master_Transmit(hi2c, REG_GUVA, buf, 2, 10);
	if (ret != HAL_OK){
		return ret;
	}
	return HAL_OK;
}

//===========================================================================
//						Sensor Reset
//===========================================================================

HAL_StatusTypeDef Reset_GUVA_C32 (I2C_HandleTypeDef * hi2c){

	uint8_t buf[2];
	HAL_StatusTypeDef ret;

	buf [0] = SOFT_RESET_GUVA;
	buf [1] = RESET;

	ret = HAL_I2C_Master_Transmit(hi2c, REG_GUVA, buf, 2, 10);
	if (ret != HAL_OK){
		return ret;
	}
	return HAL_OK;
}


//===========================================================================
//							Sensor Receive
//===========================================================================

HAL_StatusTypeDef Receive_GUVA_C32 (I2C_HandleTypeDef * hi2c, uint8_t RANGE,float* UVA){

	uint8_t buf[2];
	HAL_StatusTypeDef ret;

	buf [0] = RANGE_GUVA;
	buf [1] = RANGE;

		ret = HAL_I2C_Master_Transmit(hi2c, REG_GUVA, buf, 2, 10);
		if (ret != HAL_OK){
			return ret;
		}
		else{
			uint8_t save_buf;
			uint16_t UVA_RES;


			buf[0] = UVA_LSB_GUVA;

			ret = HAL_I2C_Master_Transmit(hi2c, REG_GUVA, buf, 1, 10);
			if(ret != HAL_OK){
				return ret;
			}
				else{
					ret = HAL_I2C_Master_Receive(hi2c, REG_GUVA, buf, 1, 10);
					if(ret != HAL_OK){
						return ret;
					}
					else{
						save_buf = buf[0];
						buf[0] = UVA_MSB_GUVA;

						ret = HAL_I2C_Master_Transmit(hi2c, REG_GUVA, buf, 1, 10);
						if(ret != HAL_OK){
							return ret;
						}
							else{
								ret = HAL_I2C_Master_Receive(hi2c, REG_GUVA, buf, 1, 10);
								if(ret != HAL_OK){
									return ret;
								}
								else{
									UVA_RES = buf[0] + save_buf;		// Da uma olhada pra ver se isso aqui funciona
									*UVA = Converter (UVA_RES, RANGE);
								}
							}
						}
					}

			return HAL_OK;
		}
}

//===========================================================================
//						Converter
//===========================================================================

float Converter (uint16_t UVA_RES, uint8_t RANGE){
	float res;

	if(RANGE == Range_x1){
		res = ((UVA_RES*100)/1);
	}
		else if(RANGE == Range_x2){
			res = ((UVA_RES*100)/2);
		}
			else if(RANGE == Range_x4){
				res = ((UVA_RES*100)/4);
			}
				else if(RANGE == Range_x8){
					res = ((UVA_RES*100)/8);
				}
					else if(RANGE == Range_x16){
						res = ((UVA_RES*100)/16);
					}
						else if(RANGE == Range_x32){
							res = ((UVA_RES*100)/32);
						}
							else if(RANGE == Range_x64){
								res = ((UVA_RES*100)/64);
							}
								else if(RANGE == Range_x128){
									res = ((UVA_RES*100)/128);
								}
	return res;
}



