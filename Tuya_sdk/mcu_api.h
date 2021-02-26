/**********************************Copyright (c)**********************************
**                       ��Ȩ���� (C), 2015-2020, Ϳѻ�Ƽ�
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    mcu_api.h
 * @author  Ϳѻ�ۺ�Э�鿪����
 * @version v2.5.6
 * @date    2020.12.16
 * @brief   �û���Ҫ�������õĺ������ڸ��ļ���
 */

/****************************** �������� ������ *******************************
����MCU���ͺͱ��뻷�����ֶ��������Դ˴�������ο����û������аѿ����մ���������
Ϳѻ����MCU���ܽ������
******************************************************************************/

#ifndef __MCU_API_H_
#define __MCU_API_H_

#include "protocol.h"
#include "../mcc_generated_files/eusart1.h"

#ifdef MCU_API_GLOBAL
  #define MCU_API_EXTERN
#else
  #define MCU_API_EXTERN   extern
#endif

/**
 * @brief  hexתbcd
 * @param[in] {Value_H} ���ֽ�
 * @param[in] {Value_L} ���ֽ�
 * @return ת����ɺ�����
 */
unsigned char hex_to_bcd(unsigned char Value_H,unsigned char Value_L);

/**
 * @brief  ���ַ�������
 * @param[in] {str} �ַ�����ַ
 * @return ���ݳ���
 */
unsigned long my_strlen(unsigned char *str);

/**
 * @brief  ��src��ָ�ڴ������ǰcount���ֽ����ó��ַ�c
 * @param[out] {src} �����õ��ڴ��׵�ַ
 * @param[in] {ch} ���õ��ַ�
 * @param[in] {count} ���õ��ڴ泤��
 * @return �����õ��ڴ��׵�ַ
 */
void *my_memset(void *src,unsigned char ch,unsigned short count);

/**
 * @brief  �ڴ濽��
 * @param[out] {dest} Ŀ���ַ
 * @param[in] {src} Դ��ַ
 * @param[in] {count} �������ݸ���
 * @return ���ݴ�������Դ��ַ
 */
void *my_memcpy(void *dest, const void *src, unsigned short count);

/**
 * @brief  �ַ�������
 * @param[in] {dest} Ŀ���ַ
 * @param[in] {src} Դ��ַ
 * @return ���ݴ�������Դ��ַ
 */
char *my_strcpy(char *dest, const char *src);

/**
 * @brief  �ַ����Ƚ�
 * @param[in] {s1} �ַ��� 1
 * @param[in] {s2} �ַ��� 2
 * @return ��С�Ƚ�ֵ
 * -         0:s1=s2
 * -         <0:s1<s2
 * -         >0:s1>s2
 */
int my_strcmp(char *s1 , char *s2);

/**
 * @brief  ��int���Ͳ���ĸ��ֽ�
 * @param[in] {number} 4�ֽ�ԭ����
 * @param[out] {value} ������ɺ�4�ֽ�����
 * @return Null
 */
void int_to_byte(unsigned long number,unsigned char value[4]);

/**
 * @brief  ��4�ֽںϲ�Ϊ1��32bit����
 * @param[in] {value} 4�ֽ�����
 * @return �ϲ���ɺ��32bit����
 */
unsigned long byte_to_int(const unsigned char value[4]);

