#ifndef __POWER_CRL_H_
#define __POWER_CRL_H_

#include "sys.h"
#include "gpio.h"
#include "ntc.h"
#include "eeprom_crl.h"
#include "dht11.h"

#define AC_ON     0
#define AC_OFF    1

#define ENABLE     1
#define DISABLE    0

typedef struct 
{
    uint8_t  tc_temp;                     
}SLAVE_04;

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
}SLAVE_06;

typedef struct 
{
    uint8_t  signal_flag;
    uint8_t  SF_enable;
    uint8_t  DF_enable;
    uint8_t  IW1_enable;
    uint8_t  IW2_enable;
    uint8_t  CW_enable;
    uint8_t  AC1_enable;
    uint8_t  AC2_enable;
    uint8_t  Insulation_enable;
}POWER_CTRL;

extern SLAVE_06 slave_06;
extern SLAVE_04 slave_04;
extern POWER_CTRL power_ctrl;

void temp_scan( void );
void IW_ctrl( void );
void ac_dc_ctrl( void );
uint8_t heat_enable_judge( uint8_t th_value, uint8_t th_heat_temp, uint8_t Insulation_temp );

#endif