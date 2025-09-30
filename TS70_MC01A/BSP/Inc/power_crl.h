#ifndef __POWER_CRL_H_
#define __POWER_CRL_H_

#include "sys.h"
#include "gpio.h"
#include "ntc.h"
#include "eeprom_crl.h"
#include "dht11.h"

#define AC_ON     0
#define AC_OFF    1

typedef struct 
{
    uint8_t  tc_temp;                     
}SLAVE_04;

typedef struct 
{
    uint8_t  tc_alarm_temp;
    uint8_t  tc_preheat_temp;
    uint8_t  sf_level;             
    uint8_t  df_level;           
    uint8_t  iw1_switch;  
    uint8_t  iw2_switch;  
    uint8_t  cw_switch;  
    uint8_t  mr_switch;   
    uint8_t  sync_switch;      
}SLAVE_06;

extern SLAVE_06 slave_06;
extern SLAVE_04 slave_04;

void sync_ctrl( void );
void temp_scan( void );
void IW_ctrl( void );
void CW_ctrl( void );
void MR_ctrl( void );

#endif