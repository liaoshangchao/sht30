/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F19196
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SCL aliases
#define SCL_TRIS                 TRISCbits.TRISC3
#define SCL_LAT                  LATCbits.LATC3
#define SCL_PORT                 PORTCbits.RC3
#define SCL_WPU                  WPUCbits.WPUC3
#define SCL_OD                   ODCONCbits.ODCC3
#define SCL_ANS                  ANSELCbits.ANSC3
#define SCL_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SCL_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SCL_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SCL_GetValue()           PORTCbits.RC3
#define SCL_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SCL_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define SCL_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define SCL_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define SCL_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define SCL_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define SCL_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set SDA aliases
#define SDA_TRIS                 TRISCbits.TRISC4
#define SDA_LAT                  LATCbits.LATC4
#define SDA_PORT                 PORTCbits.RC4
#define SDA_WPU                  WPUCbits.WPUC4
#define SDA_OD                   ODCONCbits.ODCC4
#define SDA_ANS                  ANSELCbits.ANSC4
#define SDA_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SDA_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SDA_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SDA_GetValue()           PORTCbits.RC4
#define SDA_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SDA_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define SDA_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define SDA_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define SDA_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define SDA_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define SDA_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set KEY aliases
#define KEY_TRIS                 TRISCbits.TRISC6
#define KEY_LAT                  LATCbits.LATC6
#define KEY_PORT                 PORTCbits.RC6
#define KEY_WPU                  WPUCbits.WPUC6
#define KEY_OD                   ODCONCbits.ODCC6
#define KEY_ANS                  ANSELCbits.ANSC6
#define KEY_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define KEY_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define KEY_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define KEY_GetValue()           PORTCbits.RC6
#define KEY_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define KEY_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define KEY_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define KEY_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define KEY_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define KEY_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define KEY_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define KEY_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

// get/set RST_WIFI aliases
#define RST_WIFI_TRIS                 TRISEbits.TRISE0
#define RST_WIFI_LAT                  LATEbits.LATE0
#define RST_WIFI_PORT                 PORTEbits.RE0
#define RST_WIFI_WPU                  WPUEbits.WPUE0
#define RST_WIFI_OD                   ODCONEbits.ODCE0
#define RST_WIFI_ANS                  ANSELEbits.ANSE0
#define RST_WIFI_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define RST_WIFI_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define RST_WIFI_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define RST_WIFI_GetValue()           PORTEbits.RE0
#define RST_WIFI_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define RST_WIFI_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define RST_WIFI_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define RST_WIFI_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define RST_WIFI_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define RST_WIFI_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define RST_WIFI_SetAnalogMode()      do { ANSELEbits.ANSE0 = 1; } while(0)
#define RST_WIFI_SetDigitalMode()     do { ANSELEbits.ANSE0 = 0; } while(0)

// get/set LED aliases
#define LED_TRIS                 TRISEbits.TRISE3
#define LED_LAT                  LATEbits.LATE3
#define LED_PORT                 PORTEbits.RE3
#define LED_WPU                  WPUEbits.WPUE3
#define LED_OD                   ODCONEbits.ODCE3
#define LED_ANS                  ANSELEbits.ANSE3
#define LED_SetHigh()            do { LATEbits.LATE3 = 1; } while(0)
#define LED_SetLow()             do { LATEbits.LATE3 = 0; } while(0)
#define LED_Toggle()             do { LATEbits.LATE3 = ~LATEbits.LATE3; } while(0)
#define LED_GetValue()           PORTEbits.RE3
#define LED_SetDigitalInput()    do { TRISEbits.TRISE3 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISEbits.TRISE3 = 0; } while(0)
#define LED_SetPullup()          do { WPUEbits.WPUE3 = 1; } while(0)
#define LED_ResetPullup()        do { WPUEbits.WPUE3 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONEbits.ODCE3 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONEbits.ODCE3 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELEbits.ANSE3 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELEbits.ANSE3 = 0; } while(0)

// get/set RG1 procedures
#define RG1_SetHigh()            do { LATGbits.LATG1 = 1; } while(0)
#define RG1_SetLow()             do { LATGbits.LATG1 = 0; } while(0)
#define RG1_Toggle()             do { LATGbits.LATG1 = ~LATGbits.LATG1; } while(0)
#define RG1_GetValue()              PORTGbits.RG1
#define RG1_SetDigitalInput()    do { TRISGbits.TRISG1 = 1; } while(0)
#define RG1_SetDigitalOutput()   do { TRISGbits.TRISG1 = 0; } while(0)
#define RG1_SetPullup()             do { WPUGbits.WPUG1 = 1; } while(0)
#define RG1_ResetPullup()           do { WPUGbits.WPUG1 = 0; } while(0)
#define RG1_SetAnalogMode()         do { ANSELGbits.ANSG1 = 1; } while(0)
#define RG1_SetDigitalMode()        do { ANSELGbits.ANSG1 = 0; } while(0)

// get/set RG2 procedures
#define RG2_SetHigh()            do { LATGbits.LATG2 = 1; } while(0)
#define RG2_SetLow()             do { LATGbits.LATG2 = 0; } while(0)
#define RG2_Toggle()             do { LATGbits.LATG2 = ~LATGbits.LATG2; } while(0)
#define RG2_GetValue()              PORTGbits.RG2
#define RG2_SetDigitalInput()    do { TRISGbits.TRISG2 = 1; } while(0)
#define RG2_SetDigitalOutput()   do { TRISGbits.TRISG2 = 0; } while(0)
#define RG2_SetPullup()             do { WPUGbits.WPUG2 = 1; } while(0)
#define RG2_ResetPullup()           do { WPUGbits.WPUG2 = 0; } while(0)
#define RG2_SetAnalogMode()         do { ANSELGbits.ANSG2 = 1; } while(0)
#define RG2_SetDigitalMode()        do { ANSELGbits.ANSG2 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/