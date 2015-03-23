/*************************************************************************************************************
Բ�㲩ʿС���������2014������Դ��������:
��Դ��������ο�,Բ�㲩ʿ����Դ�����ṩ�κ���ʽ�ĵ���,Ҳ������ʹ�ø�Դ��������ֵ���ʧ����.
�û�������ѧϰ��Ŀ���޸ĺ�ʹ�ø�Դ����.
���û����޸ĸ�Դ����ʱ,�����Ƴ��ò��ְ�Ȩ��Ϣ�����뱣��ԭ������.

������Ϣ������ʹٷ���վwww.etootle.com, �ٷ�����:http://weibo.com/xiaosizhou
**************************************************************************************************************/
#include "anbt_mpu6050.h"
extern unsigned char anbt_ak8975_mag_data_buffer[6];

void ANBT_MPU6050_Init(void)	
{
	//AnBT_Uart1_Send_String("M-6,Init MPU6050 Device.",24);
	//
        ANBT_MPU6050_EXIT_SLEEP_FUN();    //Բ�㲩ʿ:�˳�����ģʽ
	ANBT_MPU6050_PWM_CFG_FUN(); 	 //Բ�㲩ʿ:�����ڲ�ʱ��
	ANBT_MPU6050_GYRO_CFG_FUN();      //Բ�㲩ʿ:��������������
	ANBT_MPU6050_ACCEL_CFG_FUN();     //Բ�㲩ʿ:���ü��ٶ�����
	ANBT_MPU6050_USER_CTRL_FUN();
	ANBT_MPU6050_I2CBYPASS_CFG_FUN(); //Բ�㲩ʿ:���õ�Ŷ�дģʽ
	ANBT_MPU6050_INT_CFG_FUN();
}

void ANBT_SEND_CHIP_IDs_FUN(u8 mpu6050_gyro_id,u8 hmc5883l_mag_id,u8 ak8975_mag_id)	
{
	unsigned char chip_id[3];
	unsigned char data_type,checksum,i;
	//
	AnBT_Uart1_Send_String("M-7,Send chip IDs.",18);
	//
	chip_id[0]=mpu6050_gyro_id;
	chip_id[1]=hmc5883l_mag_id;	
	chip_id[2]=ak8975_mag_id;	
	//
	data_type=0xA0;
	checksum=data_type;
	for(i=0;i<3;i++) checksum+=chip_id[i];
	checksum&=0xff;
	checksum=~checksum;
	checksum++;
	//
	AnBT_Uart1_Send_Char(':');
	AnBT_Uart1_Send_Num(data_type);
	for(i=0;i<3;i++) AnBT_Uart1_Send_Num(chip_id[i]);	
	AnBT_Uart1_Send_Num(checksum);
	AnBT_Uart1_Send_Char('/');
	AnBT_Uart1_Send_Char(13);																	//Բ�㲩ʿ:���ͻس��ַ�
}

u8 ANBT_MPU6050_GYRO_WHOAMI_FUN(void)
{
	u8 anbt_mpu6050_gyro_id;
	//
	ANBT_I2C_START();
	ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_ADDR);	//Բ�㲩ʿ:����������д��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_WHOAMI_ADDR);  //Բ�㲩ʿ:����������ID��ַ
	ANBT_I2C_START();
	ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_ADDR+1);      //Բ�㲩ʿ:���������Ƕ���ַ
	anbt_mpu6050_gyro_id=ANBT_I2C_ReceiveByte();	//Բ�㲩ʿ:����������ID
	ANBT_I2C_STOP();
	//
	return anbt_mpu6050_gyro_id;
}
//
u8 ANBT_MPU6050_READ_REG_FUN(u8 anbt_mpu6050_dev_addr,u8 anbt_mpu6050_reg_addr)   
{
	u8 anbt_mpu6050_reg;
	
	ANBT_I2C_START();
	ANBT_I2C_SendByte(anbt_mpu6050_dev_addr);	//Բ�㲩ʿ:����������д��ַ
	ANBT_I2C_SendByte(anbt_mpu6050_reg_addr);    //Բ�㲩ʿ:���������ǼĴ�����ַ
	ANBT_I2C_START();
	ANBT_I2C_SendByte(anbt_mpu6050_dev_addr+1);      //Բ�㲩ʿ:���������Ƕ���ַ
	anbt_mpu6050_reg=ANBT_I2C_ReceiveByte();	//Բ�㲩ʿ:���������ǼĴ���ֵ
	ANBT_I2C_STOP();
	//
	return anbt_mpu6050_reg;
}

