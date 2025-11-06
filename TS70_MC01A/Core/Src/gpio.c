/*
|P0^0|RX3       |P1^0|RX2       |P2^0|MR_220V   |P3^0|RX1       |P4^0|          |P5^0|     
|P0^1|TX3       |P1^1|TX2       |P2^1|Relay3    |P3^1|TX1       |P4^1|Sensor_2  |P5^1|     
|P0^2|RX4       |P1^2|          |P2^2|IW_2      |P3^2|ZERO      |P4^2|Sensor_1  |P5^2|     
|P0^3|TX4       |P1^3|DD_ADC    |P2^3|IW_1      |P3^3|DF_24V    |P4^3|          |P5^3|     
|P0^4|DR4       |P1^4|PN2_ADC   |P2^4|          |P3^4|CW_24V    |P4^4|WK_220V   |P5^4|PN1_ADC
|P0^5|PN1_24V   |P1^5|SF_ADC    |P2^5|          |P3^5|Sensor_5  |P4^5|SCK       |P5^5|             
|P0^6|DD_24V    |P1^6|DF_ADC    |P2^6|S01       |P3^6|Sensor_4  |P4^6|          |P5^6|     
|P0^7|PN2_24V   |P1^7|CW_ADC    |P2^7|CS        |P3^7|Sensor_3  |P4^7|SF_24V    |P5^7|        
*/ 

#include "gpio.h"

/**
 * @brief	GPIO初始化
 *
 * @param   void
 *
 * @return  void
 */
void GPIO_Init( void )
{
    P0M0 = 0xfa;    P0M1 = 0x00;        //P0.1、P0.3、P0.4、P0.5、P0.6、P0.7为推挽输出
    P1M0 = 0x02;    P1M1 = 0x00;        //P1.1为高阻输入
    P2M0 = 0x8f;    P2M1 = 0x00;        //P2.0、P2.1、P2.2、P2.3为推挽输出
    P3M0 = 0X1a;    P3M1 = 0X00;        //P3.1、P3.3、P3.4为推挽输出
    P3PU = 0x38; 
    P4M0 = 0xB0;    P4M1 = 0x00;        //P4.4、P4.7为推挽输出     
    P4PU = 0x06; 
    P5M0 = 0X00;    P5M1 = 0X00;    
    PN1_24V = DD_24V = PN2_24V = 0;
    CW_24V = DF_24V = SF_24V = 0;
}