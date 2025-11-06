#ifndef __MODBUS_H__
#define __MODBUS_H__

#include "communication.h"

#define HANSEN_ADDR     0x01
#define SP350P_ADDR     0x02
#define DFJ_ADDR        0x03

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

void Modbus_Event_DFG( void );
void Modbus_Fun03_DFG( void );
void Modbus_Fun04_DFG( void );
void Modbus_Fun06_DFG( void );
void read_slave_03_DFG( void );
void read_slave_04_DFG( void );
void write_slave_06_DFG(uint16_t reg_addr, uint8_t reg_val_H, uint8_t reg_val_L);
void DFG_connect_scan( void );

void Modbus_Event_HanSen( void );
void Modbus_Fun03_HanSen( void );
void Modbus_Fun06_HanSen( void );
void Modbus_Fun16_HanSen( void );

void Modbus_Event_350P( void );
void Modbus_Fun03_350P( void );
void read_slave_03_350P( void );
void write_slave_06_350P(uint16_t reg_addr, uint8_t reg_val_H, uint8_t reg_val_L);

void slave1_to_master(uint8_t code_num,uint8_t length);
uint16_t MODBUS_CRC16(uint8_t *buf, uint16_t length);

#endif