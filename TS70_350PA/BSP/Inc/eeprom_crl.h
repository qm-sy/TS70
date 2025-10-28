#ifndef __EEPROM_CRL_H_
#define __EEPROM_CRL_H_

#include "eeprom.h"
#include "sys.h"
#include "power_crl.h"
#include "ntc.h"
#include "stdio.h"
#include "modbus_rtu.h"


#define F_AC_SWITCH         0X0000
#define M_AC_SWITCH         0X0001
#define R_AC_SWITCH         0X0002
#define F_TEMP_ALARM        0X0003
#define M_TEMP_ALARM        0X0004
#define R_TEMP_ALARM        0X0005
#define LED_ADDR            0x0006
#define FAN_ADDR            0x0007
#define FAN_SWITCH          0x0008

#define EEPROM_STATU_JUDGE  0X0010         

void eeprom_statu_judge( void );
void eeprom_data_record( void );
void eeprom_data_init( void );

#endif