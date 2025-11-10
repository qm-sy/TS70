#ifndef __COMMUNICTION_H__
#define __COMMUNICTION_H__

#include "uart.h"
#include "tim.h"

#define S4TI    0X01
#define S4RI    0X01

#define S5TI    0X01
#define S5RI    0X01

typedef struct 
{
    uint8_t     rcv_end_flag;       //数据包接收完毕标志
    uint8_t     send_buf[128];           //SBUF TI缓冲区
    uint8_t     rcv_buf[128];           //SBUF RI缓冲区
    uint8_t     send_bytelength;    //发送字节数
    uint8_t     send_cnt;           //发送计数
    uint16_t    rcv_timeout;        //接收超时
    uint8_t     rcv_cnt;            //接收计数

    uint8_t     fun04_rcv_out;
    uint8_t     fun06_rcv_out;
    uint8_t     comm_error_flag;
    uint8_t     comm_error_flag2;
    uint8_t     press_flag1;
    uint8_t     press_flag2;
}RS485_2;

typedef struct 
{
    uint8_t     RX_rcv_end_Flag;       //数据包接收完毕标志
    uint8_t     TX_buf[128];           //SBUF TI缓冲区
    uint8_t     RX_buf[128];           //SBUF RI缓冲区
    uint8_t     TX_send_bytelength;    //发送字节数
    uint8_t     TX_send_cnt;           //发送计数
    uint16_t    RX_rcv_timeout;        //接收超时
    uint8_t     RX_rcv_cnt;            //接收计数
    uint8_t     fun06_rcv_out;
    uint8_t     comm_error_flag;
}RS485_4;

typedef struct 
{
    uint8_t     RX_rcv_end_Flag;       //数据包接收完毕标志
    uint8_t     TX_buf[1024];           //SBUF TI缓冲区
    uint8_t     RX_buf[1024];           //SBUF RI缓冲区
    uint8_t     TX_send_bytelength;    //发送字节数
    uint8_t     TX_send_cnt;           //发送计数
    uint16_t    RX_rcv_timeout;        //接收超时
    uint16_t    RX_rcv_cnt;            //接收计数
}RS485_5;

extern RS485_2 rs485_2;
extern RS485_4 rs485_4;
extern RS485_5 rs485_5;

void Uart2_Send_Statu_Init( void );
void Uart4_Send_Statu_Init( void );
void Uart5_Send_Statu_Init( void );
void uart4_send_byte( uint8_t byte );
void uart4_send_str( uint8_t *str,uint16_t len );

#endif