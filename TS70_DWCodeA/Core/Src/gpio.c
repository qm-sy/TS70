#include "gpio.h"

void GPIO_Init( void )
{
    P0MDOUT |= 0X13;
    P1MDOUT |= 0X80;
}