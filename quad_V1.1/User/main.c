

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "includes.h"
#define q30  1073741824.0f
int16_t duty=0;
void delay(uint16_t t)
{
    while(t--);
}

/**************************************/
unsigned long sensor_timestamp1;
short gyro1[3], accel1[3], sensors1;
unsigned char more1;
long quat1[4];
float Yaw=0.00;
float Roll,Pitch;
int a,b,c;
float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
/********************************/
int main(void)
{
	
        SystemInit(); //system clock
	TIM4_INIT();
	TIM2_INIT(); //delay init
       // AnBT_UART1_Configuration();
        
        ANBT_I2C_Configuration();  //i2c init
         
        delay_ms(100);        /*解除休眠后的延时要上百毫秒，否则初始化不成功*/
        AnBT_DMP_MPU6050_Init();
        
	while (1)
	{
              dmp_read_fifo(gyro1, accel1, quat1, &sensor_timestamp1, &sensors1,&more1);
              if (sensors1 & INV_WXYZ_QUAT )
	      {
	 	 q0=quat1[0] / q30;
		 q1=quat1[1] / q30;
		 q2=quat1[2] / q30;
		 q3=quat1[3] / q30;
		 Pitch  =   asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; // pitch
 		 Roll   =   atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
		 Yaw    =   atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	//yaw
              }

             // delay_ms(1000); 
              //AnBT_DMP_MPU6050_SEND_DATA_FUN();
        
	}
  
 // return 0;
}


