#ifndef _NTC_H_
#define _NTC_H_

#include "sys.h"
#include "adc.h"
#include "power_crl.h"
#include "stdio.h"

typedef struct 
{
    uint8_t  scan_flag;
    uint16_t  th_temp;
}TEMP;

extern TEMP temp;

uint16_t get_adc( uint8_t channle_x );
uint16_t max6675_readRawVal( void );
uint16_t max6675_readTemp( void );

#endif