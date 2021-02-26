/**********************************Copyright (c)**********************************
**                       ��Ȩ���� (C), 2015-2020, Ϳѻ�Ƽ�
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    system.h
 * @author  Ϳѻ�ۺ�Э�鿪����
 * @version v2.5.6
 * @date    2020.12.16
 * @brief   �������ݴ����û�������ĸ��ļ�ʵ������
 */

/****************************** �������� ������ *******************************
����MCU���ͺͱ��뻷�����ֶ��������Դ˴�������ο����û������аѿ����մ���������
Ϳѻ����MCU���ܽ������
******************************************************************************/

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#ifdef SYSTEM_GLOBAL
  #define SYSTEM_EXTERN
#else
  #define SYSTEM_EXTERN   extern
#endif

//=============================================================================
//Byte order of the frame
//=============================================================================
#define         HEAD_FIRST                      0
#define         HEAD_SECOND                     1        
#define         PROTOCOL_VERSION                2
#define         FRAME_TYPE                      3
#define         LENGTH_HIGH                     4
#define         LENGTH_LOW                      5
#define         DATA_START                      6

//=============================================================================
//Data frame type
//=============================================================================
#define         HEAT_BEAT_CMD                   0                               //������
#define         PRODUCT_INFO_CMD                1                               //��Ʒ��Ϣ
#define         WORK_MODE_CMD                   2                               //��ѯMCU �趨��ģ�鹤��ģʽ	
#define         WIFI_STATE_CMD                  3                               //wifi����״̬	
#define         WIFI_RESET_CMD                  4                               //����wifi
#define         WIFI_MODE_CMD                   5                               //ѡ��smartconfig/APģʽ	
#define         DATA_QUERT_CMD                  6                               //�����·�
#define         STATE_UPLOAD_CMD                7                               //״̬�ϱ�	 
#define         STATE_QUERY_CMD                 8                               //״̬��ѯ   
#define         UPDATE_START_CMD                0x0a                            //������ʼ
#define         UPDATE_TRANS_CMD                0x0b                            //��������
#define         GET_ONLINE_TIME_CMD             0x0c                            //��ȡϵͳʱ��(��������ʱ��)
#define         FACTORY_MODE_CMD                0x0d                            //�������ģʽ    
#define         WIFI_TEST_CMD                   0x0e                            //wifi���ܲ���
#define         GET_LOCAL_TIME_CMD              0x1c                            //��ȡ����ʱ��
#define         WEATHER_OPEN_CMD                0x20                            //������          
#define         WEATHER_DATA_CMD                0x21                            //��������
#define         STATE_UPLOAD_SYN_CMD            0x22                            //״̬�ϱ���ͬ����
#define         STATE_UPLOAD_SYN_RECV_CMD       0x23                            //״̬�ϱ����֪ͨ��ͬ����
#define         HEAT_BEAT_STOP                  0x25                            //�ر�WIFIģ������
#define         STREAM_TRANS_CMD                0x28                            //�����ݴ���
#define         GET_WIFI_STATUS_CMD             0x2b                            //��ȡ��ǰwifi����״̬
#define         WIFI_CONNECT_TEST_CMD           0x2c                            //wifi���ܲ���(����ָ��·��)
#define         GET_MAC_CMD                     0x2d                            //��ȡģ��mac
#define         GET_IR_STATUS_CMD               0x2e                            //����״̬֪ͨ
#define         IR_TX_RX_TEST_CMD               0x2f                            //��������շ�����
#define         MAPS_STREAM_TRANS_CMD           0x30                            //�����ݴ���(֧�ֶ��ŵ�ͼ)
#define         FILE_DOWNLOAD_START_CMD         0x31                            //�ļ���������
#define         FILE_DOWNLOAD_TRANS_CMD         0x32                            //�ļ��������ݴ���
#define         MODULE_EXTEND_FUN_CMD           0x34                            //ģ����չ����
#define         BLE_TEST_CMD                    0x35                            //���������Բ��ԣ�ɨ��ָ�������ű꣩
#define         GET_VOICE_STATE_CMD             0x60                            //��ȡ����״̬��
#define         MIC_SILENCE_CMD                 0x61                            //MIC��������
#define         SET_SPEAKER_VOLUME_CMD          0x62                            //speaker��������
#define         VOICE_TEST_CMD                  0x63                            //����ģ����Ƶ����
#define         VOICE_AWAKEN_TEST_CMD           0x64                            //����ģ�黽�Ѳ���
#define         VOICE_EXTEND_FUN_CMD            0x65                            //����ģ����չ����


