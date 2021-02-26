/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "../mcc_generated_files/pin_manager.h"
#include "../mcc_generated_files/eusart2.h"
#include "../mcc_generated_files/eusart1.h"
#include "../mcc_generated_files/device_config.h"
#include<stdint.h>

uint8_t sht30_addr =0x44;

#define write 0
#define read  1

extern uint8_t humiture_buff1[20];
extern uint8_t humiture_buff2[20];
extern uint8_t Refresh_SHT30_Data;
extern uint8_t send_data_fleg;
extern uint8_t Temperature_L;
extern uint8_t Humidity_L;
extern uint8_t Temperature_H;
extern uint8_t Humidity_H;
 
void IIC_ACK(void);
void IIC_NACK(void);
uint8_t IIC_wait_ACK(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_SendByte(uint8_t byte);
uint8_t IIC_RcvByte(void);
void SHT30_read_result(uint8_t addr);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

