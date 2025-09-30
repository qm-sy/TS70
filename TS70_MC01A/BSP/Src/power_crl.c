#include "power_crl.h"

SLAVE_06 slave_06;
SLAVE_04 slave_04;

/**
 * @brief	同步控制函数：无外部信号时 PWM风扇和220V输出关闭
 *
 * @param   
 *
 * @return  void
**/
void sync_ctrl( void )
{
    
}

/**
 * @brief 温度扫描，DHT11温湿度扫描 1s/次 控制220V输出使能
 *
 * @param[in] 
 * 
 * @return  
 * 
**/
void temp_scan( void )
{
    if( temp.scan_flag == 1)
    {

        temp.scan_flag = 0;
    }
}

/**
 * @brief 吸风开关控制（继电器） x2
 *
 * @param[in] 
 * 
 * @return  
 * 
**/
void IW_ctrl( void )
{
    if( slave_06.iw1_switch == 1 )
    {
        IW_1 = 1;
    }else
    {
        IW_1 = 0;
    }

    if( slave_06.iw2_switch == 1 )
    {
        IW_2 = 1;
    }else
    {
        IW_2 = 0;
    }
}

/**
 * @brief 冷风开关控制
 *
 * @param[in] 
 * 
 * @return  
 * 
**/
void CW_ctrl( void )
{
    if( slave_06.cw_switch == 1 )
    {
        CW_24V = 1;
    }else
    {
        CW_24V = 0;
    }
}

/**
 * @brief 收料开关控制
 *
 * @param[in] 
 * 
 * @return  
 * 
**/
void MR_ctrl( void )
{
    if( slave_06.mr_switch == 1 )
    {
        MR_220V = AC_ON;
    }else
    {
        MR_220V = AC_OFF;
    }
}