/**
 * @brief  raw��dp�����ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @param[in] {len} ���ݳ���
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_raw_update(unsigned char dpid,const unsigned char value[],unsigned short len);

/**
 * @brief  bool��dp�����ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵ
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_bool_update(unsigned char dpid,unsigned char value);

/**
 * @brief  value��dp�����ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵ
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value);

/**
 * @brief  string��dp�����ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @param[in] {len} ���ݳ���
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_string_update(unsigned char dpid,const unsigned char value[],unsigned short len);

/**
 * @brief  enum��dp�����ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵ
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_enum_update(unsigned char dpid,unsigned char value);

/**
 * @brief  fault��dp�����ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵ
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_fault_update(unsigned char dpid,unsigned long value);

#ifdef MCU_DP_UPLOAD_SYN
/**
 * @brief  raw��dp����ͬ���ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @param[in] {len} ���ݳ���
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_raw_update_syn(unsigned char dpid,const unsigned char value[],unsigned short len);

/**
 * @brief  bool��dp����ͬ���ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_bool_update_syn(unsigned char dpid,unsigned char value);

/**
 * @brief  value��dp����ͬ���ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_value_update_syn(unsigned char dpid,unsigned long value);

/**
 * @brief  string��dp����ͬ���ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @param[in] {len} ���ݳ���
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_string_update_syn(unsigned char dpid,const unsigned char value[],unsigned short len);

/**
 * @brief  enum��dp����ͬ���ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_enum_update_syn(unsigned char dpid,unsigned char value);

/**
 * @brief  fault��dp����ͬ���ϴ�
 * @param[in] {dpid} dpid��
 * @param[in] {value} ��ǰdpֵָ��
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_fault_update_syn(unsigned char dpid,unsigned long value);
#endif

/**
 * @brief  mcu��ȡbool���·�dpֵ
 * @param[in] {value} dp���ݻ�������ַ
 * @param[in] {len} dp���ݳ���
 * @return ��ǰdpֵ
 * @note   Null
 */
unsigned char mcu_get_dp_download_bool(const unsigned char value[],unsigned short len);

/**
 * @brief  mcu��ȡenum���·�dpֵ
 * @param[in] {value} dp���ݻ�������ַ
 * @param[in] {len} dp���ݳ���
 * @return ��ǰdpֵ
 * @note   Null
 */
unsigned char mcu_get_dp_download_enum(const unsigned char value[],unsigned short len);

/**
 * @brief  mcu��ȡvalue���·�dpֵ
 * @param[in] {value} dp���ݻ�������ַ
 * @param[in] {len} dp���ݳ���
 * @return ��ǰdpֵ
 * @note   Null
 */
unsigned long mcu_get_dp_download_value(const unsigned char value[],unsigned short len);

/**
 * @brief  ���ڽ��������ݴ洦��
 * @param[in] {value} �����յ���1�ֽ�����
 * @return Null
 * @note   ��MCU���ڴ������е��øú���,�������յ���������Ϊ��������
 */
void uart_receive_input(unsigned char value);

/**
 * @brief  ���ڽ��ն���ֽ������ݴ洦��
 * @param[in] {value} ����Ҫ���յ����ݵ�Դ��ַ
 * @param[in] {data_len} ����Ҫ���յ����ݵ����ݳ���
 * @return Null
 * @note   ����Ҫ֧��һ�ζ��ֽڻ��棬�ɵ��øú���
 */
void uart_receive_buff_input(unsigned char value[], unsigned short data_len);

/**
 * @brief  wifi�������ݴ������
 * @param  Null
 * @return Null
 * @note   ��MCU������whileѭ���е��øú���
 */
void wifi_uart_service(void);

/**
 * @brief  Э�鴮�ڳ�ʼ������
 * @param  Null
 * @return Null
 * @note   ��MCU��ʼ�������е��øú���
 */
void wifi_protocol_init(void);

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
unsigned char mcu_get_reset_wifi_flag(void);

/**
 * @brief  MCU��������wifi����ģʽ
 * @param  Null
 * @return Null
 * @note   1:MCU��������,ͨ��mcu_get_reset_wifi_flag()������ȡ����wifi�Ƿ�ɹ�
 *         2:���Ϊģ���Դ���ģʽ,MCU������øú���
 */
void mcu_reset_wifi(void);

/**
 * @brief  ��ȡ����wifi״̬�ɹ���־
 * @param  Null
 * @return wifimode flag
 * -           0(SET_WIFICONFIG_ERROR):ʧ��
 * -           1(SET_WIFICONFIG_SUCCESS):�ɹ�
 * @note   1:MCU��������mcu_set_wifi_mode()����øú�����ȡ��λ״̬
 *         2:���Ϊģ���Դ���ģʽ,MCU������øú���
 */
