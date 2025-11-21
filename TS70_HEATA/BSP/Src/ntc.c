#include "ntc.h"

#define NTCTabNum 181

TEMP temp;

void Temp_Init( void )
{
    temp.scan_flag = 0;
}

uint16_t* max6675_readRawVal( void )
{
	uint16_t adc_val[3] = {0};
    uint16_t i;

    TH_CS = 0;

    for(i = 0; i < 15; i++)
    {
        TH_SCK = 1;
        delay_us(10);
        /* TherMo1  */
        if(TherMo1)
        {
            adc_val[0] |= 0x0001;
        }
        else 
        {
            adc_val[0] |= 0;
        }
        adc_val[0] <<= 1;

        /* TherMo2  */
        if(TherMo2)
        {
            adc_val[1] |= 0x0001;
        }
        else 
        {
            adc_val[1] |= 0;
        }
        adc_val[1] <<= 1;

        /* TherMo3  */
        if(TherMo3)
        {
            adc_val[2] |= 0x0001;
        }
        else 
        {
            adc_val[2] |= 0;
        }
        adc_val[2] <<= 1;

        TH_SCK = 0;
        delay_us(10);
    }

    TH_CS = 1;

    if ( adc_val[0] & 0X04 )
    {
        adc_val[0] = 4096; //未检测到热电偶
    }
    else
    {
        adc_val[0] >>= 3;//去掉D0、1、2位
    }

    if ( adc_val[1] & 0X04 )
    {
        adc_val[1] = 4096; //未检测到热电偶
    }
    else
    {
        adc_val[1] >>= 3;//去掉D0、1、2位
    }

    if ( adc_val[2] & 0X04 )
    {
        adc_val[2] = 4096; //未检测到热电偶
    }
    else
    {
        adc_val[2] >>= 3;//去掉D0、1、2位
    }
    return adc_val;
}
 
uint16_t* max6675_readTemp( void )
{
	uint16_t temp_val[3] = {0};
	uint16_t *adc_val = NULL;

	adc_val = max6675_readRawVal();
	delay_ms(1); 

	temp_val[0] = (uint16_t)(adc_val[0] * (1023.75 / 4095));
	temp_val[1] = (uint16_t)(adc_val[1] * (1023.75 / 4095));
    temp_val[2] = (uint16_t)(adc_val[2] * (1023.75 / 4095));

    return temp_val;
}