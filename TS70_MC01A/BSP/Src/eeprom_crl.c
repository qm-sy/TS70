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
        slave_06.PostDry_switch     = 1;
        slave_06.PostDry_temp       = 80;
        slave_06.SF_switch          = 1;
        slave_06.SF_direction       = 0;
        slave_06.SF_level           = 30;
        slave_06.DF_switch          = 1;
        slave_06.DF_direction       = 0;
        slave_06.DF_level           = 30;
        slave_06.IW1_switch         = 1;
        slave_06.IW2_switch         = 1;
        slave_06.CW_switch          = 1;
        slave_06.MR_switch          = 1;
        slave_06.Insulation_switch  = 1;
        slave_06.Insulation_temp    = 80;
        slave_06.sync_switch        = 0;

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

    ISP_Write(PD_SWITCH,slave_06.PostDry_switch);
    ISP_Write(PD_TEMP,slave_06.PostDry_temp);
    ISP_Write(SF_SWITCH,slave_06.SF_switch);
    ISP_Write(SF_DIRECTION,slave_06.SF_direction);
    ISP_Write(SF_LEVEL,slave_06.SF_level);
    ISP_Write(DF_SWITCH,slave_06.DF_switch);
    ISP_Write(DF_DIRECTION,slave_06.DF_direction);
    ISP_Write(DF_LEVEL,slave_06.DF_level);
    ISP_Write(IW1_SWITCH,slave_06.IW1_switch);
    ISP_Write(IW2_SWITCH,slave_06.IW2_switch);
    ISP_Write(CW_SWITCH,slave_06.CW_switch);
    ISP_Write(MR_SWITCH,slave_06.MR_switch);
    ISP_Write(INSU_SWITCH,slave_06.Insulation_switch);
    ISP_Write(INSU_TEMP,slave_06.Insulation_temp);
    ISP_Write(SYNC_SWITCH,slave_06.sync_switch);

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
    slave_06.PostDry_switch     = ISP_Read(PD_SWITCH);
    slave_06.PostDry_temp       = ISP_Read(PD_TEMP);

    slave_06.SF_switch          = ISP_Read(SF_SWITCH);
    slave_06.SF_direction       = ISP_Read(SF_DIRECTION);
    slave_06.SF_level           = ISP_Read(SF_LEVEL);

    slave_06.DF_switch          = ISP_Read(DF_SWITCH);
    slave_06.DF_direction       = ISP_Read(DF_DIRECTION);
    slave_06.DF_level           = ISP_Read(DF_LEVEL);

    slave_06.IW1_switch         = ISP_Read(IW1_SWITCH);
    slave_06.IW2_switch         = ISP_Read(IW2_SWITCH);

    slave_06.CW_switch          = ISP_Read(CW_SWITCH);

    slave_06.MR_switch          = ISP_Read(MR_SWITCH);

    slave_06.Insulation_switch  = ISP_Read(INSU_SWITCH);
    slave_06.Insulation_temp    = ISP_Read(INSU_TEMP);

    slave_06.sync_switch        = ISP_Read(SYNC_SWITCH);

    slave_06.power_switch       = 1;
}
