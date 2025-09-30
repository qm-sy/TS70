#ifndef __GUI_CTRL_H__
#define __GUI_CTRL_H__

#include "sys.h"
#include "modbus.h"

#define ALARM_TEMP12_ADDR   0x00
#define ALARM_TEMP3_ADDR    0x01
#define FM_SWITCH_ADDR      0x02
#define R_SWITCH_ADDR       0x03
#define LED_SWITCH_ADDR     0x04
#define FAN_ADDR            0x05

typedef struct 
{
    uint16_t  alarm_tempF;       //数据包接收完毕标志
    uint16_t  alarm_tempM;           //SBUF TI缓冲区
    uint16_t  alarm_tempR;           //SBUF RI缓冲区
    uint16_t  F_switch;    //发送字节数
    uint16_t  M_switch;           //发送计数
    uint16_t  R_switch;        //接收超时
    uint16_t  LED_switch;            //接收计数
    uint16_t  fan_switch;                //DR
    uint16_t  fan_level;
}SP350;

typedef struct 
{
    uint16_t addr_0x20;
    uint16_t addr_0x21;
    uint16_t addr_0x22;
    uint16_t addr_0x23;
    uint16_t addr_0x2d;
    uint16_t addr_0x30;

    uint16_t addr_0x06;
    uint16_t addr_0x00;
    uint16_t addr_0x02;

    uint16_t addr_0x20_02;
    uint16_t addr_0x20_35;
    uint16_t addr_0x20_67;
    uint16_t addr_0x20_8a;
    uint16_t addr_0x20_bc;

}HANSEN;

extern SP350 sp350;
extern HANSEN hansen;

void gui_vol_ctrl( uint16_t addr, uint8_t val_H, uint8_t val_L);
void sp350_parms_init( void );
void diwen_parms_init( void );

#endif