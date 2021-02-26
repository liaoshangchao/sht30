/**********************************Copyright (c)**********************************
**                       ��Ȩ���� (C), 2015-2020, Ϳѻ�Ƽ�
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    mcu_api.c
 * @author  Ϳѻ�ۺ�Э�鿪����
 * @version v2.5.6
 * @date    2020.12.16
 * @brief   �û���Ҫ�������õĺ������ڸ��ļ���
 */

/****************************** �������� ������ *******************************
����MCU���ͺͱ��뻷�����ֶ��������Դ˴�������ο����û������аѿ����մ���������
Ϳѻ����MCU���ܽ������
******************************************************************************/

#define MCU_API_GLOBAL

#include "wifi.h"


/**
 * @brief  hexתbcd
 * @param[in] {Value_H} ���ֽ�
 * @param[in] {Value_L} ���ֽ�
 * @return ת����ɺ�����
 */
unsigned char hex_to_bcd(unsigned char Value_H,unsigned char Value_L)
{
    unsigned char bcd_value;
    
    if((Value_H >= '0') && (Value_H <= '9'))
        Value_H -= '0';
    else if((Value_H >= 'A') && (Value_H <= 'F'))
        Value_H = Value_H - 'A' + 10;
    else if((Value_H >= 'a') && (Value_H <= 'f'))
        Value_H = Value_H - 'a' + 10;
     
    bcd_value = Value_H & 0x0f;
    
    bcd_value <<= 4;
    if((Value_L >= '0') && (Value_L <= '9'))
        Value_L -= '0';
    else if((Value_L >= 'A') && (Value_L <= 'F'))
        Value_L = Value_L - 'a' + 10;
    else if((Value_L >= 'a') && (Value_L <= 'f'))
        Value_L = Value_L - 'a' + 10;
    
    bcd_value |= Value_L & 0x0f;

    return bcd_value;
}

/**
 * @brief  ���ַ�������
 * @param[in] {str} �ַ�����ַ
 * @return ���ݳ���
 */
unsigned long my_strlen(unsigned char *str)  
{
    unsigned long len = 0;
    if(str == NULL) { 
        return 0;
    }
    
    for(len = 0; *str ++ != '\0'; ) {
        len ++;
    }
    
    return len;
}

/**
 * @brief  ��src��ָ�ڴ������ǰcount���ֽ����ó��ַ�c
 * @param[out] {src} �����õ��ڴ��׵�ַ
 * @param[in] {ch} ���õ��ַ�
 * @param[in] {count} ���õ��ڴ泤��
 * @return �����õ��ڴ��׵�ַ
 */
void *my_memset(void *src,unsigned char ch,unsigned short count)
{
    unsigned char *tmp = (unsigned char *)src;
    
    if(src == NULL) {
        return NULL;
    }
    
    while(count --) {
        *tmp ++ = ch;
    }
    
    return src;
}

/**
 * @brief  �ڴ濽��
 * @param[out] {dest} Ŀ���ַ
 * @param[in] {src} Դ��ַ
 * @param[in] {count} �������ݸ���
 * @return ���ݴ�������Դ��ַ
 */
void *my_memcpy(void *dest, const void *src, unsigned short count)  
{  
    unsigned char *pdest = (unsigned char *)dest;  
    const unsigned char *psrc  = (const unsigned char *)src;  
    unsigned short i;
    
    if(dest == NULL || src == NULL) { 
        return NULL;
    }
    
    if((pdest <= psrc) || (pdest > psrc + count)) {  
        for(i = 0; i < count; i ++) {  
            pdest[i] = psrc[i];  
        }  
    }else {
        for(i = count; i > 0; i --) {  
            pdest[i - 1] = psrc[i - 1];  
        }  
    }  
    
    return dest;  
}

/**
 * @brief  �ַ�������
 * @param[in] {dest} Ŀ���ַ
 * @param[in] {src} Դ��ַ
 * @return ���ݴ�������Դ��ַ
 */
