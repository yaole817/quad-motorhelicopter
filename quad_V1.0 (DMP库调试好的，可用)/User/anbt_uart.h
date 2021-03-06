#ifndef __ANBT_UART_H__
#define __ANBT_UART_H__
/*****************************************************************************************
圆点博士STM32蓝牙4.0最小系统板AnBT库文件和例程源代码。和圆点博士STM32无线下载助手软件兼容。
该例程适用LGPL协议。用户可以自由转载使用该代码，但不得移除该部分版权信息
更多信息，请访问官方网站www.etootle.com
******************************************************************************************/
//#include "stm32f10x_lib.h"
#include "includes.h"

#define AnBT_COM_Buf_Length	64
#define AnBT_USART1_TX	GPIO_Pin_9
#define AnBT_USART1_RX	GPIO_Pin_10
//
extern unsigned char com_receive_str_index;		//圆点博士:接收缓冲地址索引
extern unsigned char com_receive_str_buf[AnBT_COM_Buf_Length]; //圆点博士:接收缓冲
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
