#include "ntc.h"

TEMP temp;

/**
 * @brief 取10次adc_val均值对应的temp
 *
 * @param[in] channle_x ntc通道1~4
 * 
 * @return  temp :最终温度
 * 
**/
uint16_t get_adc( uint8_t channle_x )
{
    uint8_t t;
    uint16_t adc_val = 0;

    /* 1, 取10次adc_val                           */
    for( t = 0; t < 10; t++ )
		{
			adc_val += Get_ADC_12bit(channle_x);
            
		}	       
    adc_val = adc_val/10;


    return adc_val;
}

uint16_t max6675_readRawVal( void )
{
    uint16_t tmp=0;
    uint16_t i;

    TH_CS = 0;

    for(i = 0; i < 15; i++)
    {
        TH_SCK = 1;
        delay_us(10);

        if(TH_S01)
        {
            tmp|=0x0001;
        }
        else 
        {
            tmp |= 0;
        }
        tmp<<=1;

        TH_SCK = 0;
        delay_us(10);

    }

    TH_CS = 1;

    if ( tmp & 0X04 )
    {
        tmp = 4096; //未检测到热电偶
    }
    else
    {
        tmp >>= 3;//去掉D0、1、2位
    }
    return tmp;
}
 
uint16_t max6675_readTemp( void )
{
	uint16_t d;
	uint16_t i;

	d = max6675_readRawVal();
	delay_ms(1);
	i = (uint16_t)(d * (1023.75 / 4095));

    return i;
}