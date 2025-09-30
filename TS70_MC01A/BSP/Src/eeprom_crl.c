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

    if( eeprom_statu_flag != 0x58 )
    {
        slave_06.tc_preheat_temp    = 60;
        slave_06.tc_alarm_temp      = 80;
        slave_06.sf_level           = 30;
        slave_06.df_level           = 30;
        slave_06.iw1_switch         = 1;
        slave_06.iw2_switch         = 1;
        slave_06.cw_switch          = 1;
        slave_06.mr_switch          = 1;
        slave_06.sync_switch        = 1;

        eeprom_data_record(); 
    }
    eeprom_data_init();    
}

/**
 * @brief	主机更改参数后写入
 *
 * @param   
 *
 * @return  void
**/
void eeprom_data_record( void )
{
    ISP_Earse(0x0000);

    ISP_Write(PREHEAT_TEMP_ADDR,slave_06.tc_preheat_temp);
    ISP_Write(ALARM_TEMP_ADDR,slave_06.tc_alarm_temp);
    ISP_Write(SF24_ADDR,slave_06.sf_level);
    ISP_Write(DF24_ADDR,slave_06.df_level);
    ISP_Write(IW1_ADDR,slave_06.iw1_switch);
    ISP_Write(IW2_ADDR,slave_06.iw2_switch);
    ISP_Write(CW_ADDR,slave_06.cw_switch);
    ISP_Write(MR_ADDR,slave_06.mr_switch);
    ISP_Write(SYNC_ADDR,slave_06.sync_switch);

    ISP_Write(EEPROM_STATU_JUDGE,0x58);

    delay_ms(10);
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
    slave_06.tc_preheat_temp = ISP_Read(PREHEAT_TEMP_ADDR);

    slave_06.tc_alarm_temp   = ISP_Read(ALARM_TEMP_ADDR);

    slave_06.sf_level        = ISP_Read(SF24_ADDR);

    slave_06.df_level        = ISP_Read(DF24_ADDR);

    slave_06.iw1_switch      = ISP_Read(IW1_ADDR);
    slave_06.iw2_switch      = ISP_Read(IW2_ADDR);
    IW_ctrl();

    slave_06.cw_switch       = ISP_Read(CW_ADDR);
    CW_ctrl();

    slave_06.mr_switch       = ISP_Read(MR_ADDR);
    MR_ctrl();

    slave_06.sync_switch     = ISP_Read(SYNC_ADDR);

    PN1_24V = DD_24V = PN2_24V = 1;
}
