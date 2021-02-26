/******************************************************************************
文件名称: OLED.c
摘    要: OLED显示驱动
当前版本: V1.0	
完成日期: 2021.02.20
*******************************************************************************/

#include "OLED.h"
#include "../sht30/sht30.h"

#define OLED_Address 0x78


/*****************************************************************************
函数名称 : WriteCmd
功能描述 : 写指令函数
输入参数 : command：指令
返回参数 : 无
使用说明 : 无
*****************************************************************************/
static void WriteCmd(uint8_t command ,uint8_t addr)
{
	IIC_Start();
	IIC_SendByte(addr);//OLED地址
	IIC_ACK();
	IIC_SendByte(0x00);//寄存器地址
	IIC_ACK();
	IIC_SendByte(command);
	IIC_ACK();
	IIC_Stop();
}
/*****************************************************************************
函数名称 : WriteDat
功能描述 : 写数据函数
输入参数 : Data：数据
返回参数 : 无
使用说明 : 无
*****************************************************************************/
static void WriteDat(uint8_t Data,uint8_t addr)
{
	IIC_Start();
	IIC_SendByte(addr);                        //D/C#=0; R/W#=0
	IIC_ACK();       
	IIC_SendByte(0x40);                        //write data
	IIC_ACK();       
	IIC_SendByte(Data);
	IIC_ACK();       
	IIC_Stop();
}
/*****************************************************************************
函数名称 : OLED_WR_Byte
功能描述 : OLED写一字节
输入参数 : dat：要写入的数据 cmd=1写指令，cmd=0写数据
返回参数 : 无
使用说明 : 无
*****************************************************************************/
static void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd==1)
	{
		WriteCmd(dat,OLED_Address);
	}
	else
	{
		WriteDat(dat,OLED_Address);
	}
}
/*****************************************************************************
函数名称 : OLED_OLED_WR_Byte_con
功能描述 : 连续写入count个数据
输入参数 : dat[]：要写入的数据  count写入的个数
返回参数 : 无
使用说明 : 无
*****************************************************************************/ 
//void OLED_OLED_WR_Byte_con(uint8_t dat[], uint16_t count)//写入连续数据count个
//{
//	int i = 0;
//	Start();
//	SendData(OLED_Address);                        //D/C#=0; R/W#=0
//	SendACK();       
//	SendData(0x40);                        //write data
//	SendACK();       
//	for(i = 0 ;i < count ;i++)
//	{
//		SendData(dat[i]);
//		SendACK();
//	}
//	Stop();
//}
/*****************************************************************************
函数名称 : OLED_OLED_WR_Byte_same
功能描述 : 连续写入count个相同的数据
输入参数 : dat：要写入的数据  count：重复次数
返回参数 : 无
使用说明 : 无
*****************************************************************************/ 
/*void OLED_OLED_WR_Byte_same(uint8_t dat, uint16_t count)//写入连续数据count个
{
	int i = 0;
	Start();
	SendData(OLED_Address);                        //D/C#=0; R/W#=0
	SendACK();       
	SendData(0x40);                        //write data
	SendACK();       
	for(i = 0 ;i < count ;i++)
	{
		SendData(dat);
		SendACK();
	}
	Stop();
}*/
/*****************************************************************************
函数名称 : OLED_Init
功能描述 : OLED初始化
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void OLED_Init()
{
	OLED_WR_Byte(0xAE,1);//--display off
 	OLED_WR_Byte(0x00,1);//--set low column address
 	OLED_WR_Byte(0x10,1);//--set high column address
 	OLED_WR_Byte(0x40,1);//--set display start line
	OLED_WR_Byte(0xB0,1);//--set page address
 	OLED_WR_Byte(0x81,1);//--contract control
 	OLED_WR_Byte(0xFF,1);//--Set SEG Output Current Brightness
 	OLED_WR_Byte(0xA1,1);//--set segment remap     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xA6,1);//--normal / reverse
	OLED_WR_Byte(0xA8,1);//--multiplex ratio
	OLED_WR_Byte(0x3F,1);//--duty = 1/64
 	OLED_WR_Byte(0xC8,1);//--Com scan direction   0xc0上下反置 0xc8正常
 	OLED_WR_Byte(0xD3,1);//--set display offset
 	OLED_WR_Byte(0x00,1);//
	OLED_WR_Byte(0xD5,1);//--set osc division
 	OLED_WR_Byte(0x80,1);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,1);//--set pre-charge period
 	OLED_WR_Byte(0xF1,1);//--Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
 	OLED_WR_Byte(0xDA,1);//--set COM pins
 	OLED_WR_Byte(0x12,1);//
 	OLED_WR_Byte(0xDB,1);//--set vcomh
//    OLED_WR_Byte(0x40,1);//--Set VCOM Deselect Level
    OLED_WR_Byte(0x30,1);//
 	OLED_WR_Byte(0x8D,1);//--set charge pump disable
	OLED_WR_Byte(0x14,1);//--set(0x10) disable
 	OLED_WR_Byte(0xaf,1);//--turn on oled panel
}
/*****************************************************************************
函数名称 : OLED_Clear
功能描述 : OLED清屏
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void OLED_Clear(void)
{
  uint8_t i,n;              //定义变量
  for(i=0; i<8; i++)
  {
    OLED_WR_Byte(0xb0+i,1); //设置页地址（0~7）
    OLED_WR_Byte(0x00,1);   //设置显示位置—列低地址
    OLED_WR_Byte(0x10,1);   //设置显示位置—列高地址
    for(n=0; n<128; n++)OLED_WR_Byte(0x00,0); //写0x00到屏幕寄存器上
  }
}


/*****************************************************************************
函数名称 : OLED_Clear
功能描述 : OLED清屏
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void OLED_Clear_ONE_ROW(uint8_t i)
{
    uint8_t n;              //定义变量
    OLED_WR_Byte(0xb0+i,1); //设置页地址（0~7）
    OLED_WR_Byte(0x00,1);   //设置显示位置—列低地址
    OLED_WR_Byte(0x10,1);   //设置显示位置—列高地址
    for(n=0; n<128; n++)OLED_WR_Byte(0x00,0); //写0x00到屏幕寄存器上
}
///*****************************************************************************
//函数名称 : OLED_Clear_part
//功能描述 : OLED局部清屏
//输入参数 : x0：起始列地址（0~127）
//					 y0：起始页地址（0~7）
//					 x1：终止列地址（1~128）
//					 y1：终止页地址（1~8）
//返回参数 : 无
//使用说明 : 无
//*****************************************************************************/
//void OLED_Clear_part(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1)
//{
//  uint8_t i,n;              //定义变量
//  for(i=y0; i<y1; i++)
//  {
//    OLED_WR_Byte(0xb0+i,1); //设置页地址（0~7）
//    OLED_WR_Byte(0x00,1);   //设置显示位置—列低地址
//    OLED_WR_Byte(0x10,1);   //设置显示位置—列高地址
//    for(n=x0; n<x1; n++)OLED_WR_Byte(0x00,0); //写0x00到屏幕寄存器上
//  }
//}
/*****************************************************************************
函数名称 : OLED_SetPos
功能描述 : 设置开始的光标位置
输入参数 : x，y：位置
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void OLED_SetPos(uint8_t x, uint8_t y)
{
	OLED_WR_Byte(0xb0+y,1);             //写入页地址
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,1); //写入列低地址
	OLED_WR_Byte(x&0x0f,1);             //写入列高地址
}
/*****************************************************************************
函数名称 : OLED_ON
功能描述 : 将OLED从休眠中唤醒
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/ 
/*void OLED_ON(void)
{
  OLED_WR_Byte(0X8D,1);  //设置电荷泵
  OLED_WR_Byte(0X14,1);  //开启电荷泵
  OLED_WR_Byte(0XAF,1);  //OLED唤醒
}*/
/*****************************************************************************
函数名称 : OLED_OFF
功能描述 : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/ 
/*void OLED_OFF(void)
{
  OLED_WR_Byte(0X8D,1);  //设置电荷泵
  OLED_WR_Byte(0X10,1);  //关闭电荷泵
  OLED_WR_Byte(0XAE,1);  //OLED休眠
}*/
/*****************************************************************************
函数名称 : OLED_ShowChar
功能描述 : 显示6*8或8*16一个标准ASCII字符串
输入参数 : x：起始列
					 y：起始页，TextSize = 16占两页；TextSize = 8占1页
					 ch：字符
返回参数 : 无
使用说明 : 无
*****************************************************************************/ 
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t ch, uint8_t TextSize)
{
  uint8_t c=0,i=0;
  c = ch-' ';//获取字符的偏移量	
	if(x>Max_Column-1)//如果列书超出了范围，就从下2页的第0列开始
	{
		x=0;
		y=y+2;
	}
  if(TextSize==16)//字符大小如果为 2 = 8*16
  {
		OLED_SetPos(x,y);//从x y 开始画点
    for(i=0; i<8; i++)//循环8次 占8列
      OLED_WR_Byte(F8X16[c*16+i],0);//找出字符 c 的数组位置，先在第一页把列画完
		OLED_SetPos(x,y+1);//页数加1
		for(i=0; i<8; i++)//循环8次
      OLED_WR_Byte(F8X16[c*16+i+8],0);//把第二页的列数画完
  }
	else
  {//字符大小为 6 = 6*8
		OLED_SetPos(x,y);//一页就可以画完
    for(i=0; i<6; i++)//循环6次 ，占6列
      OLED_WR_Byte(F6x8[c][i],0);//把字符画完
  }
}
/*****************************************************************************
函数名称 : OLED_ShowStr
功能描述 : 显示字符串
输入参数 : x：起始列
					 y：起始页
					 *ch：第一个字符首地址
           TextSize：字符大小(1:6*8 ; 2:8*16)
返回参数 : 无
使用说明 : 无
*****************************************************************************/ 
void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t *ch, uint8_t TextSize)
{
  uint8_t j = 0;//定义变量
	while(ch[j] != '\0')//如果不是最后一个字符
	{		
		OLED_ShowChar(x,y,ch[j],TextSize);//显示字符
		if(TextSize==8)
		{
			x += 6;//列数加6 ，一个字符的列数占6
			if(x > 122)  //如果x超过128，切换页，从该页的第一列显示
			{
				x = 0;  
				y += 2;  
			}  		
			j++;  //下一个字符
		}
		else
		{
			x += 8;//列数加8 ，一个字符的列数占8
			if(x > 120)  //如果x超过128，切换页，从该页的第一列显示
			{
				x = 0;  
				y += 2;  
			}  		
			j++;  //下一个字符
		}
	}
}
/*****************************************************************************
函数名称 : oled_pow
功能描述 : 计算m^n
输入参数 : m：输入的一个数   n：输入数的次方
返回参数 : result：一个数的n次方
使用说明 : 无
*****************************************************************************/ 
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}				  
/*****************************************************************************
函数名称 : OLED_ShowNum
功能描述 : 在指定的位置，显示一个指定长度大小的数
输入参数 : x：起始列
					 y：起始页
					 num：数字
					 len：数字的长度
					 TextSize：字符大小(1:6*8 ; 2:8*16)
返回参数 : 无
使用说明 : 无
*****************************************************************************/ 
void OLED_ShowNum(uint8_t x,uint8_t y,int num,uint8_t len,uint8_t TextSize)
{         	
	uint8_t i,t,temp;  //定义变量
	uint8_t enshow=0;		//定义变量
	if(TextSize==8)
		i = 6;
	else
		i = 8;
	if(num<0)  //要显示的数小于0
	{
		num = -num;
		OLED_ShowChar(x,y,'-',TextSize);
		for(t=0;t<len;t++)
		{
			temp=(num/oled_pow(10,len-t-1))%10;//取出输入数的每个位，由高到低
			if(enshow==0&&t<(len-1)) //enshow：是否为第一个数；t<(len-1)：判断是否为最后一个数
			{
				if(temp==0) //如果该数为0 
				{
					OLED_ShowChar(x+i*(t+1),y,' ',TextSize);//显示 0 ；x+(size2/2)*t根据字体大小偏移的列数（8）
					continue; //跳过剩下语句，继续重复循环（避免重复显示）
				}else enshow=1; 
			}
			OLED_ShowChar(x+i*(t+1),y,temp+'0',TextSize); //显示一个位；x+(size2/2)*t根据字体大小偏移的列数（8）
		}
	}
	else  //要显示的数大于0
	{
		for(t=0;t<len;t++)
		{
			temp=(num/oled_pow(10,len-t-1))%10;//取出输入数的每个位，由高到低
			if(enshow==0&&t<(len-1)) //enshow：是否为第一个数；t<(len-1)：判断是否为最后一个数
			{
				if(temp==0) //如果该数为0 
				{
					OLED_ShowChar(x+i*t,y,' ',TextSize);//显示 0 ；x+(size2/2)*t根据字体大小偏移的列数（8）
					continue; //跳过剩下语句，继续重复循环（避免重复显示）
				}else enshow=1; 
		 	}
			OLED_ShowChar(x+i*t,y,temp+'0',TextSize); //显示一个位；x+(size2/2)*t根据字体大小偏移的列数（8）
		}
	}
} 
/*****************************************************************************
函数名称 : OLED_ShowCHinese
功能描述 : 显示中文
输入参数 : x：起始列，一个字占16列 y：起始页，一个字占两页 no：字体的序列号
返回参数 : 无
使用说明 : 无
*****************************************************************************/ 
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0; //定义变量
	OLED_SetPos(x,y);	//从 x y 开始画点，先画第一页
    for(t=0;t<16;t++) //循环16次，画第一页的16列
		{
				OLED_WR_Byte(Hzk[2*no][t],0);//画no在数组位置的第一页16列的点
				adder+=1; //数组地址加1
     }	
		OLED_SetPos(x,y+1); //画第二列
    for(t=0;t<16;t++)//循环16次，画第二页的16列
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],0);//画no在数组位置的第二页16列的点
				adder+=1;//数组地址加1
      }					
}

/*****************************************************************************
函数名称 : OLED_DrawBMP
功能描述 : 显示图片
输入参数 : x0：起始列地址（0~127）
					 y0：起始页地址（0~7）
					 x1：终止列地址（1~128）
					 y1：终止页地址（1~8）
				   BMP[]：存放图片代码的数组
返回参数 : 无
使用说明 : 无
*****************************************************************************/ 
void OLED_DrawBMP(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[])
{
  uint16_t j=0;  //定义变量
  uint8_t x,y;   //定义变量
 
  if(y1%8==0)    //判断终止页是否为8的整数倍
    y = y1/8;
  else
    y = y1/8 + 1;
  for(y=y0; y<y1; y++)   //从起始页开始，画到终止页
  {
    OLED_SetPos(x0,y);   //在页的起始列开始画
    for(x=x0; x<x1; x++) //画x1 - x0 列
    {
      OLED_WR_Byte(BMP[j++],0);//画图片的点
    }
  }
}
