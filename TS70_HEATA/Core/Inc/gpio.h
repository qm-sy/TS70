/*
|P0^0|Sensor2  |P1^0|       |P2^0|PWM1       |P3^0|RX1        |P4^0|           |P5^0|     
|P0^1|Sensor1  |P1^1|       |P2^1|PWM2       |P3^1|TX1        |P4^1|AC_Out1    |P5^1|     
|P0^2|RX_485   |P1^2|       |P2^2|PWM3       |P3^2|ZERO       |P4^2|AC_Out2    |P5^2|     
|P0^3|TX_485   |P1^3|       |P2^3|Buzzer     |P3^3|           |P4^3|AC_Out3    |P5^3|     
|P0^4|DR_485   |P1^4|       |P2^4|thermo1    |P3^4|           |P4^4|Fan_Temp   |P5^4|
|P0^5|         |P1^5|       |P2^5|thermo2    |P3^5|           |P4^5|TH_CS      |P5^5|             
|P0^6|         |P1^6|       |P2^6|thermo3    |P3^6|           |P4^6|TH_SCK     |P5^6|     
|P0^7|         |P1^7|       |P2^7|           |P3^7|           |P4^7|           |P5^7|     
*/ 

#ifndef __GPIO_H_
#define __GPIO_H_

#include "sys.h"

sbit Sensor2     = P0^0;
sbit Sensor1     = P0^1;
sbit RX_485      = P0^2;
sbit TX_485      = P0^3;
sbit DR_485      = P0^4;

sbit PWM1        = P2^0;
sbit PWM2        = P2^1;
sbit PWM3        = P2^2;
sbit Buzzer      = P2^3;
sbit TherMo1     = P2^4;
sbit TherMo2     = P2^5;
sbit TherMo3     = P2^6;

sbit RX1         = P3^0;
sbit TX1         = P3^1;
sbit ZERO        = P3^2;

sbit AC_Out1     = P4^1;
sbit AC_Out2     = P4^2;
sbit AC_Out3     = P4^3;
sbit Fan_Temp    = P4^4;
sbit TH_CS       = P4^5;
sbit TH_SCK      = P4^6;

void GPIO_Init( void );

#endif