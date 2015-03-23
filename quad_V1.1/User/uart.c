#include "includes.h"


/*******************************************************************************
"	��������USART_Configuration											  "
"	��  ��:																   "
"	��  ��:																   "
"	����˵����															   "
"	��ʼ������Ӳ���豸��δ�����жϡ�									   "
"	���ò��裺																"
"	(1)��GPIO��USART��ʱ��												 ""
"	(2)����USART�����ܽ�GPIOģʽ							                        	""
"	(3)����USART���ݸ�ʽ�������ʵȲ���									  "
"	(4)���ʹ��USART����													  "
*/
// void USART_Configuration(void)
// {
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	USART_InitTypeDef USART_InitStructure;

// 	/*" ��1������GPIO��USART������ʱ�� "*/
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

// 	/*" ��2������USART Tx��GPIO����Ϊ���츴��ģʽ "*/
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);

// 	/*" ��3������USART Rx��GPIO����Ϊ��������ģʽ							 "
// 	"	����CPU��λ��GPIOȱʡ���Ǹ�������ģʽ���������������費�Ǳ����	  "
// 		���ǣ��һ��ǽ�����ϱ����Ķ������ҷ�ֹ�����ط��޸���������ߵ����ò���
// 	*/
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
// 	/*"  ��3���Ѿ����ˣ�����ⲽ���Բ���								 "
// 		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	*/
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);


// 	/*" ��4��������USART����									"
// 	    - BaudRate = 115200 baud
// 	    - Word Length = 8 Bits
// 	    - One Stop Bit
// 	    - No parity
// 	    - Hardware flow control disabled (RTS and CTS signals)
// 	    - Receive and transmit enabled
// 	*/
// 	USART_InitStructure.USART_BaudRate = 9600;
// 	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
// 	USART_InitStructure.USART_StopBits = USART_StopBits_1;
// 	USART_InitStructure.USART_Parity = USART_Parity_No;
// 	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
// 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
// 	USART_Init(USART1, &USART_InitStructure);

// 	/* Enable USARTy Receive and Transmit interrupts */
//     USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//     //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
// 	/* ��5����ʹ�� USART�� ������� */
// 	USART_Cmd(USART1, ENABLE);

// 	/* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
// 		�����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
// 	USART_ClearFlag(USART1, USART_FLAG_TC);     /* �巢����Ǳ�־��Transmission Complete flag */
// }


void RS485_ChooseDelay(unsigned short time)
{
		while(time--) 
                {	
		}
}


void USART_Configuration(void)
{
        USART_InitTypeDef USART_InitStructure;
        NVIC_InitTypeDef NVIC_InitStructure;
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE  );
	
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
    
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;			  //???D1��??10
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	  //????��?��?
        GPIO_Init(GPIOA, &GPIO_InitStructure);				  //????A???��

	
        NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
	

	USART_InitStructure.USART_BaudRate            = 115200  ;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;


	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE); 

}

// void UsartSend(uint8_t ch)
// {
// 	USART_SendData(USART1, (uint8_t) ch);

// 	/* Loop until the end of transmission */
// 	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
// 	{}
// }


void UsartSend(unsigned char temp)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);	 
	
	RS485_ChooseDelay(10);
	
	USART_SendData(USART3, temp);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);

	GPIO_SetBits(GPIOA, GPIO_Pin_12);
	
	RS485_ChooseDelay(10);
}

//���ַ��ĸ�ʽ���
void Print(uint8_t num)
{
	uint8_t  bai,shi,ge;
	bai=num/100;
	shi=num%100/10;
	ge=num%10;
	UsartSend('0'+bai);
	UsartSend('0'+shi);
	UsartSend('0'+ge);
}
//���ַ�����ʽ���INT������
void PrintInt(uint16_t num)
{
	 uint8_t w5,w4,w3,w2,w1;
	 w5=num/10000;
	 w4=num%10000/1000;
	 w3=num%1000/100;
	 w2=num%100/10;
	 w1=num%10;
	 UsartSend('0'+w5);
	 UsartSend('0'+w4);
	 UsartSend('0'+w3);
	 UsartSend('0'+w2);
	 UsartSend('0'+w1);
}
//����ַ���
// void PrintChar(char *s)
// {
// 	char *p;
// 	p=s;
// 	while(*p != '\0')
// 	{
// 		UsartSend(*p);
// 		p++;
// 	}
// }
void RS485_SendByte(unsigned char temp)
{
	
	USART_SendData(USART3, temp);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);

}
void PrintChar (char *s) 
{
        GPIO_ResetBits(GPIOA, GPIO_Pin_12);	 
	
	RS485_ChooseDelay(10);
	
	while (*s != '\0') 
	{

		RS485_SendByte(*(unsigned char *)s);
		s++;
	}
	
	RS485_ChooseDelay(800);
	GPIO_SetBits(GPIOA, GPIO_Pin_12);
	
}
void PrintHexInt16(int16_t num)
{
	UsartSend((num & 0xff00) >> 8);//�ȷ��͸ߣ�λ���ٷ��͵ͣ�λ
	UsartSend((uint8_t)(num & 0x00ff));
}
void usart_INIT(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* NVIC_PriorityGroup 1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}	
