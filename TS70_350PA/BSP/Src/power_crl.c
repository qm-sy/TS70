#include "power_crl.h"

AC_CTRL ac_ctrl;

/**
 * @brief	移相触发调用结构体初始化
 *
 * @param   
 *
 * @return  void
**/
void Power_Statu_Init( void )
{
    AC_Out1 = AC_Out2 = AC_Out3 = AC_Out4 = 1;
}


/**
 * @brief	24V LED开关控制函数
 *
 * @param   on_off：0：关闭 1：开启
 *
 * @return  void
**/
void led_ctrl( uint8_t on_off )
{
    if( on_off == LED_ON )
    {
        DC_24V = 0;
    }else
    {
        DC_24V = 1;
    }
}

/**
 * @brief	24V PWM风扇档位控制函数
 *
 * @param   level :风扇档位 0~6档
 *
 * @return  void
**/
void fan_ctrl( uint8_t fan_SW,uint8_t level )
{
    if( level == 0x01 )
    {
        level = 1;
    }
    if( level == 0x02 )
    {
        level = 2;
    }
    if( level == 0x04 )
    {
        level = 3;
    }
    if( level == 0x08 )
    {
        level = 4;
    }
    if( level == 0x10 )
    {
        level = 5;
    }
    if( level == 0x20 )
    {
        level = 6;
    }
    PWMB_CCR7 = PWMB_CCR8 = level * 184;
    PWMB_BKR  = (fan_SW == 1) ? 0x80 : 0x00;
}

