#ifndef __EEPROM_CRL_H_
#define __EEPROM_CRL_H_

#include "eeprom.h"
#include "sys.h"
#include "power_crl.h"
#include "ntc.h"
#include "stdio.h"

#define PD_SWITCH       0x0000
#define PD_TEMP         0x0001      //后烘干
#define SF_SWITCH       0x0002
#define SF_DIRECTION    0x0003      //热电偶
#define SF_LEVEL        0x0004      //撒粉      
#define DF_SWITCH       0x0005
#define DF_DIRECTION    0x0006      //热电偶
#define DF_LEVEL        0x0007      //撒粉   
#define IW1_SWITCH      0x0008      //抖粉
#define IW2_SWITCH      0x0009      //吸风开关1
#define CW_SWITCH       0x000A      //吸风开关2
#define MR_SWITCH       0X000B      //冷风
#define INSU_SWITCH     0X000C      //收料
#define INSU_TEMP       0X000D      //同步
#define SYNC_SWITCH     0X000E      //收料

#define EEPROM_STATU_JUDGE  0X0010         

void eeprom_statu_judge( void );
void eeprom_data_record( void );
void eeprom_data_init( void );

#endif