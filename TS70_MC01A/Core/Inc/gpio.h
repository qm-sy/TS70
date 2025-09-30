/*
|P0^0|RX3       |P1^0|RX2       |P2^0|MR_220V   |P3^0|RX1       |P4^0|          |P5^0|     
|P0^1|TX3       |P1^1|TX2       |P2^1|Relay3    |P3^1|TX1       |P4^1|Sensor_2  |P5^1|     
|P0^2|RX4       |P1^2|          |P2^2|IW_2      |P3^2|ZERO      |P4^2|Sensor_1  |P5^2|     
|P0^3|TX4       |P1^3|DD_ADC    |P2^3|IW_1      |P3^3|DF_24V    |P4^3|          |P5^3|     
|P0^4|DR4       |P1^4|PN2_ADC   |P2^4|          |P3^4|CW_24V    |P4^4|WK_220V   |P5^4|PN1_ADC
|P0^5|PN1_24V   |P1^5|SF_ADC    |P2^5|          |P3^5|Sensor_5  |P4^5|          |P5^5|             
|P0^6|DD_24V    |P1^6|DF_ADC    |P2^6|          |P3^6|Sensor_4  |P4^6|          |P5^6|     
|P0^7|PN2_24V   |P1^7|CW_ADC    |P2^7|          |P3^7|Sensor_3  |P4^7|SF_24V    |P5^7|     
*/ 

#ifndef _GPIO_H_
#define _GPIO_H_

#include "sys.h"

sbit RX3        = P0^0;
sbit TX3        = P0^1;
sbit RX4        = P0^2;
sbit TX4        = P0^3;
sbit DR4        = P0^4;
sbit PN1_24V    = P0^5;
sbit DD_24V     = P0^6;
sbit PN2_24V    = P0^7;

sbit RX2        = P1^0;
sbit TX2        = P1^1;
sbit DD_ADC     = P1^3;
sbit PN2_ADC    = P1^4;
sbit SF_ADC     = P1^5;
sbit DF_ADC     = P1^6;
sbit CW_ADC     = P1^7;

sbit MR_220V    = P2^0;
sbit Relay3     = P2^1;
sbit IW_2       = P2^2;
sbit IW_1       = P2^3;

sbit RX1        = P3^0;
sbit TX1        = P3^1;
sbit ZERO       = P3^2;
sbit DF_24V     = P3^3;
sbit CW_24V     = P3^4;
sbit Sensor_5   = P3^5;
sbit Sensor_4   = P3^6;
sbit Sensor_3   = P3^7;

sbit Sensor_2   = P4^1;
sbit Sensor_1   = P4^2;
sbit WK_220V    = P4^4;
sbit SF_24V     = P4^7;

sbit PN1_ADC    = P5^4;

void GPIO_Init( void );

#endif