#ifndef _NTC_H_
#define _NTC_H_

#include "sys.h"
#include "power_crl.h"
#include "stdio.h"

#define NTC1        4       
#define NTC2        5 
#define NTC3        6

typedef struct 
{
    uint8_t  scan_flag;

    uint16_t  thermo1_temp;
    uint16_t  thermo2_temp;
    uint16_t  thermo3_temp;
}TEMP;

extern TEMP temp;

void Temp_Init( void );
uint16_t* max6675_readRawVal( void );
uint16_t* max6675_readTemp( void );

#endif