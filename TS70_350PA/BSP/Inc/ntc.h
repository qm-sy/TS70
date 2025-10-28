#ifndef _NTC_H_
#define _NTC_H_

#include "sys.h"
#include "adc.h"
#include "power_crl.h"
#include "stdio.h"
#include "dht11.h"
#include "modbus_rtu.h"

#define NTC_1        4
#define NTC_2        5
#define NTC_3        6

typedef struct 
{
    uint8_t  F_temp_val;   
    uint8_t  M_temp_val;  
    uint8_t  R_temp_val;  

    uint8_t  temp_scan_flag;
}TEMP;

extern TEMP temp;

uint16_t get_temp( uint8_t channle_x );
void temp_scan( void );

#endif