unsigned char mcu_get_wifimode_flag(void);

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
void mcu_set_wifi_mode(unsigned char mode);

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
unsigned char mcu_get_wifi_work_state(void);
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  MCU��ȡ����ʱ��
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_get_green_time(void);
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU��ȡϵͳʱ��,����У�Ա���ʱ��
 * @param  Null
 * @return Null
 * @note   MCU����������ɺ���mcu_write_rtctime������У��rtcʱ��
 */
void mcu_get_system_time(void);
#endif

#ifdef WIFI_TEST_ENABLE
/**
 * @brief  mcu����wifi���ܲ���
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_start_wifitest(void);
#endif

#ifdef WIFI_HEARTSTOP_ENABLE
/**
 * @brief  ֪ͨWIFIģ��ر�����
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void wifi_heart_stop(void);
#endif

#ifdef GET_WIFI_STATUS_ENABLE
/**
 * @brief  ��ȡ��ǰwifi����״̬
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_get_wifi_connect_status(void);
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
unsigned char stream_trans_send(unsigned int id, unsigned char *buffer, unsigned long buf_len);

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
unsigned char maps_stream_trans_send(unsigned int id, unsigned char sub_id, unsigned char sub_id_pro_mode, unsigned char *buffer, unsigned long buf_len);
#endif

#ifdef WIFI_CONNECT_TEST_ENABLE
/**
 * @brief  mcu����wifi���ܲ���(����ָ��·��)
 * @param[in] {ssid_buf} ���·���������ַ������ݵĵ�ַ(ssid�������֧��32���ֽ�)
 * @param[in] {passwd_buffer} ���·���������ַ������ݵĵ�ַ(passwd�������֧��64���ֽ�)
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_start_connect_wifitest(unsigned char *ssid_buf,unsigned char *passwd_buffer);
#endif

#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  ��ȡģ��MAC
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_get_module_mac(void);
#endif

#ifdef IR_TX_RX_TEST_ENABLE
/**
 * @brief  mcu�����������շ�����
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_start_ir_test(void);
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
void open_module_time_serve(unsigned char time_type);

/**
 * @brief  ��������������������
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void request_weather_serve(void);

/**
 * @brief  ��ģ������״̬֪ͨ
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void open_module_reset_state_serve(void);
#endif

#ifdef BLE_RELATED_FUNCTION_ENABLE
/**
 * @brief  mcu�������������Բ��ԣ�ɨ��ָ�������ű꣩
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void mcu_start_BLE_test(void);
#endif

#ifdef VOICE_MODULE_PROTOCOL_ENABLE
/**
 * @brief  ��ȡ����״̬��
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void get_voice_state(void);

/**
 * @brief  MIC��������
 * @param[in] {set_val} ��������ֵ
 * @ref       0x00: mic����
 * @ref       0x01: mic����
 * @ref       0xA0: ��ѯ����״̬
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void set_voice_MIC_silence(unsigned char set_val);

/**
 * @brief  speaker��������
 * @param[in] {set_val} ��������ֵ
 * @ref       0~10: ������Χ
 * @ref       0xA0: ��ѯ����ֵ
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void set_speaker_voice(unsigned char set_val);

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
void voice_test(unsigned char test_val);

/**
 * @brief  ���Ѳ���
 * @param  Null
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void voice_awaken_test(void);

/**
 * @brief  ����ģ��MCU��������
 * @param[in] {play} ����/��ͣ���� 1(����) / 0(��ͣ)
 * @param[in] {bt_play} �������ع��� 1(��) / 0(��)
 * @return Null
 * @note   MCU��Ҫ���е��øù���
 */
void voice_mcu_fun_set(unsigned char play, unsigned char bt_play);
#endif

#endif