//=============================================================================
#define MCU_RX_VER              0x00                                            //ģ�鷢��֡Э��汾��
#define MCU_TX_VER              0x03                                            //MCU ����֡Э��汾��(Ĭ��)
#define PROTOCOL_HEAD           0x07                                            //�̶�Э��ͷ����
#define FRAME_FIRST             0x55                                            //֡ͷ��һ�ֽ�
#define FRAME_SECOND            0xaa                                            //֡ͷ�ڶ��ֽ�
//============================================================================= 
SYSTEM_EXTERN volatile unsigned char wifi_data_process_buf[PROTOCOL_HEAD + WIFI_DATA_PROCESS_LMT];     //�������ݴ�����
SYSTEM_EXTERN volatile unsigned char wifi_uart_rx_buf[PROTOCOL_HEAD + WIFI_UART_RECV_BUF_LMT];         //���ڽ��ջ���
SYSTEM_EXTERN volatile unsigned char wifi_uart_tx_buf[PROTOCOL_HEAD + WIFIR_UART_SEND_BUF_LMT];        //���ڷ��ͻ���
//
SYSTEM_EXTERN volatile unsigned char *rx_buf_in;
SYSTEM_EXTERN volatile unsigned char *rx_buf_out;

SYSTEM_EXTERN volatile unsigned char stop_update_flag;                                                 //ENABLE:ֹͣһ�������ϴ�  DISABLE:�ָ�һ�������ϴ�

#ifndef WIFI_CONTROL_SELF_MODE
SYSTEM_EXTERN volatile unsigned char reset_wifi_flag;                                                  //����wifi��־(TRUE:�ɹ�/FALSE:ʧ��)
SYSTEM_EXTERN volatile unsigned char set_wifimode_flag;                                                //����WIFI����ģʽ��־(TRUE:�ɹ�/FALSE:ʧ��)
SYSTEM_EXTERN volatile unsigned char wifi_work_state;                                                  //wifiģ�鵱ǰ����״̬
#endif

#ifdef WIFI_STREAM_ENABLE
SYSTEM_EXTERN volatile unsigned char stream_status;                                                             //�����񷢰�����״̬
SYSTEM_EXTERN volatile unsigned char maps_stream_status;                                                        //���ͼ�����񷢰�����״̬
#endif

/**
 * @brief  дwifi_uart�ֽ�
 * @param[in] {dest} ��������ʵ��ַ
 * @param[in] {byte} д���ֽ�ֵ
 * @return д����ɺ���ܳ���
 */
unsigned short set_wifi_uart_byte(unsigned short dest, unsigned char byte);

/**
 * @brief  дwifi_uart_buffer
 * @param[in] {dest} Ŀ���ַ
 * @param[in] {src} Դ��ַ
 * @param[in] {len} ���ݳ���
 * @return д������Ļ����ַ
 */
unsigned short set_wifi_uart_buffer(unsigned short dest, const unsigned char *src, unsigned short len);

/**
 * @brief  ����У���
 * @param[in] {pack} ����Դָ��
 * @param[in] {pack_len} ����У��ͳ���
 * @return У���
 */
unsigned char get_check_sum(unsigned char *pack, unsigned short pack_len);

/**
 * @brief  ��wifi���ڷ���һ֡����
 * @param[in] {fr_type} ֡����
 * @param[in] {fr_ver} ֡�汾
 * @param[in] {len} ���ݳ���
 * @return Null
 */
void wifi_uart_write_frame(unsigned char fr_type, unsigned char fr_ver, unsigned short len);

#ifdef WIFI_STREAM_ENABLE
/**
 * @brief  �����ݴ���
 * @param[in] {id} �������ʶ
 * @param[in] {offset} ƫ����
 * @param[in] {buffer} ���ݵ�ַ
 * @param[in] {buf_len} ���ݳ���
 * @return Null
 * @note   Null
 */
unsigned char stream_trans(unsigned short id, unsigned int offset, unsigned char *buffer, unsigned short buf_len);

/**
 * @brief  ���ͼ�����ݴ���
 * @param[in] {pro_ver} ��ͼ����Э��汾
 * @param[in] {id} ��ͼ������ỰID
 * @param[in] {sub_id} �ӵ�ͼID
 * @param[in] {sub_id_pro_mode} �ӵ�ͼID���ݴ���ʽ
 * @ref           0x00:�����ۼ�
 * @ref           0x00:����ϴ�������
 * @param[in] {offset} ƫ����
 * @param[in] {buffer} ���ݵ�ַ
 * @param[in] {buf_len} ���ݳ���
 * @return Null
 * @note   Null
 */
unsigned char maps_stream_trans(unsigned char pro_ver, unsigned short id, unsigned char sub_id, unsigned char sub_id_pro_mode, 
                                unsigned int offset, unsigned char *buffer, unsigned short buf_len);
#endif

/**
 * @brief  ����֡����
 * @param[in] {offset} ������ʼλ
 * @return Null
 */
void data_handle(unsigned short offset);

/**
 * @brief  �жϴ��ڽ��ջ������Ƿ�������
 * @param  Null
 * @return �Ƿ�������
 */
unsigned char with_data_rxbuff(void);

/**
 * @brief  ��ȡ����1�ֽ�����
 * @param  Null
 * @return Read the data
 */
unsigned char take_byte_rxbuff(void);
#endif
  
  
