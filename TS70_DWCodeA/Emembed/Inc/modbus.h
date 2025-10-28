#ifndef __MODBUS_H__
#define __MODBUS_H__

#include "communication.h"

#define HANSEN_ADDR     0x01
#define SP350P_ADDR      0x02

#define FUN_03          0x03
#define FUN_04          0x04
#define FUN_06          0x06
#define FUN_16          0x10

typedef struct 
{
    uint8_t  byte_info_H;               //DATA_H
    uint8_t  byte_info_L;               //DATA_L
    uint8_t  byte_cnt;                  //BYTE NUM*2
    uint16_t send_val_addr;             //DATA1 H 位置
    uint16_t rcv_value_addr;            //DATA1 H 位置
    uint16_t start_addr;                //查询起始位置
}MODBIS5_INFO;

typedef struct 
{
    uint8_t  byte_info_H;               //DATA_H
    uint8_t  byte_info_L;               //DATA_L
    uint8_t  byte_cnt;                  //BYTE NUM*2
    uint16_t send_val_addr;             //DATA1 H 位置
    uint16_t rcv_value_addr;            //DATA1 H 位置
    uint16_t start_addr;                //查询起始位置
}MODBIS4_INFO;


extern MODBIS4_INFO modbus4;
extern MODBIS5_INFO modbus5;
extern uint8_t fuyin_flag;

void Modbus_Event_Uart2( void );

void Modbus_Event_Uart5( void );
void Modbus_Fun03_slave1( void );
void Modbus_Fun06_slave1( void );
void Modbus_Fun16_slave1( void );

void Modbus_Event_Uart4( void );
void Modbus_Fun03_slave2( void );

void slave1_to_master(uint8_t code_num,uint8_t length);
void slave2_to_master(uint8_t code_num, uint8_t length);
uint16_t MODBUS_CRC16(uint8_t *buf, uint16_t length);
void write_slave_06(uint16_t reg_addr, uint8_t reg_val_H, uint8_t reg_val_L);
void get_slave_03( void );

#endif