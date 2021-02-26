/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F19196
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB             :  MPLAB X 5.45

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
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

#include "pin_manager.h"





void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATE = 0x21;
    LATD = 0x00;
    LATA = 0x00;
    LATF = 0x00;
    LATB = 0x00;
    LATG = 0x00;
    LATC = 0x18;
    LATH = 0x0C;

    /**
    TRISx registers
    */
    TRISE = 0xF2;
    TRISF = 0xFF;
    TRISA = 0xDF;
    TRISG = 0xDB;
    TRISB = 0xFF;
    TRISH = 0x0B;
    TRISC = 0x67;
    TRISD = 0xFF;

    /**
    ANSELx registers
    */
    ANSELD = 0x00;
    ANSELC = 0xA5;
    ANSELB = 0xFF;
    ANSELE = 0xC0;
    ANSELG = 0xDD;
    ANSELF = 0x00;
    ANSELA = 0xDF;

    /**
    WPUx registers
    */
    WPUD = 0x00;
    WPUF = 0x00;
    WPUE = 0x00;
    WPUB = 0x00;
    WPUG = 0x00;
    WPUA = 0x00;
    WPUC = 0x40;
    WPUH = 0x00;

    /**
    ODx registers
    */
    ODCONE = 0x00;
    ODCONF = 0x00;
    ODCONA = 0x00;
    ODCONG = 0x00;
    ODCONB = 0x00;
    ODCONH = 0x00;
    ODCONC = 0x00;
    ODCOND = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xDF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0xFB;
    SLRCONF = 0xFF;
    SLRCONG = 0xDF;
    SLRCONH = 0x0F;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLD = 0xFF;
    INLVLE = 0xFB;
    INLVLF = 0xFF;
    INLVLG = 0xFF;
    INLVLH = 0x0F;





   
    
	
    RX2PPS = 0x31;   //RG1->EUSART2:RX2;    
    RC7PPS = 0x0D;   //RC7->EUSART1:TX1;    
    RG2PPS = 0x0F;   //RG2->EUSART2:TX2;    
}
  
void PIN_MANAGER_IOC(void)
{   
}

/**
 End of File
*/