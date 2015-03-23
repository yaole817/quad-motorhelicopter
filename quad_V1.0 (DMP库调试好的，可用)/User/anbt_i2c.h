#ifndef __ANBT_I2C_H__
#define __ANBT_I2C_H__
/*****************************************************************************************
Բ�㲩ʿSTM32����4.0��Сϵͳ��AnBT���ļ�������Դ���롣��Բ�㲩ʿSTM32������������������ݡ�
����������LGPLЭ�顣�û���������ת��ʹ�øô��룬�������Ƴ��ò��ְ�Ȩ��Ϣ
������Ϣ������ʹٷ���վwww.etootle.com
******************************************************************************************/
//#include "stm32f10x_lib.h"
#include "includes.h"
#include "anbt_uart.h"
//
//
#define AnBT_MPU6050_INT			GPIO_Pin_3		//PB3
#define AnBT_MPU6050_INT_PORT	                GPIOB
//
#define ANBT_MPU6050_INT_STATE   GPIO_ReadInputDataBit(AnBT_MPU6050_INT_PORT, AnBT_MPU6050_INT)
//
#define ANBT_I2C_SDA 		GPIO_Pin_5	 
#define ANBT_I2C_SCL 		GPIO_Pin_4	
#define ANBT_I2C_PORT           GPIOA
//
#define ANBT_I2C_SCL_0 		GPIO_ResetBits(ANBT_I2C_PORT, ANBT_I2C_SCL)
#define ANBT_I2C_SCL_1 		GPIO_SetBits(ANBT_I2C_PORT, ANBT_I2C_SCL)
#define ANBT_I2C_SDA_0 		GPIO_ResetBits(ANBT_I2C_PORT, ANBT_I2C_SDA)
#define ANBT_I2C_SDA_1   	GPIO_SetBits(ANBT_I2C_PORT, ANBT_I2C_SDA)
//
#define ANBT_I2C_SDA_STATE   	GPIO_ReadInputDataBit(ANBT_I2C_PORT, ANBT_I2C_SDA)
#define ANBT_I2C_DELAY 				ANBT_I2C_Delay(100000)
#define ANBT_I2C_NOP					ANBT_I2C_Delay(10) 
//
#define ANBT_I2C_READY		0x00
#define ANBT_I2C_BUS_BUSY	0x01	
#define ANBT_I2C_BUS_ERROR	0x02
//
#define ANBT_I2C_NACK	        0x00 
#define ANBT_I2C_ACK		0x01
//
extern void ANBT_I2C_Configuration(void);
extern void ANBT_I2C_Delay(u32 dly);
extern u8 ANBT_I2C_START(void);
extern void ANBT_I2C_STOP(void);
extern void ANBT_I2C_SendACK(void);
extern void ANBT_I2C_SendNACK(void);
extern u8 ANBT_I2C_SendByte(u8 anbt_i2c_data);
extern u8 ANBT_I2C_ReceiveByte_WithACK(void);
extern u8 ANBT_I2C_ReceiveByte(void);
extern void ANBT_I2C_Receive12Bytes(u8 *anbt_i2c_data_buffer);
extern void ANBT_I2C_Receive6Bytes(u8 *anbt_i2c_data_buffer);
extern void ANBT_I2C_Receive14Bytes(u8 *anbt_i2c_data_buffer);
extern u8 AnBT_DMP_I2C_Write(u8 anbt_dev_addr, u8 anbt_reg_addr, u8 anbt_i2c_len, u8 *anbt_i2c_data_buf);
extern u8 AnBT_DMP_I2C_Read(u8 anbt_dev_addr, u8 anbt_reg_addr, u8 anbt_i2c_len, u8 *anbt_i2c_data_buf);
extern void AnBT_DMP_Delay_us(u32 dly);
extern void AnBT_DMP_Delay_ms(u32 dly);


#endif