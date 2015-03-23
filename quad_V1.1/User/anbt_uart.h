#ifndef __ANBT_UART_H__
#define __ANBT_UART_H__
/*****************************************************************************************
Բ�㲩ʿSTM32����4.0��Сϵͳ��AnBT���ļ�������Դ���롣��Բ�㲩ʿSTM32������������������ݡ�
����������LGPLЭ�顣�û���������ת��ʹ�øô��룬�������Ƴ��ò��ְ�Ȩ��Ϣ
������Ϣ������ʹٷ���վwww.etootle.com
******************************************************************************************/
//#include "stm32f10x_lib.h"
#include "includes.h"

#define AnBT_COM_Buf_Length	64
#define AnBT_USART1_TX	GPIO_Pin_9
#define AnBT_USART1_RX	GPIO_Pin_10
//
extern unsigned char com_receive_str_index;		//Բ�㲩ʿ:���ջ����ַ����
extern unsigned char com_receive_str_buf[AnBT_COM_Buf_Length]; //Բ�㲩ʿ:���ջ���
//
extern unsigned char pid_data_buffer[16];
extern unsigned char motor_unlock_sign;
extern unsigned char gas_data_buffer;
extern unsigned char pitch_data_buffer,roll_data_buffer,yaw_data_buffer;
//
extern void AnBT_UART1_Configuration(void);
extern void AnBT_UART1_NVIC_Configuration(void);
extern void AnBT_UART1_Interrupt(void);
extern void AnBT_UART1_GPIO_Configuration(void);
extern void AnBT_Uart1_Send_Char(unsigned char ascii_code);
extern void AnBT_Uart1_Send_String(unsigned char* str_buf , unsigned char str_len);
extern void AnBT_Uart1_Send_Num(unsigned char number);
extern void AnBT_Uart1_Send_Nums(unsigned char* nums_buf , unsigned char nums_len);
//



#endif
