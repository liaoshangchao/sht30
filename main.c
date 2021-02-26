/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F19196
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "sht30/sht30.h"
#include "OLED/OLED.h"


#include "Tuya_sdk/mcu_api.h"
#include "Tuya_sdk/protocol.h"
#include "Tuya_sdk/system.h"
#include "Tuya_sdk/wifi.h"

#define WIFI_CONTROL_SELF_MODE 
extern bool Connect_Flag;
bool start_Flag = 0;
bool Charge_Flag = false;
extern bool updata_flag;
extern bool connect_statue;
unsigned char result;

void Reset_WIFI_SSID();
void task(); 
void LED_Statue();
void Show_Temp_Hum();
void Menu_Loge();
unsigned char Beijing_time[15];
extern unsigned int wifi_sht30_data[4];
/*
                         Main application
 */


void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
                  
    RST_WIFI_SetLow(); 
    
    //�ⲿOLED��ʼ��
    __delay_ms(1000);
    OLED_Init();         //OLED��ʼ��
	OLED_Clear();        //OLED����
    
    RST_WIFI_SetHigh();
    
    //wifiģ��Э���ʼ��
    wifi_protocol_init();
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
     
    Show_Temp_Hum();
    
    while (1)
    {
        // Add your application code

        //���WIFI���ڷ�����������
        wifi_uart_service();
        
        if (  updata_flag == 1   )     //�ж��Ƿ�ʱ�䣬�ϱ�״̬��Ϣ��Ĭ�϶�ʱ��1s�ж�һ�Σ�
        {  
            
            SHT30_read_result(sht30_addr);      //��ȡ��ʪ��ֵ
            updata_flag = 0;                    //����ϱ���־
            all_data_update();                  //�ϱ�������Ϣ
//            printf("�����ϱ���\n");
        }
        
        //������������Ϣ����
        Reset_WIFI_SSID();
        
//        //LED״ָ̬ʾ
//        LED_Statue();
  
        //��ʾ�м䣨Tuya��ʪ�ȣ�����
        Menu_Loge();
        
        //wifi״̬OLED��ʾ
		get_wifi_status(result);
               
////        //��ȡ����ʱ��
//        mcu_get_system_time();
//        mcu_write_rtctime(Beijing_time);

    }
}
/**
 End of File
*/


/*****************************************************************************
�������� : Menu_Loge
�������� : ������ʾ
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void Menu_Loge()
{
	OLED_ShowStr(24,1,"Tuya",16);
	OLED_ShowCHinese(56,1,0);
	OLED_ShowCHinese(72,1,2);
	OLED_ShowCHinese(88,1,1);
}

/*****************************************************************************
�������� : Reset_WIFI_SSID()
�������� : ���������Ϣ����
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void Reset_WIFI_SSID()  
{
    if( KEY_GetValue() == 0 )
    {
        __delay_ms(5);
        if( KEY_GetValue() == 0 )
        {
            while(!KEY_GetValue());
            mcu_reset_wifi();                       //�����������
            Connect_Flag = 0 ;
//            if( mcu_get_reset_wifi_flag() )         //�ж�������������Ƿ�ɹ�
//            {
//                printf("����������óɹ�\n");
                mcu_set_wifi_mode(0);           //����Ϊsmartconfig����ģʽ
                OLED_Clear();        //OLED���� 	
//            }
        }
    }
}

/*****************************************************************************
�������� : LED_Statue()
�������� : ledָʾ����״̬
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void LED_Statue()
{
    if ( Connect_Flag == 0 )
    {
        if( connect_statue == 1 )
        {
            LED_Toggle();
        }
    }
    else
    {
        LED_SetHigh();
    }
}

/*****************************************************************************
�������� : Show_Temp_Hum
�������� : ��ʾ��ʪ��ֵ
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void Show_Temp_Hum()
{
	OLED_Clear();
	Menu_Loge();
	SHT30_read_result(sht30_addr);
	wifi_uart_service();
	get_wifi_status(result);
	wifi_uart_service();

}


/*****************************************************************************
�������� : Show_Fuction_One
�������� : ��ʾ��ʪ��ֵ,
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void Show_Fuction_One()
{
    //��ʾ�м䣨Tuya��ʪ�ȣ�����
    Menu_Loge();

    //wifi״̬OLED��ʾ
    get_wifi_status(result);

//    //��ȡ����ʱ��(�����У׼λ����ʱ��))
//    mcu_get_green_time();
//    mcu_get_greentime(Beijing_time);
}


























