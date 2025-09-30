#ifndef __EEPROM_CRL_H_
#define __EEPROM_CRL_H_

#include "eeprom.h"
#include "sys.h"
#include "power_crl.h"
#include "ntc.h"
#include "stdio.h"

#define PREHEAT_TEMP_ADDR   0x0000
#define ALARM_TEMP_ADDR     0x0001      //热电偶
#define SF24_ADDR           0x0002      //撒粉      
#define DF24_ADDR           0x0003      //抖粉
#define IW1_ADDR            0x0004      //吸风开关1
#define IW2_ADDR            0x0005      //吸风开关2
#define CW_ADDR             0X0006      //冷风
#define MR_ADDR             0X0007      //收料
#define SYNC_ADDR           0X0008      //同步

#define EEPROM_STATU_JUDGE  0X0010         

void eeprom_statu_judge( void );
void eeprom_data_record( void );
void eeprom_data_init( void );

#endif