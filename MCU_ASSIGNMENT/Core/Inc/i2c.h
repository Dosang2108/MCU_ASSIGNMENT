/*
 * i2c.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Sang
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "main.h"

#define __I2C_DELAY 10

 void I2C_init(GPIO_TypeDef *SDA_Port,uint16_t SDA_pin,GPIO_TypeDef *SCL_Port,uint16_t SCL_pin);
 void SDA_in(void);
 void I2C_Delay(unsigned int time);
 void SDA_out(void);
 void I2C_Start(void);
 void I2C_STOP(void);
 unsigned char I2C_CheckAck(void);
 void I2C_Write(unsigned char Data);
 unsigned char I2C_Read(void);


#endif /* INC_I2C_H_ */
