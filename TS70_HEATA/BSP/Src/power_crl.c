#include "power_crl.h"

SLAVE_06 slave_06;
POWER_CTRL power_ctrl;


void Power_Init( void )
{
    /*  开机状态置一                */
    power_ctrl.power_switch = 1;

    AC_Out1 = AC_Out2 = AC_Out3 = AC_OFF;

    Buzzer = BUZZER_OFF;
    slave_06.sync_signal_turndown = 0;
    slave_06.sync_switch_delay = 0;
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
    uint16_t *temp_val = NULL;

    if( temp.scan_flag == 1 )
    {
        temp_val = max6675_readTemp();

        temp.thermo1_temp = temp_val[0];
        temp.thermo2_temp = temp_val[1];
        temp.thermo3_temp = temp_val[2];

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
    if( power_ctrl.power_switch == 1 )
    {
        power_ctrl.AC1_enable = heat_enable_judge(slave_06.F_HeatSwitch,
                                                  temp.thermo1_temp,            // 温度传感器1的当前值
                                                  slave_06.F_HeatTemp           // 通道F的加热目标温度
                                                  ) ? ENABLE : DISABLE;         // 根据函数返回值设置使能状态

        power_ctrl.AC2_enable = heat_enable_judge(slave_06.M_HeatSwitch,
                                                  temp.thermo2_temp,            // 温度传感器2的当前值
                                                  slave_06.M_HeatTemp           // 通道M的加热目标温度
                                                  ) ? ENABLE : DISABLE;         // 根据函数返回值设置使能状态

        power_ctrl.AC3_enable = heat_enable_judge(slave_06.R_HeatSwitch,
                                                  temp.thermo3_temp,            // 温度传感器3的当前值
                                                  slave_06.R_HeatTemp          // 通道R的加热目标温度
                                                  ) ? ENABLE : DISABLE;         // 根据函数返回值设置使能状态

        power_ctrl.FanTemp_enable = ENABLE;

        motor_enable_judge();
    }else
    {
        power_ctrl.AC1_enable = power_ctrl.AC2_enable = power_ctrl.AC3_enable = DISABLE;
        power_ctrl.FanTemp_enable = DISABLE;
        PWMB_ENO = 0;
    }
    
    AC_Out1  = (power_ctrl.AC1_enable == ENABLE) ? AC_ON  : AC_OFF;
    AC_Out2  = (power_ctrl.AC2_enable == ENABLE) ? AC_ON  : AC_OFF;
    AC_Out3  = (power_ctrl.AC3_enable == ENABLE) ? AC_ON  : AC_OFF;
    Fan_Temp = (power_ctrl.FanTemp_enable == ENABLE) ? FAN_ON  : FAN_OFF;
    PWMB_CCR5 = 183 * slave_06.SF_level;
    PWMB_CCR6 = PWMB_CCR7 = 183 * slave_06.HF_level;
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
uint8_t heat_enable_judge(uint8_t CH_switch, uint8_t TherMo_value, uint8_t CH_heat_temp)                 
{
    // 第1层检查：加热开关
    if( CH_switch == 0 )
    {
        return DISABLE;
    }
    
    // 第2层检查：加热需求
    // 如果温度已经达到加热目标温度，立即返回 0（不加热）
    if ( TherMo_value >= CH_heat_temp ) 
    {
        return DISABLE;
    }
    
    // 第3层检查：工作模式  同步模式下，无同步信号则不进行加热
    if ( slave_06.sync_switch == SW_OPEN ) 
    {  
        if ( slave_06.sync_signal == 0 )         
        {
           return DISABLE;
        }
    }
    
    // 其他情况：允许加热
    return ENABLE;
}

void motor_enable_judge( void )
{
    sync_signal_listen();
    sync_switch_listen();

    if( slave_06.sync_switch == 0 )
    {
        motor_state_set();
    }else
    {
        if( slave_06.sync_signal == 0 )
        {
            if( slave_06.sync_signal_turndown == 1 )
            {
                PWMB_ENO &= 0xeb;
            }else
            {
                PWMB_ENO = 0;
            }
        }
    }
}

void motor_state_set( void )
{
    if( slave_06.sync_switch_delay == 0 )
    {
        if (slave_06.SF_Switch == 1) 
        {
            PWMB_ENO = (slave_06.HF_Switch == 1) ? 
                    (slave_06.HF_Direction == 1 ? 0x11 : 0x05) : 0x01;
        }else 
        {
            PWMB_ENO = (slave_06.HF_Switch == 1) ? 
                    (slave_06.HF_Direction == 1 ? 0x10 : 0x04) : 0x00;
        }
    }else
    {
        PWMB_ENO = 0;
    }

}

/**
 * @brief	同步信号监听 同时满足有同步且同步信号从1↓0时触发风扇延时输出
 *
 * @param   
 *
 * @return  void
**/
void sync_signal_listen( void )
{
    static uint8_t signal_flag = 0;

    if( signal_flag != slave_06.sync_signal )
    {
        signal_flag = slave_06.sync_signal;

        if( slave_06.sync_switch == 1 )     //同步模式下
        {
            if( signal_flag == 0 )          //同步信号 1 →→ 0  J1延时
            {
                slave_06.sync_signal_turndown = 1;
            }else                           //同步信号 0 →→ 1  J2J3复位
            {
                slave_06.hf_reset_flag = 1;
            }
        }
    }
}

/**
 * @brief	同步信号监听 同时满足有同步且同步信号从1↓0时触发风扇延时输出
 *
 * @param   
 *
 * @return  void
**/
void sync_switch_listen( void )
{
    static uint8_t switch_flag = 0;

    if( switch_flag != slave_06.sync_switch )
    {
        switch_flag = slave_06.sync_switch;

        if(( switch_flag == 1 ) && ( slave_06.sync_signal == 1 ))       //手动 →→ 自动 且有同步信号J2J3复位
        {
            slave_06.hf_reset_flag = 1;
        }

        if( switch_flag == 0 )
        {
            slave_06.sync_switch_delay = 1;
        }
    }
}
