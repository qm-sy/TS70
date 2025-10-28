#include "eeprom_crl.h"

/**
 * @brief	eeprom状态判定，是否写入过
 *
 * @param   
 *
 * @return  void
**/
void eeprom_statu_judge( void )
{
    uint8_t eeprom_statu_flag;

    eeprom_statu_flag = ISP_Read(EEPROM_STATU_JUDGE);

    if( eeprom_statu_flag == 0xFF)
    {
        slave_06.F_switch           = 0;
        slave_06.M_switch           = 0;
        slave_06.R_switch           = 0;
        slave_06.F_alarm_val        = 0x50;          //NTC1 alarm value 默认80℃
        slave_06.M_alarm_val        = 0x50;          //NTC2 alarm value 默认80℃  
        slave_06.R_alarm_val        = 0x50;          //NTC3 alarm value 默认80℃ 
        slave_06.fan_level          = 0x04;          //011 pwm7默认开3档风速
        slave_06.fan_switch         = 0;
        slave_06.led_switch         = 0;          //0000000 1  led默认开
        eeprom_data_record(); 
    }
    eeprom_data_init();    
}

/**
 * @brief	eeprom 数据写入
 *
 * @param   
 *
 * @return  void
**/
void eeprom_data_record( void )
{
    ISP_Earse(0x0000);

    ISP_Write(F_AC_SWITCH,slave_06.F_switch);
    ISP_Write(M_AC_SWITCH,slave_06.M_switch);
    ISP_Write(R_AC_SWITCH,slave_06.R_switch);
    ISP_Write(F_TEMP_ALARM,slave_06.F_alarm_val);
    ISP_Write(M_TEMP_ALARM,slave_06.M_alarm_val);
    ISP_Write(R_TEMP_ALARM,slave_06.R_alarm_val);
    ISP_Write(LED_ADDR,slave_06.led_switch);
    ISP_Write(FAN_ADDR,slave_06.fan_level);
    ISP_Write(FAN_SWITCH,slave_06.fan_switch);

    ISP_Write(EEPROM_STATU_JUDGE,0x58);
}

/**
 * @brief	eeprom 数据初始化
 *
 * @param   
 *
 * @return  void
**/
void eeprom_data_init( void )
{
    /*    LED开关状态初始化    */
    slave_06.led_switch = ISP_Read(LED_ADDR);
    led_ctrl(slave_06.led_switch);

    /*    PWM7、PWM8 风速及开关状态初始化    */
    slave_06.fan_level  = ISP_Read(FAN_ADDR);
    slave_06.fan_switch = ISP_Read(FAN_SWITCH);
    fan_ctrl(slave_06.fan_switch,slave_06.fan_level);

    /*    220V输出开关状态初始化    */
    slave_06.F_switch = ISP_Read(F_AC_SWITCH);
    slave_06.M_switch = ISP_Read(M_AC_SWITCH);
    slave_06.R_switch = ISP_Read(R_AC_SWITCH);
    slave_06.F_alarm_val = ISP_Read(F_TEMP_ALARM);
    slave_06.M_alarm_val = ISP_Read(M_TEMP_ALARM);
    slave_06.R_alarm_val = ISP_Read(R_TEMP_ALARM);
}
