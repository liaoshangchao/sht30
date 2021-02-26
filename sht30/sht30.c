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
 
 /*主机发送ACK*/
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

 /*主机不发送ACK*/
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

 /*主机等待从机的ACK*/
uint8_t IIC_wait_ACK(void)
{
    uint8_t t = 200;
    SDA_SetDigitalOutput() ;
    SDA_SetHigh();          //8位发送完后释放数据线，准备接收应答位 
    __delay_us(1); 
    SCL_SetLow();
    __delay_us(1);  
    SDA_SetDigitalInput() ;
    __delay_us(1);  
    while(SDA_GetValue())   //等待SHT30应答
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
功能:启动I2C总线,即发送I2C起始条件.  
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
功能:结束I2C总线,即发送I2C结束条件.  
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
字节数据发送函数               
函数原型: void  SendByte(UCHAR c);
功能:将数据c发送出去,可以是地址,也可以是数据
********************************************************************/
void  IIC_SendByte(uint8_t byte)
{
	uint8_t  BitCnt;
	SDA_SetDigitalOutput() ;
	SCL_SetLow();
	for(BitCnt=0;BitCnt<8;BitCnt++)         //要传送的数据长度为8位
	{
		if(byte&0x80) SDA_SetHigh();        //判断发送位
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
 字节数据接收函数               
函数原型: UCHAR  RcvByte();
功能: 用来接收从器件传来的数据  
********************************************************************/    
uint8_t IIC_RcvByte(void)
{
    uint8_t retc;
    uint8_t BitCnt;
    retc=0; 
    SDA_SetDigitalInput();      //置数据线为输入方式
    __delay_us(1);                    
    for ( BitCnt = 0 ; BitCnt < 8 ; BitCnt++ )
    {  
        SCL_SetLow();           //置时钟线为低，准备接收数据位
        __delay_us(2);               
        SCL_SetHigh();          //置时钟线为高使数据线上数据有效                
        retc = retc<<1;
        if ( SDA_GetValue() )
        {
            retc |= 1;          //读数据位,接收的数据位放入retc中 
        }
        __delay_us(1);
    }
    SCL_SetLow();    
    return(retc);
}
/*******************************************************************
 温湿度获取函数               
函数原型: SHT30_read_result(u8 addr);
功能: 用来接收从器件采集并合成温湿度
********************************************************************/ 
void SHT30_read_result(uint8_t addr)
{
	uint16_t tem,hum;
	uint16_t buff[6];
	float Temperature=0;
	float Humidity=0;
	
	IIC_Start();
	IIC_SendByte(addr<<1 | write);//写7位I2C设备地址加0作为写取位,1为读取位
	IIC_wait_ACK();
	IIC_SendByte(0x2C);
	IIC_wait_ACK();
	IIC_SendByte(0x06);
	IIC_wait_ACK();
	IIC_Stop();
	__delay_ms(50);
	IIC_Start();
	IIC_SendByte(addr<<1 | read);//写7位I2C设备地址加0作为写取位,1为读取位
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
	
	tem = ((buff[0]<<8) | buff[1]);//温度拼接
	hum = ((buff[3]<<8) | buff[4]);//湿度拼接
	
	/*转换实际温度*/
	Temperature= (175.0*(float)tem/65535.0-45.0) ;// T = -45 + 175 * tem / (2^16-1)
	Humidity= (100.0*(float)hum/65535.0);// RH = hum*100 / (2^16-1)
	
	if((Temperature>=-20)&&(Temperature<=125)&&(Humidity>=0)&&(Humidity<=100))//过滤错误数据
	{
		humiture[0]=Temperature;
		humiture[2]=Humidity;
        //将数据装换位Tuya平台Value型数据；如331表示33.1C
        wifi_sht30_data[0]=(unsigned int)(Temperature*10);
        wifi_sht30_data[2]=(unsigned int)(Humidity);
//		sprintf(humiture_buff1,"%6.2f*C %6.2f%%",Temperature,Humidity);//111.01*C 100.01%（保留2位小数）
        
        OLED_ShowNum(32,4,humiture[0],2,16);    //显示温度值
        OLED_ShowCHinese(0,4,0);                //显示“温”字符
        OLED_ShowCHinese(16,4,1);               //显示“度”字符

		if(humiture[0]>0)
			OLED_ShowChar(48,4,'`',16);
		else
			OLED_ShowChar(56,4,'`',16);
		OLED_ShowCHinese(72,4,2);               //显示“湿”字符
        OLED_ShowCHinese(88,4,1);               //显示“度”字符
		OLED_ShowNum(104,4,humiture[2],2,16);   //显示湿度值
		OLED_ShowChar(120,4,'%',16);
        
		
	}
//    printf("温湿度：%s\n",humiture_buff1);
//	  printf("温度：%d,湿度：%d\n",wifi_sht30_data[0],wifi_sht30_data[2]);
	hum=0;
	tem=0;
}
