#ifndef __GUI_CTRL_H__
#define __GUI_CTRL_H__

#include "sys.h"
#include "modbus.h"

#define F_AC_SWITCH         0X0000
#define M_AC_SWITCH         0X0001
#define R_AC_SWITCH         0X0002
#define F_TEMP_ALARM        0X0003
#define M_TEMP_ALARM        0X0004
#define R_TEMP_ALARM        0X0005
#define LED_ADDR            0x0006
#define FAN_ADDR            0x0007
#define FAN_SWITCH          0x0008

typedef struct 
{
    uint8_t  F_alarm_val;       //数据包接收完毕标志
    uint8_t  M_alarm_val;           //SBUF TI缓冲区
    uint8_t  R_alarm_val;           //SBUF RI缓冲区
    uint8_t  F_switch;    //发送字节数
    uint8_t  M_switch;           //发送计数
    uint8_t  R_switch;        //接收超时
    uint8_t  LED_switch;            //接收计数
    uint8_t  fan_switch;                //DR
    uint8_t  fan_level;
    uint8_t   params_get_flag1;
    uint8_t   params_get_flag2;
}SP350;

typedef struct 
{
    uint8_t  PostDry_switch;
    uint8_t  PostDry_temp;   
    uint8_t  SF_switch;
    uint8_t  SF_direction;
    uint8_t  SF_level;
    uint8_t  DF_switch;
    uint8_t  DF_direction;
    uint8_t  DF_level;
    uint8_t  IW1_switch;
    uint8_t  IW2_switch;
    uint8_t  CW_switch;
    uint8_t  MR_switch;
    uint8_t  Insulation_switch;
    uint8_t  Insulation_temp;
    uint8_t  sync_switch;
    uint8_t  power_switch;
    uint8_t  params_get_flag1;
    uint8_t  params_get_flag2;

    uint8_t temp_scan_flag;
    uint16_t th_temp;
}MC01;

typedef struct 
{
    uint16_t  cnt_s;       //数据包接收完毕标志
    uint16_t  cnt_min;           //SBUF TI缓冲区
    uint16_t  cnt_h;           //SBUF RI缓冲区
    uint16_t  remain_s;    //发送字节数
    uint16_t  remain_min;           //发送计数
    uint16_t  remain_h;        //接收超时
}DAYIN_T;

typedef struct 
{
    uint16_t ctrl_flag;
    uint16_t connect_flag;
    uint16_t addr_0x0c;
    uint16_t addr_0x20;
    uint16_t addr_0x21;
    uint16_t addr_0x22;
    uint16_t addr_0x23;
    uint16_t addr_0x2d;
    uint16_t addr_0x30;

    uint16_t addr_0x06;
    uint16_t addr_0x00;
    uint16_t addr_0x02;
    uint16_t addr_0x10;
    uint16_t addr_0x06_02;
    uint16_t addr_0x06_35;
    uint16_t addr_0x06_67;
    uint16_t addr_0x06_8a;
    uint16_t addr_0x06_bc;
    uint16_t addr_yuhua;
    uint16_t addr_sjpt;

    uint16_t addr_0x0100;
    uint16_t addr_0x0102;
    uint16_t addr_0x0110;
    uint16_t addr_0x0111;
    uint16_t addr_0x0112;
    uint16_t addr_0x0114;
    uint16_t addr_0x0116;
    uint16_t addr_0x0118;
    uint16_t addr_0x011a;
    uint16_t addr_0x011c;

    uint16_t addr_0x0134;
    uint16_t addr_0x0136;
    uint16_t addr_0x0138;
    uint16_t addr_0x013a;
    uint16_t addr_0x013c;

    uint16_t addr_0x0169;
    uint16_t addr_0x0150;
    uint16_t addr_0x0151;
    uint16_t addr_0x0152;
    uint16_t addr_0x0153;
    uint16_t addr_0x0154;
    uint16_t addr_0x0155;
    uint16_t addr_0x0156_H;
    uint16_t addr_0x0156_L;
    uint16_t addr_0x0157_H;
    uint16_t addr_0x0157_L;
    uint8_t  paoji_flag;
    uint8_t  paoji_send;
    uint16_t  paoji_s;
    uint16_t  paoji_min;
    uint16_t  paoji_h;
}HANSEN;

extern SP350 sp350;
extern HANSEN hansen;
extern DAYIN_T dayin_t;
extern MC01 mc01;

void gui_vol_ctrl( uint16_t addr, uint8_t val_H, uint8_t val_L);
void sp350_parms_init( void );
void diwen_parms_init( void );
void jump_page( uint8_t page_num );
void time_trans( uint16_t time_val ,uint8_t num );
void mc01_parms_init( void );

#endif