void ANBT_MPU6050_PWM_CFG_FUN(void)   
{
	ANBT_I2C_START();
	ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_ADDR);	//Բ�㲩ʿ:����������д��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_PWR_MGMT_1_ADDR);  //Բ�㲩ʿ:����������PWM��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_PWR_MGMT_1_VALUE); //Բ�㲩ʿ:����������PWMֵ
	ANBT_I2C_STOP();
}
//
void ANBT_MPU6050_GYRO_CFG_FUN(void)   
{
	ANBT_I2C_START();
	ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_ADDR);		//Բ�㲩ʿ:����������д��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_CFG_ADDR);   	//Բ�㲩ʿ:����������PWM��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_CFG_VALUE); 	//Բ�㲩ʿ:����������PWMֵ
	ANBT_I2C_STOP();
}
//
void ANBT_MPU6050_ACCEL_CFG_FUN(void)   
{
	ANBT_I2C_START();
	ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_ADDR);	//Բ�㲩ʿ:����������д��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_ACCEL_CFG_ADDR);   //Բ�㲩ʿ:����������PWM��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_ACCEL_CFG_VALUE); //Բ�㲩ʿ:����������PWMֵ
	ANBT_I2C_STOP();
}

void ANBT_MPU6050_EXIT_SLEEP_FUN(void)  
{
	ANBT_I2C_START();
	ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_ADDR);	//Բ�㲩ʿ:����������д��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_PWR_MGMT_1_ADDR);  //Բ�㲩ʿ:����������PWM��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_EXIT_SLEEP_VALUE); //Բ�㲩ʿ:����������PWMֵ
	ANBT_I2C_STOP();
}

void ANBT_MPU6050_USER_CTRL_FUN(void)   
{
	ANBT_I2C_START();
	ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_ADDR);	//Բ�㲩ʿ:����������д��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_USER_CTRL_ADDR);  //Բ�㲩ʿ:����������PWM��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_USER_CTRL_VALUE); //Բ�㲩ʿ:����������PWMֵ
	ANBT_I2C_STOP();
}

void ANBT_MPU6050_I2CBYPASS_CFG_FUN(void)   
{
	ANBT_I2C_START();
	ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_ADDR);		//Բ�㲩ʿ:����������д��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_I2CBYPASS_CFG_ADDR);   //Բ�㲩ʿ:����������PWM��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_I2CBYPASS_CFG_VALUE); 	//Բ�㲩ʿ:����������PWMֵ
	ANBT_I2C_STOP();
}

void ANBT_MPU6050_INT_CFG_FUN(void)   
{
	ANBT_I2C_START();
	ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_ADDR);	//Բ�㲩ʿ:����������д��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_INT_CFG_ADDR);   //Բ�㲩ʿ:����������PWM��ַ
	ANBT_I2C_SendByte(ANBT_MPU6050_INT_CFG_VALUE); 	//Բ�㲩ʿ:����������PWMֵ
	ANBT_I2C_STOP();
}

void ANBT_MPU6050_GYRO_READ_FUN(u8 *mpu6050_gyro_data_buffer)   
{
	if(!ANBT_MPU6050_INT_STATE) 
	{
		ANBT_I2C_START();
		ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_ADDR);	//Բ�㲩ʿ:����������д��ַ
		ANBT_I2C_SendByte(ANBT_MPU6050_ACCEL_DATA_ADDR);   //Բ�㲩ʿ:���������ǼĴ�����ַ
		ANBT_I2C_START();
		ANBT_I2C_SendByte(ANBT_MPU6050_GYRO_ADDR+1);      //Բ�㲩ʿ:���������Ƕ���ַ
		ANBT_I2C_Receive14Bytes(mpu6050_gyro_data_buffer); //Բ�㲩ʿ:���������ǼĴ���ֵ
		ANBT_I2C_STOP();
	}
}

void ANBT_MPU6050_SEND_DATA_FUN(u8 *mpu6050_gyro_data_buffer)	
{
	unsigned char data_type,checksum,i;
	//
	data_type=0xA1;
	checksum=data_type;
	for(i=0;i<14;i++) checksum+=mpu6050_gyro_data_buffer[i];
	checksum&=0xff;
	checksum=~checksum;
	checksum++;
	//
	AnBT_Uart1_Send_Char(':');
	AnBT_Uart1_Send_Num(data_type);
	for(i=0;i<14;i++) AnBT_Uart1_Send_Num(mpu6050_gyro_data_buffer[i]);	
	AnBT_Uart1_Send_Num(checksum);
	AnBT_Uart1_Send_Char('/');
	AnBT_Uart1_Send_Char(13);																	//Բ�㲩ʿ:���ͻس��ַ�
}