char *my_strcpy(char *dest, const char *src)  
{
    if((NULL == dest) || (NULL == src)) {
        return NULL;
    }
    
    char *p = dest;
    while(*src!='\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return p;
}

/**
 * @brief  �ַ����Ƚ�
 * @param[in] {s1} �ַ��� 1
 * @param[in] {s2} �ַ��� 2
 * @return ��С�Ƚ�ֵ
 * -         0:s1=s2
 * -         <0:s1<s2
 * -         >0:s1>s2
 */
int my_strcmp(char *s1 , char *s2)
{
    while( *s1 && *s2 && *s1 == *s2 ) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

/**
 * @brief  ��int���Ͳ���ĸ��ֽ�
 * @param[in] {number} 4�ֽ�ԭ����
 * @param[out] {value} ������ɺ�4�ֽ�����
 * @return Null
 */
void int_to_byte(unsigned long number,unsigned char value[4])
{
    value[0] = number >> 24;
    value[1] = number >> 16;
    value[2] = number >> 8;
    value[3] = number & 0xff;
}

/**
 * @brief  ��4�ֽںϲ�Ϊ1��32bit����
 * @param[in] {value} 4�ֽ�����
 * @return �ϲ���ɺ��32bit����
 */
unsigned long byte_to_int(const unsigned char value[4])
{
    unsigned long nubmer = 0;

    nubmer = (unsigned long)value[0];
    nubmer <<= 8;
    nubmer |= (unsigned long)value[1];
    nubmer <<= 8;
    nubmer |= (unsigned long)value[2];
    nubmer <<= 8;
    nubmer |= (unsigned long)value[3];
    
    return nubmer;
}

/**
 * @brief  raw��dp�����ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @param[in] {len} ���ݳ���
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_raw_update(unsigned char dpid,const unsigned char value[],unsigned short len)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_RAW);
    //
    send_len = set_wifi_uart_byte(send_len,len / 0x100);
    send_len = set_wifi_uart_byte(send_len,len % 0x100);
    //
    send_len = set_wifi_uart_buffer(send_len,(unsigned char *)value,len);
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  bool��dp�����ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵ
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_bool_update(unsigned char dpid,unsigned char value)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_BOOL);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,1);
    //
    if(value == FALSE) {
        send_len = set_wifi_uart_byte(send_len,FALSE);
    }else {
        send_len = set_wifi_uart_byte(send_len,1);
    }
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD, MCU_TX_VER, send_len);
    
    return SUCCESS;
}

/**
 * @brief  value��dp�����ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵ
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_VALUE);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,4);
    //
    send_len = set_wifi_uart_byte(send_len,value >> 24);
    send_len = set_wifi_uart_byte(send_len,value >> 16);
    send_len = set_wifi_uart_byte(send_len,value >> 8);
    send_len = set_wifi_uart_byte(send_len,value & 0xff);
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  string��dp�����ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @param[in] {len} ���ݳ���
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_string_update(unsigned char dpid,const unsigned char value[],unsigned short len)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_STRING);
    //
    send_len = set_wifi_uart_byte(send_len,len / 0x100);
    send_len = set_wifi_uart_byte(send_len,len % 0x100);
    //
    send_len = set_wifi_uart_buffer(send_len,(unsigned char *)value,len);
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  enum��dp�����ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵ
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_enum_update(unsigned char dpid,unsigned char value)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_ENUM);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,1);
    //
    send_len = set_wifi_uart_byte(send_len,value);
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  fault��dp�����ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵ
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_fault_update(unsigned char dpid,unsigned long value)
{
    unsigned short send_len = 0;
     
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_BITMAP);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    
    if((value | 0xff) == 0xff) {
        send_len = set_wifi_uart_byte(send_len,1);
        send_len = set_wifi_uart_byte(send_len,value);
    }else if((value | 0xffff) == 0xffff) {
        send_len = set_wifi_uart_byte(send_len,2);
        send_len = set_wifi_uart_byte(send_len,value >> 8);
        send_len = set_wifi_uart_byte(send_len,value & 0xff);
    }else {
        send_len = set_wifi_uart_byte(send_len,4);
        send_len = set_wifi_uart_byte(send_len,value >> 24);
        send_len = set_wifi_uart_byte(send_len,value >> 16);
        send_len = set_wifi_uart_byte(send_len,value >> 8);
        send_len = set_wifi_uart_byte(send_len,value & 0xff);
    }    
    
    wifi_uart_write_frame(STATE_UPLOAD_CMD, MCU_TX_VER, send_len);

    return SUCCESS;
}

#ifdef MCU_DP_UPLOAD_SYN
/**
 * @brief  raw��dp����ͬ���ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @param[in] {len} ���ݳ���
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_raw_update_syn(unsigned char dpid,const unsigned char value[],unsigned short len)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_RAW);
    //
    send_len = set_wifi_uart_byte(send_len,len / 0x100);
    send_len = set_wifi_uart_byte(send_len,len % 0x100);
    //
    send_len = set_wifi_uart_buffer(send_len,(unsigned char *)value,len);
    
    wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  bool��dp����ͬ���ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_bool_update_syn(unsigned char dpid,unsigned char value)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_BOOL);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,1);
    //
    if(value == FALSE) {
        send_len = set_wifi_uart_byte(send_len,FALSE);
    }else {
        send_len = set_wifi_uart_byte(send_len,1);
    }
    
    wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD, MCU_TX_VER, send_len);
    
    return SUCCESS;
}

/**
 * @brief  value��dp����ͬ���ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_value_update_syn(unsigned char dpid,unsigned long value)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_VALUE);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,4);
    //
    send_len = set_wifi_uart_byte(send_len,value >> 24);
    send_len = set_wifi_uart_byte(send_len,value >> 16);
    send_len = set_wifi_uart_byte(send_len,value >> 8);
    send_len = set_wifi_uart_byte(send_len,value & 0xff);
    
    wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD, MCU_TX_VER, send_len);
    
    return SUCCESS;
}

/**
 * @brief  string��dp����ͬ���ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @param[in] {len} ���ݳ���
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_string_update_syn(unsigned char dpid,const unsigned char value[],unsigned short len)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    //
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_STRING);
    //
    send_len = set_wifi_uart_byte(send_len,len / 0x100);
    send_len = set_wifi_uart_byte(send_len,len % 0x100);
    //
    send_len = set_wifi_uart_buffer(send_len,(unsigned char *)value,len);
    
    wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  enum��dp����ͬ���ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_enum_update_syn(unsigned char dpid,unsigned char value)
{
    unsigned short send_len = 0;
    
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_ENUM);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    send_len = set_wifi_uart_byte(send_len,1);
    
    send_len = set_wifi_uart_byte(send_len,value);
    
    wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_TX_VER,send_len);
    
    return SUCCESS;
}

/**
 * @brief  fault��dp����ͬ���ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_fault_update_syn(unsigned char dpid,unsigned long value)
{
    unsigned short send_len = 0;
     
    if(stop_update_flag == ENABLE)
        return SUCCESS;
    
    send_len = set_wifi_uart_byte(send_len,dpid);
    send_len = set_wifi_uart_byte(send_len,DP_TYPE_BITMAP);
    //
    send_len = set_wifi_uart_byte(send_len,0);
    
    if((value | 0xff) == 0xff) {
        send_len = set_wifi_uart_byte(send_len,1);
        send_len = set_wifi_uart_byte(send_len,value);
    }else if((value | 0xffff) == 0xffff) {
        send_len = set_wifi_uart_byte(send_len,2);
        send_len = set_wifi_uart_byte(send_len,value >> 8);
        send_len = set_wifi_uart_byte(send_len,value & 0xff);
    }else {
        send_len = set_wifi_uart_byte(send_len,4);
        send_len = set_wifi_uart_byte(send_len,value >> 24);
        send_len = set_wifi_uart_byte(send_len,value >> 16);
        send_len = set_wifi_uart_byte(send_len,value >> 8);
        send_len = set_wifi_uart_byte(send_len,value & 0xff);
    }    
    
    wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_TX_VER,send_len);

    return SUCCESS;
}
#endif

/**
 * @brief  mcu��ȡbool���·�dpֵ
 * @param[in] {value} dp���ݻ�������ַ
 * @param[in] {len} dp���ݳ���
 * @return ��ǰdpֵ
 * @note   Null
 */
unsigned char mcu_get_dp_download_bool(const unsigned char value[],unsigned short len)
{
    return(value[0]);
}

/**
 * @brief  mcu��ȡenum���·�dpֵ
 * @param[in] {value} dp���ݻ�������ַ
 * @param[in] {len} dp���ݳ���
 * @return ��ǰdpֵ
 * @note   Null
 */
unsigned char mcu_get_dp_download_enum(const unsigned char value[],unsigned short len)
{
    return(value[0]);
}

/**
 * @brief  mcu��ȡvalue���·�dpֵ
 * @param[in] {value} dp���ݻ�������ַ
 * @param[in] {len} dp���ݳ���
 * @return ��ǰdpֵ
 * @note   Null
 */
unsigned long mcu_get_dp_download_value(const unsigned char value[],unsigned short len)
{
    return(byte_to_int(value));
}

/**
 * @brief  ���ڽ��������ݴ洦��
 * @param[in] {value} �����յ���1�ֽ�����
 * @return Null
 * @note   ��MCU���ڴ������е��øú���,�������յ���������Ϊ��������
 *          ���ڴ��ڽ����ж��е���uart_receive_input(value),����������MCU_SDK����,�û����������д���,
 */
void uart_receive_input(unsigned char value)
{
    
    if(1 == rx_buf_out - rx_buf_in) {
        //���ڽ��ջ�������
    }else if((rx_buf_in > rx_buf_out) && ((rx_buf_in - rx_buf_out) >= sizeof(wifi_uart_rx_buf))) {
        //���ڽ��ջ�������
    }else {
        //���ڽ��ջ���δ��
        if(rx_buf_in >= (unsigned char *)(wifi_uart_rx_buf + sizeof(wifi_uart_rx_buf))) {
            rx_buf_in = (unsigned char *)(wifi_uart_rx_buf);
        }
        
        *rx_buf_in ++ = value;
    }
}

/**
 * @brief  ���ڽ��ն���ֽ������ݴ洦��
 * @param[in] {value} ����Ҫ���յ����ݵ�Դ��ַ
 * @param[in] {data_len} ����Ҫ���յ����ݵ����ݳ���
 * @return Null
 * @note   ����Ҫ֧��һ�ζ��ֽڻ��棬�ɵ��øú���
 *          ������Ҫһ�λ������ֽڴ������ݴ����ô˺���,����������MCU_SDK����,�û����������д��� 
 */
void uart_receive_buff_input(unsigned char value[], unsigned short data_len)
{
    unsigned short i = 0;
    for(i = 0; i < data_len; i++) {
        uart_receive_input(value[i]);
    }
}

/**
 * @brief  wifi�������ݴ������
 * @param  Null
 * @return Null
 * @note   ��MCU������whileѭ���е��øú���
 *          ��ֱ����main������while(1){}�����wifi_uart_service(),���øú�����Ҫ���κ������ж�
 */
void wifi_uart_service(void)
{
    static unsigned short rx_in = 0;
    unsigned short offset = 0;
    unsigned short rx_value_len = 0;
    
    while((rx_in < sizeof(wifi_data_process_buf)) && with_data_rxbuff() > 0) {
        wifi_data_process_buf[rx_in ++] = take_byte_rxbuff();
    }
    
    if(rx_in < PROTOCOL_HEAD)
        return;
    
    while((rx_in - offset) >= PROTOCOL_HEAD) {
        if(wifi_data_process_buf[offset + HEAD_FIRST] != FRAME_FIRST) {
            offset ++;
            continue;
        }
        
        if(wifi_data_process_buf[offset + HEAD_SECOND] != FRAME_SECOND) {
            offset ++;
            continue;
        }  
        
        if(wifi_data_process_buf[offset + PROTOCOL_VERSION] != MCU_RX_VER) {
            offset += 2;
            continue;
        }      
        
        rx_value_len = wifi_data_process_buf[offset + LENGTH_HIGH] * 0x100;
        rx_value_len += (wifi_data_process_buf[offset + LENGTH_LOW] + PROTOCOL_HEAD);
        if(rx_value_len > sizeof(wifi_data_process_buf) + PROTOCOL_HEAD) {
            offset += 3;
            continue;
        }
        
        if((rx_in - offset) < rx_value_len) {
            break;
        }
        
        //���ݽ������
        if(get_check_sum((unsigned char *)wifi_data_process_buf + offset,rx_value_len - 1) != wifi_data_process_buf[offset + rx_value_len - 1]) {
            //У�����
//            printf("crc error (crc:0x%X  but data:0x%X)\r\n",get_check_sum((unsigned char *)wifi_data_process_buf + offset,rx_value_len - 1),wifi_data_process_buf[offset + rx_value_len - 1]);
            offset += 3;
            continue;
        }
        
        data_handle(offset);
        offset += rx_value_len;
    }//end while

    rx_in -= offset;
    if(rx_in > 0) {
        my_memcpy((char *)wifi_data_process_buf, (const char *)wifi_data_process_buf + offset, rx_in);
    }
}

/**
 * @brief  Э�鴮�ڳ�ʼ������
 * @param  Null
 * @return Null
 * @note   ��MCU��ʼ�������е��øú���
 *          ����main���������wifi_protocol_init()���wifiЭ���ʼ��
 */
void wifi_protocol_init(void)
{
    rx_buf_in = (unsigned char *)wifi_uart_rx_buf;
    rx_buf_out = (unsigned char *)wifi_uart_rx_buf;
    
    stop_update_flag = DISABLE;
    
#ifndef WIFI_CONTROL_SELF_MODE
    wifi_work_state = WIFI_SATE_UNKNOW;
#endif
}



#ifndef WIFI_CONTROL_SELF_MODE
/**
 * @brief  MCU��ȡ��λwifi�ɹ���־
 * @param  Null
 * @return ��λ��־
 * -           0(RESET_WIFI_ERROR):ʧ��
 * -           1(RESET_WIFI_SUCCESS):�ɹ�
 * @note   1:MCU��������mcu_reset_wifi()����øú�����ȡ��λ״̬
 *         2:���Ϊģ���Դ���ģʽ,MCU������øú���
 */
unsigned char mcu_get_reset_wifi_flag(void)
{
    return reset_wifi_flag;
}

/**
 * @brief  MCU��������wifi����ģʽ
 * @param  Null
 * @return Null
 * @note   1:MCU��������,ͨ��mcu_get_reset_wifi_flag()������ȡ����wifi�Ƿ�ɹ�
 *         2:���Ϊģ���Դ���ģʽ,MCU������øú���
 */
void mcu_reset_wifi(void)
{
    reset_wifi_flag = RESET_WIFI_ERROR;
    
    wifi_uart_write_frame(WIFI_RESET_CMD, MCU_TX_VER, 0);
}

/**
 * @brief  ��ȡ����wifi״̬�ɹ���־
 * @param  Null
 * @return wifimode flag
 * -           0(SET_WIFICONFIG_ERROR):ʧ��
 * -           1(SET_WIFICONFIG_SUCCESS):�ɹ�
 * @note   1:MCU��������mcu_set_wifi_mode()����øú�����ȡ��λ״̬
 *         2:���Ϊģ���Դ���ģʽ,MCU������øú���
 */
unsigned char mcu_get_wifimode_flag(void)
{
    return set_wifimode_flag;
}

/**
 * @brief  MCU����wifi����ģʽ
 * @param[in] {mode} �����ģʽ
 * @ref        0(SMART_CONFIG):����smartconfigģʽ
 * @ref        1(AP_CONFIG):����APģʽ
 * @return Null
 * @note   1:MCU��������
 *         2:�ɹ���,���ж�set_wifi_config_state�Ƿ�ΪTRUE;TRUE��ʾΪ����wifi����ģʽ�ɹ�
 *         3:���Ϊģ���Դ���ģʽ,MCU������øú���
 */
void mcu_set_wifi_mode(unsigned char mode)
{
    unsigned char length = 0;
    
    set_wifimode_flag = SET_WIFICONFIG_ERROR;
    
    length = set_wifi_uart_byte(length, mode);
    
    wifi_uart_write_frame(WIFI_MODE_CMD, MCU_TX_VER, length);
}

/**
 * @brief  MCU������ȡ��ǰwifi����״̬
 * @param  Null
 * @return wifi work state
 * -          SMART_CONFIG_STATE: smartconfig����״̬
 * -          AP_STATE: AP����״̬
 * -          WIFI_NOT_CONNECTED: WIFI���óɹ���δ����·����
 * -          WIFI_CONNECTED: WIFI���óɹ�������·����
 * -          WIFI_CONN_CLOUD: WIFI�Ѿ��������Ʒ�����
 * -          WIFI_LOW_POWER: WIFI���ڵ͹���ģʽ
 * -          SMART_AND_AP_STATE: WIFI smartconfig&AP ģʽ
 * @note   ���Ϊģ���Դ���ģʽ,MCU������øú���
 */
unsigned char mcu_get_wifi_work_state(void)
{
    return wifi_work_state;
}
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  MCU��ȡ����ʱ��
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_get_green_time(void)
{
    wifi_uart_write_frame(GET_ONLINE_TIME_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU��ȡϵͳʱ��,����У�Ա���ʱ��
 * @param  Null
 * @return Null
 * @note   MCU����������ɺ���mcu_write_rtctime������У��rtcʱ��
 */
void mcu_get_system_time(void)
{
    wifi_uart_write_frame(GET_LOCAL_TIME_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef WIFI_TEST_ENABLE
/**
 * @brief  mcu����wifi���ܲ���
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_start_wifitest(void)
{
    wifi_uart_write_frame(WIFI_TEST_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef WIFI_HEARTSTOP_ENABLE
/**
 * @brief  ֪ͨWIFIģ��ر�����
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void wifi_heart_stop(void)
{
    wifi_uart_write_frame(HEAT_BEAT_STOP, MCU_TX_VER, 0);
}
#endif

#ifdef GET_WIFI_STATUS_ENABLE
/**
 * @brief  ��ȡ��ǰwifi����״̬
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_get_wifi_connect_status(void)
{
    wifi_uart_write_frame(GET_WIFI_STATUS_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef WIFI_STREAM_ENABLE
/**
 * @brief  ��������
 * @param[in] {id} ID��
 * @param[in] {buffer} ���Ͱ��ĵ�ַ
 * @param[in] {buf_len} ���Ͱ�����
 * @return ����������
 * -           0(ERROR): ʧ��
 * -           1(SUCCESS): �ɹ�
 * @note   MCU��Ҫ����ʵ�ָù���
 */
unsigned char stream_trans_send(unsigned int id, unsigned char *buffer, unsigned long buf_len)
{
    unsigned long map_offset = 0;
    unsigned int pack_num = 0;
    unsigned int rest_length = 0;

    if(stop_update_flag == ENABLE)
        return ERROR;

    pack_num = buf_len / STREM_PACK_LEN;
    rest_length = buf_len - pack_num * STREM_PACK_LEN;
    if (rest_length > 0) {
        pack_num++;
    }

    int this_len = STREM_PACK_LEN;
    for (int cnt = 0; cnt < pack_num; cnt++,map_offset += this_len) {
        if (cnt == pack_num - 1 && rest_length > 0) {
            this_len = rest_length;
        }else {
            this_len = STREM_PACK_LEN;
        }

        if(ERROR == stream_trans(id, map_offset, buffer + map_offset, this_len)) {
            //mcu���������У������Խ�����������
            //printf("is upgrade\n");
            return ERROR;
        }
        
//        #error "�������ʾ�����������������ʹ��룬��ɺ���ɾ������"
        /*  ���MCU����ʹ�ö���̻���̣߳����Խ��˺�������һ�������Ľ��̻��߳���ִ�У�����������ʾ�Ĵ���  */
        /*
        while(0xff == stream_status); //�ȴ�ģ��ظ�
        
        if(0x00 != stream_status) {
            //ʧ��  ���� stream_trans_send_result �����в鿴������
            return ERROR;
        }
        */
        
        /*  ���MCU��֧�ֶ���̻���̣߳�ʹ�ô˺���ʱÿ��ֻ��һ�������ݳ��Ȳ�����STREM_PACK_LEN����
        ������֮���� stream_trans_send_result �����д���ģ�鷵�صĽ�������ͳɹ�ʱ�ٴε��ô˺���������һ����ע���ƫ��Ҫ����  */
    }
    
    return SUCCESS;
}

/**
 * @brief  ���ͼ��������
 * @param[in] {id} ��ͼ������ỰID
 * @param[in] {sub_id} �ӵ�ͼID
 * @param[in] {sub_id_pro_mode} �ӵ�ͼID���ݴ���ʽ
 * @ref       0x00: �����ۼ�
 * @ref       0x01: ����ϴ�������
 * @param[in] {buffer} ���ݰ����͵ĵ�ַ
 * @param[in] {buf_len} ���ݰ����͵ĳ���
 * @return ����������
 * -           0(ERROR): ʧ��
 * -           1(SUCCESS): �ɹ�
 * @note   MCU��Ҫ����ʵ�ָù���
 */
unsigned char maps_stream_trans_send(unsigned int id, unsigned char sub_id, unsigned char sub_id_pro_mode, unsigned char *buffer, unsigned long buf_len)
{
    unsigned long map_offset = 0;
    unsigned int pack_num = 0;
    unsigned int rest_length = 0;
    unsigned char pro_ver = 0; //��ͼ����Э��汾 Ĭ��Ϊ0

    if(stop_update_flag == ENABLE)
        return SUCCESS;

    pack_num = buf_len / STREM_PACK_LEN;
    rest_length = buf_len - pack_num * STREM_PACK_LEN;
    if (rest_length > 0) {
        pack_num++;
    }

    int this_len = STREM_PACK_LEN;
    for (int cnt = 0; cnt < pack_num; cnt++,map_offset += this_len) {
        if (cnt == pack_num - 1 && rest_length > 0) {
            this_len = rest_length;
        }else {
            this_len = STREM_PACK_LEN;
        }

        if(ERROR == maps_stream_trans(pro_ver, id, sub_id, sub_id_pro_mode, map_offset, buffer + map_offset, this_len)) {
            //mcu���������У������Խ�����������
            //printf("is upgrade\n");
            return ERROR;
        }
        
//        #error "�������ʾ�����������������ʹ��룬��ɺ���ɾ������"
        /*  ���MCU����ʹ�ö���̻���̣߳����Խ��˺�������һ�������Ľ��̻��߳���ִ�У�����������ʾ�Ĵ���  */
        /*
        while(0xff == maps_stream_status); //�ȴ�ģ��ظ�
        
        if(0x00 != maps_stream_status) {
            //ʧ��  ���� maps_stream_trans_send_result �����в鿴������
            return ERROR;
        }
        */
        
        /*  ���MCU��֧�ֶ���̻���̣߳�ʹ�ô˺���ʱÿ��ֻ��һ�������ݳ��Ȳ�����STREM_PACK_LEN����
        ������֮���� maps_stream_trans_send_result �����д���ģ�鷵�صĽ�������ͳɹ�ʱ�ٴε��ô˺���������һ����ע���ƫ��Ҫ����  */
    }
    
    return SUCCESS;
}
#endif

#ifdef WIFI_CONNECT_TEST_ENABLE
/**
 * @brief  mcu����wifi���ܲ���(����ָ��·��)
 * @param[in] {ssid_buf} ���·���������ַ������ݵĵ�ַ(ssid�������֧��32���ֽ�)
 * @param[in] {passwd_buffer} ���·���������ַ������ݵĵ�ַ(passwd�������֧��64���ֽ�)
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_start_connect_wifitest(unsigned char *ssid_buf,unsigned char *passwd_buffer)
{
    unsigned short send_len = 0;

    if( my_strlen(ssid_buf) > 32 || my_strlen(passwd_buffer) > 64) {
        //printf("ssid_buf or passwd_buffer is too long!");
        return;
    }
    
    send_len = set_wifi_uart_buffer(send_len, "{\"ssid\":\"", my_strlen("{\"ssid\":\""));
    send_len = set_wifi_uart_buffer(send_len,ssid_buf,my_strlen(ssid_buf));
    send_len = set_wifi_uart_buffer(send_len, "\",\"password\":\"", my_strlen("\",\"password\":\""));
    send_len = set_wifi_uart_buffer(send_len,passwd_buffer,my_strlen(passwd_buffer));
    send_len = set_wifi_uart_buffer(send_len, "\"}", my_strlen("\"}"));

    wifi_uart_write_frame(WIFI_CONNECT_TEST_CMD, MCU_TX_VER, send_len);
}
#endif

#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  ��ȡģ��MAC
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_get_module_mac(void)
{
    wifi_uart_write_frame(GET_MAC_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef IR_TX_RX_TEST_ENABLE
/**
 * @brief  mcu�����������շ�����
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_start_ir_test(void)
{
    wifi_uart_write_frame(IR_TX_RX_TEST_CMD, MCU_TX_VER, 0);
}
#endif

#ifdef MODULE_EXPANDING_SERVICE_ENABLE
/**
 * @brief  ��ģ��ʱ�����֪ͨ
 * @param[in] {time_type} ʱ������
 * @ref       0x00: ����ʱ��
 * @ref       0x01: ����ʱ��
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void open_module_time_serve(unsigned char time_type)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, 0x01);
    send_len = set_wifi_uart_byte(send_len, time_type);
    wifi_uart_write_frame(MODULE_EXTEND_FUN_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  ��������������������
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void request_weather_serve(void)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, 0x03);
    wifi_uart_write_frame(MODULE_EXTEND_FUN_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  ��ģ������״̬֪ͨ
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void open_module_reset_state_serve(void)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, 0x04);
    wifi_uart_write_frame(MODULE_EXTEND_FUN_CMD, MCU_TX_VER, send_len);
}
#endif

#ifdef BLE_RELATED_FUNCTION_ENABLE
/**
 * @brief  mcu�������������Բ��ԣ�ɨ��ָ�������ű꣩
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_start_BLE_test(void)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, 0x01);
    wifi_uart_write_frame(BLE_TEST_CMD, MCU_TX_VER, send_len);
}
#endif

#ifdef VOICE_MODULE_PROTOCOL_ENABLE
/**
 * @brief  ��ȡ����״̬��
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void get_voice_state(void)
{
    wifi_uart_write_frame(GET_VOICE_STATE_CMD, MCU_TX_VER, 0);
}

/**
 * @brief  MIC��������
 * @param[in] {set_val} ��������ֵ
 * @ref       0x00: mic����
 * @ref       0x01: mic����
 * @ref       0xA0: ��ѯ����״̬
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void set_voice_MIC_silence(unsigned char set_val)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, set_val);
    wifi_uart_write_frame(MIC_SILENCE_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  speaker��������
 * @param[in] {set_val} ��������ֵ
 * @ref       0~10: ������Χ
 * @ref       0xA0: ��ѯ����ֵ
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void set_speaker_voice(unsigned char set_val)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, set_val);
    wifi_uart_write_frame(SET_SPEAKER_VOLUME_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  ��Ƶ����
 * @param[in] {set_val} ��Ƶ����ֵ
 * @ref       0x00: �ر���Ƶ����
 * @ref       0x01: mic1��Ƶ��·����
 * @ref       0x02: mic2��Ƶ��·����
 * @ref       0xA0: ��ѯ��ǰ����״̬
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void voice_test(unsigned char test_val)
{
    unsigned short send_len = 0;
    send_len = set_wifi_uart_byte(send_len, test_val);
    wifi_uart_write_frame(VOICE_TEST_CMD, MCU_TX_VER, send_len);
}

/**
 * @brief  ���Ѳ���
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void voice_awaken_test(void)
{
    wifi_uart_write_frame(VOICE_AWAKEN_TEST_CMD, MCU_TX_VER, 0);
}

/**
 * @brief  ����ģ��MCU��������
 * @param[in] {play} ����/��ͣ���� 1(����) / 0(��ͣ)
 * @param[in] {bt_play} �������ع��� 1(��) / 0(��)
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void voice_mcu_fun_set(unsigned char play, unsigned char bt_play)
{
    unsigned short send_len = 0;
    unsigned char str[50];
    
    //MCU�����ݽ�֧�֡�����/��ͣ�� ���������ء�
    
    sprintf((char*)str,"{\"play\":%s,\"bt_play\":%s}", play?"true":"false", bt_play?"true":"false");
    
    send_len = set_wifi_uart_byte(send_len, 0x00);
    send_len = set_wifi_uart_buffer(send_len, str, my_strlen(str));
    wifi_uart_write_frame(VOICE_EXTEND_FUN_CMD, MCU_TX_VER, send_len);
}
#endif


