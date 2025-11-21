#ifndef __POWER_CRL_H_
#define __POWER_CRL_H_

#include "sys.h"
#include "gpio.h"
#include "ntc.h"
#include "eeprom_crl.h"

#define AC_ON      0
#define AC_OFF     1

#define FAN_ON      1
#define FAN_OFF     0

#define SW_OPEN      1
#define SW_CLOSE     0

#define ENABLE     1
#define DISABLE    0

#define BUZZER_ON      0
#define BUZZER_OFF     1

typedef struct 
{
    uint8_t  F_HeatTemp;
    uint8_t  F_HeatSwitch;
    uint8_t  M_HeatTemp;
    uint8_t  M_HeatSwitch;
    uint8_t  R_HeatTemp;         
    uint8_t  R_HeatSwitch;
    uint8_t  SF_Direction;           
    uint8_t  SF_level; 
    uint8_t  SF_Switch; 
    uint8_t  HF_Direction;           
    uint8_t  HF_level;  
    uint8_t  HF_Switch; 
    uint8_t  sync_switch;           
    uint8_t  sync_signal;  
    uint8_t  sync_signal_turndown;  
    uint8_t  sync_switch_delay; 
    uint8_t  hf_reset_flag;  
    uint8_t  signal_back;   
}SLAVE_06;

typedef struct 
{
    uint8_t  AC1_enable; 
    uint8_t  AC2_enable; 
    uint8_t  AC3_enable; 
    uint8_t  PWM1_enable; 
    uint8_t  PWM2_enable; 
    uint8_t  PWM3_enable; 
    uint8_t  FanTemp_enable; 
    uint8_t  Buzzer_enable; 
    uint8_t  power_switch;
}POWER_CTRL;

extern SLAVE_06 slave_06;
extern POWER_CTRL power_ctrl;

void Power_Init( void );
void temp_scan( void );
uint8_t heat_enable_judge(uint8_t CH_switch, uint8_t TherMo_value, uint8_t CH_heat_temp);
void ac_dc_ctrl( void );
void motor_enable_judge( void );
void sync_signal_listen( void );
void sync_switch_listen( void );
void motor_state_set( void );

#endif