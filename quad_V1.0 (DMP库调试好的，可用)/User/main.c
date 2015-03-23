

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
uint8_t acc_x_h,acc_x_l,
	acc_y_h,acc_y_l,
	acc_z_h,acc_z_l;
uint8_t gyro_x_h,gyro_x_l,
        gyro_y_h,gyro_y_l,
        gyro_z_h,gyro_z_l;
uint8_t tem_h,tem_l;
uint16_t tem;
int16_t acc_x,acc_y,acc_z;
int16_t gyro_x,gyro_y,gyro_z;

/**************************************/
unsigned long sensor_timestamp1;
short gyro1[3], accel1[3], sensors1;
unsigned char more1;
long quat1[4];
float Yaw1=0.00;
float Roll,Pitch;
int a,b,c;
u8 temp;
float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
float Yaw=0.00;
float Roll,Pitch;
/********************************/
int main(void)
{
	
        SystemInit();
       // i2cInit();
        
	TIM4_INIT();
	TIM2_INIT();
       // AnBT_UART1_Configuration();
        
        
        //i2cWrite(0x68,0x6b,0x00);       //�������*/
       // delay_ms(1000);        /*������ߺ����ʱҪ�ϰٺ��룬�����ʼ�����ɹ�*/
        //i2cWrite(0x68,0x19,0x07);       //�����ǲ����ʣ�1khzЧ������
        //i2cWrite(0x68,0x1a,0x06);           //���ٶ�44hz�˲���������42hz�˲�
        //i2cWrite(0x68,0x1b,0x18);      //������������� +-2000��ÿ��
        //i2cWrite(0x68,0x1c,0x01);     //���ٶȶ�������� +-4G 
       // delay_ms(100);        /*������ߺ����ʱҪ�ϰٺ��룬�����ʼ�����ɹ�*/
        
        ANBT_I2C_Configuration();
        delay_ms(100);        /*������ߺ����ʱҪ�ϰٺ��룬�����ʼ�����ɹ�*/
        AnBT_DMP_MPU6050_Init();
        temp=0x00;
       /* AnBT_DMP_I2C_Write(0x68,0x6b,1,&temp);
        temp=0x07;
        AnBT_DMP_I2C_Write(0x68,0x19,1,&temp);
        temp=0x06;
        AnBT_DMP_I2C_Write(0x68,0x1a,1,&temp);
        temp=0x18;
        AnBT_DMP_I2C_Write(0x68,0x1b,1,&temp);
        temp=0x01;
        AnBT_DMP_I2C_Write(0x68,0x1c,1,&temp);
        */
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
		 Yaw    =   atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	
              }
              /*  i2cRead(0x68, 0x3B ,  1 , &acc_x_h);
              i2cRead(0x68, 0x3c ,  1 , &acc_x_l);
              i2cRead(0x68, 0x3e ,  1 , &acc_y_h);
              i2cRead(0x68, 0x3f ,  1 , &acc_y_l);
              i2cRead(0x68, 0x40 ,  1 , &acc_z_h);
              i2cRead(0x68, 0x41 ,  1 , &acc_z_l);*/
          
             /* AnBT_DMP_I2C_Read(0x68, 0x3B ,  1 , &acc_x_h);
              AnBT_DMP_I2C_Read(0x68, 0x3c ,  1 , &acc_x_l);
              AnBT_DMP_I2C_Read(0x68, 0x3e ,  1 , &acc_y_h);
              AnBT_DMP_I2C_Read(0x68, 0x3f ,  1 , &acc_y_l);
              AnBT_DMP_I2C_Read(0x68, 0x40 ,  1 , &acc_z_h);
              AnBT_DMP_I2C_Read(0x68, 0x41 ,  1 , &acc_z_l);*/
             // delay_ms(1000); 
              //AnBT_DMP_MPU6050_SEND_DATA_FUN();
        
	}
  
 // return 0;
}


