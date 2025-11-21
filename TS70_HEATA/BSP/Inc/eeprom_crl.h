#ifndef __EEPROM_CRL_H_
#define __EEPROM_CRL_H_

#include "eeprom.h"
#include "sys.h"
#include "power_crl.h"
#include "ntc.h"
#include "stdio.h"

#define F_HEAT_TEMP         0x0000
#define F_HEAT_SWITCH       0x0001
#define M_HEAT_TEMP         0x0002
#define M_HEAT_SWITCH       0x0003
#define R_HEAT_TEMP         0x0004
#define R_HEAT_SWITCH       0x0005
#define SF_LEVEL            0x0006
#define SF_SWITCH           0x0007
#define HF_DIRECTION        0X0008
#define HF_LEVEL            0x0009
#define HF_SWITCH           0x000A

#define EEPROM_STATU_JUDGE  0X0020         

void eeprom_statu_judge( void );
void eeprom_data_record( void );
void eeprom_data_init( void );

#endif