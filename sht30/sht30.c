/*
 * File:   sht30.c
 * Author: chao
 *
 * Created on February 5, 2021, 10:15 AM
 */


#include <xc.h>
#include "sht30.h"
#include "../OLED/OLED.h"

float humiture[4];
unsigned int wifi_sht30_data[4];
uint8_t Refresh_SHT30_Data=0;
uint8_t humiture_buff1[20];
uint8_t humiture_buff2[20];
 
uint8_t Temperature_L=15;
uint8_t Humidity_L=50;
uint8_t Temperature_H=30;
uint8_t Humidity_H=80;
 
 /*��������ACK*/
void IIC_ACK(void)
{
    SDA_SetDigitalOutput() ;
    SCL_SetLow();
    __delay_us(2); 
    SDA_SetLow() ;
    __delay_us(2);     
    SCL_SetHigh();         
    __delay_us(2);                 
    SCL_SetLow();                     
    __delay_us(1);    
}

 /*����������ACK*/
void IIC_NACK(void)
{
    SDA_SetDigitalOutput() ;
    SCL_SetLow();
    __delay_us(2);  
    SDA_SetHigh();
    __delay_us(2);      
     SCL_SetHigh();
    __delay_us(2);                   
    SCL_SetLow();                     
    __delay_us(1);    
}

 /*�����ȴ��ӻ���ACK*/
uint8_t IIC_wait_ACK(void)
{
    uint8_t t = 200;
    SDA_SetDigitalOutput() ;
    SDA_SetHigh();          //8λ��������ͷ������ߣ�׼������Ӧ��λ 
    __delay_us(1); 
    SCL_SetLow();
    __delay_us(1);  
    SDA_SetDigitalInput() ;
    __delay_us(1);  
    while(SDA_GetValue())   //�ȴ�SHT30Ӧ��
    {
        t--;
        __delay_us(1);  
        if(t==0)
        {
            SCL_SetLow();
            return 1;
        }
        __delay_us(1);  
    }
    __delay_us(1);       
    SCL_SetHigh();
    __delay_us(1); 
    SCL_SetLow();             
    __delay_us(1);    
    return 0;	
}

/*******************************************************************
����:����I2C����,������I2C��ʼ����.  
********************************************************************/
void IIC_Start(void)
{
    SDA_SetDigitalOutput() ;
    SDA_SetHigh();
    SCL_SetHigh();
    __delay_us(4);	
    SDA_SetLow();
    __delay_us(4); 
    SCL_SetLow();
}
 
/*******************************************************************
����:����I2C����,������I2C��������.  
********************************************************************/
void IIC_Stop(void)
{
	SDA_SetDigitalOutput() ;
    SDA_SetLow();
    SCL_SetLow();
    __delay_us(4);
    SCL_SetHigh();
	__delay_us(4);
	SDA_SetHigh();
	__delay_us(4);
}
 
