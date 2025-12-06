/*
 * i2c.c
 *
 *  Created on: Dec 6, 2025
 *      Author: Lolle
 */


#include "i2c.h"

static struct{
   GPIO_TypeDef *SDA_GPIO;
   uint16_t SDA_PIN;
   GPIO_TypeDef *SCL_GPIO;
   uint16_t SCL_PIN;
}I2C;

void I2C_init(GPIO_TypeDef *SDA_Port,uint16_t SDA_pin,GPIO_TypeDef *SCL_Port,uint16_t SCL_pin)
{
   I2C.SDA_GPIO = SDA_Port;
   I2C.SDA_PIN = SDA_pin;

   I2C.SCL_GPIO = SCL_Port;
   I2C.SCL_PIN = SCL_pin;

   GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = SCL_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SCL_Port, &GPIO_InitStruct);
}

void SDA_in(void)
{
   GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = I2C.SDA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
   //GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(I2C.SDA_GPIO, &GPIO_InitStruct);
}

void I2C_Delay(unsigned int time)
{
   while(time)
   time--;
}

void SDA_out(void)
{
   GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = I2C.SDA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(I2C.SDA_GPIO, &GPIO_InitStruct);
}

void I2C_Start(void)
{
  SDA_out();
   HAL_GPIO_WritePin(I2C.SDA_GPIO,I2C.SDA_PIN,GPIO_PIN_SET);
   HAL_GPIO_WritePin(I2C.SCL_GPIO,I2C.SCL_PIN,GPIO_PIN_SET);
   I2C_Delay(__I2C_DELAY);
   HAL_GPIO_WritePin(I2C.SDA_GPIO,I2C.SDA_PIN,GPIO_PIN_RESET);
   I2C_Delay(__I2C_DELAY);
   HAL_GPIO_WritePin(I2C.SCL_GPIO,I2C.SCL_PIN,GPIO_PIN_RESET);
   I2C_Delay(__I2C_DELAY);
}
void I2C_STOP(void)
{
  SDA_out();
  HAL_GPIO_WritePin(I2C.SDA_GPIO,I2C.SDA_PIN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(I2C.SCL_GPIO,I2C.SCL_PIN,GPIO_PIN_SET);
  I2C_Delay(__I2C_DELAY);
   HAL_GPIO_WritePin(I2C.SDA_GPIO,I2C.SDA_PIN,GPIO_PIN_SET);
  I2C_Delay(__I2C_DELAY);
  HAL_GPIO_WritePin(I2C.SCL_GPIO,I2C.SCL_PIN,GPIO_PIN_RESET);
   I2C_Delay(__I2C_DELAY);
}

unsigned char I2C_CheckAck(void)
{
     unsigned char ack=0;
     SDA_in();
     HAL_GPIO_WritePin(I2C.SCL_GPIO,I2C.SCL_PIN,GPIO_PIN_SET);
     I2C_Delay(__I2C_DELAY/2);
     ack=HAL_GPIO_ReadPin(I2C.SDA_GPIO,I2C.SDA_PIN);
     I2C_Delay(__I2C_DELAY/2);
     HAL_GPIO_WritePin(I2C.SCL_GPIO,I2C.SCL_PIN,GPIO_PIN_RESET);
     I2C_Delay(__I2C_DELAY/2);
     if(ack==1) return 0;
     return 1;
}

void I2C_Write(unsigned char Data)
{
unsigned char i;
     SDA_out();
     for(i=0;i<8;i++)
    {
       if(((Data<<i)&0x80) == 0 ) HAL_GPIO_WritePin(I2C.SDA_GPIO,I2C.SDA_PIN,GPIO_PIN_RESET);
       else HAL_GPIO_WritePin(I2C.SDA_GPIO,I2C.SDA_PIN,GPIO_PIN_SET);

       HAL_GPIO_WritePin(I2C.SCL_GPIO,I2C.SCL_PIN,GPIO_PIN_SET);
       I2C_Delay(__I2C_DELAY);
       HAL_GPIO_WritePin(I2C.SCL_GPIO,I2C.SCL_PIN,GPIO_PIN_RESET);
       I2C_Delay(__I2C_DELAY);
     }
}

unsigned char I2C_Read(void)
{
     unsigned char I2C_data=0,i,temp;
     SDA_in();
     for(i=0;i<8;i++)
    {
      SDA_out();
       HAL_GPIO_WritePin(I2C.SDA_GPIO,I2C.SDA_PIN,GPIO_PIN_SET);
       SDA_in();
         HAL_GPIO_WritePin(I2C.SCL_GPIO,I2C.SCL_PIN,GPIO_PIN_SET);
         I2C_Delay(__I2C_DELAY);
         temp=HAL_GPIO_ReadPin(I2C.SDA_GPIO,I2C.SDA_PIN);
         HAL_GPIO_WritePin(I2C.SCL_GPIO,I2C.SCL_PIN,GPIO_PIN_RESET);
         I2C_Delay(__I2C_DELAY);
         I2C_data=I2C_data<<1;
          if(temp==1)I2C_data=I2C_data|0x01;
    }
    return I2C_data;
}
