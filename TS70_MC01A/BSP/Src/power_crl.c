#include "power_crl.h"

SLAVE_06 slave_06;
SLAVE_04 slave_04;
POWER_CTRL power_ctrl;

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
    if( temp.scan_flag == 1 )
    {
        temp.th_temp = max6675_readTemp();
        temp.scan_flag = 0;
    }
}

/**
 * @brief AC DC输出使能控制
 *
 * @param[in] 
 * 
 * @return  
 * 
**/
void ac_dc_ctrl( void )
{
    if( slave_06.power_switch == 1 )
    {
        power_ctrl.AC1_enable = heat_enable_judge(temp.th_temp,              // 温度传感器1的当前值
                                                  slave_06.PostDry_temp,      // 通道1的加热目标温度
                                                  slave_06.Insulation_temp     // 通道1的预加热温度
                                                  ) ? ENABLE : DISABLE;         // 根据函数返回值设置使能状态

        power_ctrl.DF_enable  =                  ((slave_06.sync_switch   == 0  ||    //同步关闭
                                                   power_ctrl.signal_flag == 1) &&    //有24V信号进来
                                                  (slave_06.DF_switch == 1))   //抖粉开关打开
                                                  ? ENABLE : DISABLE;

        power_ctrl.SF_enable  =                  ((slave_06.sync_switch   == 0  ||    //同步关闭
                                                   power_ctrl.signal_flag == 1) &&    //有24V信号进来
                                                  (slave_06.SF_switch == 1))   //撒粉开关打开
                                                  ? ENABLE : DISABLE;

        power_ctrl.CW_enable  =                  ((slave_06.sync_switch   == 0  ||    //同步关闭
                                                   power_ctrl.signal_flag == 1) &&    //有24V信号进来
                                                  (slave_06.CW_switch == 1))   //撒粉开关打开
                                                  ? ENABLE : DISABLE;

        power_ctrl.AC2_enable =                  ((slave_06.sync_switch   == 0  ||    //同步关闭
                                                   Sensor_3 == 0) &&                  //有24V信号进来
                                                  (slave_06.MR_switch == 1))          //收料开关打开
                                                  ? ENABLE : DISABLE;                           
        power_ctrl.IW1_enable =                 (slave_06.IW1_switch == 1) ? ENABLE : DISABLE;                              
    }else
    {
        power_ctrl.AC1_enable = power_ctrl.DF_enable = power_ctrl.SF_enable = 0;
        power_ctrl.CW_enable = power_ctrl.AC2_enable = power_ctrl.IW1_enable = 0;
    }

    WK_220V  = (power_ctrl.AC1_enable == ENABLE) ? AC_ON  : AC_OFF;
    MR_220V  = (power_ctrl.AC2_enable == ENABLE) ? AC_ON  : AC_OFF;
    CW_24V   = (power_ctrl.CW_enable  == ENABLE) ? 1  : 0;
    IW_1     = (power_ctrl.IW1_enable  == ENABLE) ? 1  : 0;
}


/**
 * @brief AC输出使能判断
 *
 * @param[in] ntc_value,        当前温度值
              ntc_heat_temp,    加热目标温度  
              pre_temp,         预加热温度
 * 
 * @return  
 * 
**/
uint8_t heat_enable_judge( uint8_t th_value, uint8_t th_heat_temp, uint8_t Insulation_temp )                 
{
    // 第1层检查：后烘干开关  如果关闭，立即返回 0（不加热）
    if( slave_06.PostDry_switch == 0 )
    {
        return DISABLE;
    }

    // 第2层检查：加热需求
    // 如果温度已经达到加热目标温度，立即返回 0（不加热）
    if ( th_value >= th_heat_temp ) 
    {
        return DISABLE;
    }
    
    // 第3层检查：工作模式
    if ( slave_06.sync_switch == 1 ) 
    {  
        if ( power_ctrl.signal_flag == 0 )         // 同步模式且无信号时，只有在预加热状态下才允许加热
        {
            // 在预加热状态下，只有温度低于预加热目标温度时才加热
            if( slave_06.Insulation_switch == 1 )
            {
                if( th_value < Insulation_temp )
                {
                    return ENABLE;
                }else
                {
                    return DISABLE;
                }
            }else
            {
                return DISABLE;
            }
        }
    }
    
    // 其他情况：允许加热
    return ENABLE;
}