/*******************************************************************
�ֽ����ݷ��ͺ���               
����ԭ��: void  SendByte(UCHAR c);
����:������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������
********************************************************************/
void  IIC_SendByte(uint8_t byte)
{
	uint8_t  BitCnt;
	SDA_SetDigitalOutput() ;
	SCL_SetLow();
	for(BitCnt=0;BitCnt<8;BitCnt++)         //Ҫ���͵����ݳ���Ϊ8λ
	{
		if(byte&0x80) SDA_SetHigh();        //�жϷ���λ
		else SDA_SetLow(); 
		byte<<=1;
		__delay_us(2); 
		SCL_SetHigh();
		__delay_us(2);
		SCL_SetLow();
		__delay_us(2);
	}
}
/*******************************************************************
 �ֽ����ݽ��պ���               
����ԭ��: UCHAR  RcvByte();
����: �������մ���������������  
********************************************************************/    
uint8_t IIC_RcvByte(void)
{
    uint8_t retc;
    uint8_t BitCnt;
    retc=0; 
    SDA_SetDigitalInput();      //��������Ϊ���뷽ʽ
    __delay_us(1);                    
    for ( BitCnt = 0 ; BitCnt < 8 ; BitCnt++ )
    {  
        SCL_SetLow();           //��ʱ����Ϊ�ͣ�׼����������λ
        __delay_us(2);               
        SCL_SetHigh();          //��ʱ����Ϊ��ʹ��������������Ч                
        retc = retc<<1;
        if ( SDA_GetValue() )
        {
            retc |= 1;          //������λ,���յ�����λ����retc�� 
        }
        __delay_us(1);
    }
    SCL_SetLow();    
    return(retc);
}
/*******************************************************************
 ��ʪ�Ȼ�ȡ����               
����ԭ��: SHT30_read_result(u8 addr);
����: �������մ������ɼ����ϳ���ʪ��
********************************************************************/ 
void SHT30_read_result(uint8_t addr)
{
	uint16_t tem,hum;
	uint16_t buff[6];
	float Temperature=0;
	float Humidity=0;
	
	IIC_Start();
	IIC_SendByte(addr<<1 | write);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
	IIC_wait_ACK();
	IIC_SendByte(0x2C);
	IIC_wait_ACK();
	IIC_SendByte(0x06);
	IIC_wait_ACK();
	IIC_Stop();
	__delay_ms(50);
	IIC_Start();
	IIC_SendByte(addr<<1 | read);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
	if( IIC_wait_ACK() == 0 )
	{
		buff[0]=IIC_RcvByte();
		IIC_ACK();
		buff[1]=IIC_RcvByte();
		IIC_ACK();
		buff[2]=IIC_RcvByte();
		IIC_ACK();
		buff[3]=IIC_RcvByte();
		IIC_ACK();
		buff[4]=IIC_RcvByte();
		IIC_ACK();
		buff[5]=IIC_RcvByte();
		IIC_NACK();
		IIC_Stop();
	}
	
	tem = ((buff[0]<<8) | buff[1]);//�¶�ƴ��
	hum = ((buff[3]<<8) | buff[4]);//ʪ��ƴ��
	
	/*ת��ʵ���¶�*/
	Temperature= (175.0*(float)tem/65535.0-45.0) ;// T = -45 + 175 * tem / (2^16-1)
	Humidity= (100.0*(float)hum/65535.0);// RH = hum*100 / (2^16-1)
	
	if((Temperature>=-20)&&(Temperature<=125)&&(Humidity>=0)&&(Humidity<=100))//���˴�������
	{
		humiture[0]=Temperature;
		humiture[2]=Humidity;
        //������װ��λTuyaƽ̨Value�����ݣ���331��ʾ33.1C
        wifi_sht30_data[0]=(unsigned int)(Temperature*10);
        wifi_sht30_data[2]=(unsigned int)(Humidity);
//		sprintf(humiture_buff1,"%6.2f*C %6.2f%%",Temperature,Humidity);//111.01*C 100.01%������2λС����
        
        OLED_ShowNum(32,4,humiture[0],2,16);    //��ʾ�¶�ֵ
        OLED_ShowCHinese(0,4,0);                //��ʾ���¡��ַ�
        OLED_ShowCHinese(16,4,1);               //��ʾ���ȡ��ַ�

		if(humiture[0]>0)
			OLED_ShowChar(48,4,'`',16);
		else
			OLED_ShowChar(56,4,'`',16);
		OLED_ShowCHinese(72,4,2);               //��ʾ��ʪ���ַ�
        OLED_ShowCHinese(88,4,1);               //��ʾ���ȡ��ַ�
		OLED_ShowNum(104,4,humiture[2],2,16);   //��ʾʪ��ֵ
		OLED_ShowChar(120,4,'%',16);
        
		
	}
//    printf("��ʪ�ȣ�%s\n",humiture_buff1);
//	  printf("�¶ȣ�%d,ʪ�ȣ�%d\n",wifi_sht30_data[0],wifi_sht30_data[2]);
	hum=0;
	tem=0;
}
