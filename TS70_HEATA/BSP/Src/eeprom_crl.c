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
        slave_06.F_HeatTemp     = 80;
        slave_06.F_HeatSwitch   = 1;
        slave_06.M_HeatTemp     = 80;
        slave_06.M_HeatSwitch   = 1;
        slave_06.R_HeatTemp     = 80;
        slave_06.R_HeatSwitch   = 1;                     
        slave_06.SF_level       = 3;  
        slave_06.SF_Switch      = 1;
        slave_06.HF_Direction   = 0;           
        slave_06.HF_level       = 3;  
        slave_06.HF_Switch      = 1;
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

    ISP_Write(F_HEAT_TEMP,slave_06.F_HeatTemp);
    ISP_Write(F_HEAT_SWITCH,slave_06.F_HeatSwitch);
    ISP_Write(M_HEAT_TEMP,slave_06.M_HeatTemp);
    ISP_Write(M_HEAT_SWITCH,slave_06.M_HeatSwitch);
    ISP_Write(R_HEAT_TEMP,slave_06.R_HeatTemp);
    ISP_Write(R_HEAT_SWITCH,slave_06.R_HeatSwitch);
    ISP_Write(SF_LEVEL,slave_06.SF_level);
    ISP_Write(SF_SWITCH,slave_06.SF_Switch);
    ISP_Write(HF_DIRECTION,slave_06.HF_Direction);
    ISP_Write(HF_LEVEL,slave_06.HF_level);        
    ISP_Write(HF_SWITCH,slave_06.HF_Switch); 

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
    slave_06.F_HeatTemp     = ISP_Read(F_HEAT_TEMP);
    slave_06.F_HeatSwitch   = ISP_Read(F_HEAT_SWITCH);
    slave_06.M_HeatTemp     = ISP_Read(M_HEAT_TEMP);
    slave_06.M_HeatSwitch   = ISP_Read(M_HEAT_SWITCH);
    slave_06.R_HeatTemp     = ISP_Read(R_HEAT_TEMP);
    slave_06.R_HeatSwitch   = ISP_Read(R_HEAT_SWITCH);
    slave_06.SF_level       = ISP_Read(SF_LEVEL);
    slave_06.SF_Switch      = ISP_Read(SF_SWITCH);
    slave_06.HF_Direction   = ISP_Read(HF_DIRECTION);
    slave_06.HF_level       = ISP_Read(HF_LEVEL);
    slave_06.HF_Switch      = ISP_Read(HF_SWITCH);

    slave_06.sync_switch    = 0;           
    slave_06.sync_signal    = 0;  
    slave_06.signal_back    = 0;  
}

