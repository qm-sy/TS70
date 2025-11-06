#include "gui_ctrl.h"

SP350 sp350;
HANSEN hansen;
DAYIN_T dayin_t;
MC01 mc01;

void sp350_parms_init( void )
{
    Write_Dgus(0x2010,(uint16_t)sp350.F_alarm_val);
    Write_Dgus(0x2011,(uint16_t)sp350.M_alarm_val);
    Write_Dgus(0x2012,(uint16_t)sp350.R_alarm_val);
    Write_Dgus(0x2013,(uint16_t)sp350.F_switch);
    Write_Dgus(0x2014,(uint16_t)sp350.M_switch);
    Write_Dgus(0x2015,(uint16_t)sp350.R_switch);
    Write_Dgus(0x2016,(uint16_t)sp350.LED_switch);
    Write_Dgus(0x2017,(uint16_t)sp350.fan_level);
    Write_Dgus(0x2018,(uint16_t)sp350.fan_switch);
}

void mc01_parms_init( void )
{
    Write_Dgus(0x2103,(uint16_t)mc01.PostDry_switch);
    Write_Dgus(0x2105,(uint16_t)mc01.PostDry_temp);

    Write_Dgus(0x2110,(uint16_t)((mc01.SF_direction << 8) | mc01.SF_switch));
    Write_Dgus(0x2111,(uint16_t)mc01.SF_level);

    Write_Dgus(0x2112,(uint16_t)((mc01.DF_direction << 8) | mc01.DF_switch));
    Write_Dgus(0x2113,(uint16_t)mc01.DF_level);

    Write_Dgus(0x2114,(uint16_t)((mc01.IW2_switch << 8) | mc01.IW1_switch));

    Write_Dgus(0x2115,(uint16_t)mc01.CW_switch);
    Write_Dgus(0x2116,(uint16_t)mc01.MR_switch);

    Write_Dgus(0x2117,(uint16_t)mc01.Insulation_switch);
    Write_Dgus(0x2118,(uint16_t)mc01.Insulation_temp);
    
    Write_Dgus(0x2119,(uint16_t)mc01.sync_switch);
    Write_Dgus(0x211A,(uint16_t)mc01.power_switch);
}


void diwen_parms_init( void )
{
    hansen.ctrl_flag = 0;
    hansen.connect_flag = 0;
    hansen.addr_0x00 = 0x00;
    hansen.addr_0x02 = 0x00;
    hansen.addr_0x06 = 0x0149;
    hansen.addr_0x10 = 0x1f;
    hansen.addr_0x20 = 0x00;
    hansen.addr_0x21 = 0x00;
    hansen.addr_0x22 = 0x01;
    hansen.addr_0x23 = 0x0f;
    hansen.addr_0x2d = 0x00;
    hansen.addr_0x30 = 0x00;
    hansen.addr_0x0c = 0x01;

    hansen.paoji_flag = hansen.paoji_send = 0;
    hansen.paoji_h = hansen.paoji_min = hansen.paoji_s = 0;
    jump_page(12);
}

void gui_vol_ctrl( uint16_t addr, uint8_t val_H, uint8_t val_L)
{
    uint8_t val_tab[2] = {0};
    uint8_t utf_tab[4] = {0XBA,0XDA,0XD4,0XB2};
    uint8_t i = 0;
    static uint8_t addr_20a0 = 0;

    switch ( addr )
    {   
        /*      0x20 马达复位：置1后开始复位，等待被置0        */
        /*      0x20 跑机操作：置1后开始复位，等待被置0        */
        /*      0x20 点动操作：置1一直移动，写0后停止移动      */
        /*      0x20 bit0  x马达复位     */
        /*      0x20 bit3  左移          */
        /*      0x20 bit4  右移          */
        /*      0x20 bit5  进料          */
        /*      0x20 bit6  退料          */
        /*      0x20 bit9  开始跑机      */
        /*      0x20 bit13  停止跑机     */
        case 0x2020:
            hansen.addr_0x20 = (val_H << 8) |  val_L;
            
            break;

        case 0x2021:
            hansen.addr_0x21 = (val_H << 8) |  val_L;
            
            break;

        case 0x2022:
            hansen.addr_0x22 = (val_H << 8) |  val_L;
  
            break;   

        case 0x2023:
            hansen.addr_0x23 = (val_H << 8) |  val_L;
            
            break;

        case 0x2030:
            hansen.addr_0x30 = (val_H << 8) |  val_L;
            fuyin_flag = 1;
            
            break;

        case 0x2051:
            hansen.addr_0x06 &= ~0x07;
            switch (val_L)
            {
                case 1: hansen.addr_0x06 |= 0x01;       break;
                case 2: hansen.addr_0x06 |= 0x02;       break;
                case 4: hansen.addr_0x06 |= 0x04;       break;
                default:                                break;
            }
            
            break;

        case 0x2052:
            hansen.addr_0x06 &= ~0x38;
            switch (val_L)
            {
                case 1: hansen.addr_0x06 |= 0x08;       break;
                case 2: hansen.addr_0x06 |= 0x10;       break;
                case 4: hansen.addr_0x06 |= 0x20;       break;
                default:                                break;
            }
            
            break;

        case 0x2053:
            hansen.addr_0x06 &= ~0xC0;
            switch (val_L)
            {
                case 1: hansen.addr_0x06 |= 0x40;       break;
                case 2: hansen.addr_0x06 |= 0x80;       break;
                case 4: hansen.addr_0x06 |= 0xc0;       break;
                default:                                break;
            }
            
            break;

        case 0x2054:
            hansen.addr_0x06 &= ~0x0700;
            switch (val_L)
            {
                case 1: hansen.addr_0x06 |= 0x0100;     break;
                case 2: hansen.addr_0x06 |= 0x0200;     break;
                case 4: hansen.addr_0x06 |= 0x0400;     break;
                default:                                break;
            }
            
            break;

        case 0x2055:
            hansen.addr_0x06 &= ~0x1800;
            switch (val_L)
            {
                case 1: hansen.addr_0x06 |= 0x0000;     break;
                case 2: hansen.addr_0x06 |= 0x0800;     break;
                case 4: hansen.addr_0x06 |= 0x1000;     break;
                case 8: hansen.addr_0x06 |= 0x1800;     break;
                default:                                break;
            }
            
            break;

        case 0x2060:
            hansen.addr_0x00 = (val_H << 8) |  val_L;
            
            break;

        case 0x2062:
            hansen.addr_0x02 = (val_H << 8) |  val_L;
            
            break;

        case 0x2033:

            Write_Dgusii_Vp_byChar(0x20c0,utf_tab,4);

            break;

        case 0x2090:
            addr_20a0 = 0;
            break;

        case 0x2098:
            if( mima_val == 222222 )
            {
                jump_page(10);
                mima_val = 0;
                Write_Dgus(0x2090,0x01);
                Write_Dgus(0x2091,0xe240);
            } 
           
            break;

        case 0x20a0:
            if( val_L == 1 ) 
            {
                hansen.addr_0x20 = 0x0200;
                hansen.paoji_flag = 1;
            }else
            {
                hansen.addr_0x20 = 0x2000;
                Write_Dgus(0x20a4,0);
                Write_Dgus(0x20a3,0);
                Write_Dgus(0x20a2,0);
                jump_page(0);
                hansen.paoji_flag = 0;
            }  
            addr_20a0 = val_L;

            break;

        case 0x20d6:
            if( val_L == 4 )
            {
                hansen.addr_0x2d = 3;    
            }
            if( val_L == 3 )
            {
                hansen.addr_0x2d = 4;    
            }
            break;

        case 0x20d7:
            if(hansen.addr_0x2d == 3 )
            {
                hansen.addr_0x21 = 1;
                Write_Dgusii_Vp_byChar(0x1600,"印中清洗",8);
            }

            break;  

        case 0x20d8:
            hansen.addr_0x2d = val_L;
            jump_page(0);
            break;

        case 0x20a1:
            if( addr_20a0 == 0 )
            jump_page(0);
            break;
        /*          40001 设置F_alarm_val(val_L) M_alarm_val(val_H)          */
        case 0x2010:
            sp350.F_alarm_val = val_L;
            write_slave_06(F_TEMP_ALARM,0,sp350.F_alarm_val);  

            break;
        
        case 0x2011:
            sp350.M_alarm_val = val_L;
            write_slave_06(M_TEMP_ALARM,0,sp350.M_alarm_val);    

            break;

        case 0x2012:
            sp350.R_alarm_val = val_L;
            write_slave_06(R_TEMP_ALARM,0,sp350.R_alarm_val);  
            
            break;

				 
        /*          40002 设置 F\M\R  Switch                                 */
        case 0x2013:
            sp350.F_switch = val_L;
            write_slave_06(F_AC_SWITCH,0,sp350.F_switch);  

            break;
        
        case 0x2014:
            sp350.M_switch = val_L;
            write_slave_06(M_AC_SWITCH,0,sp350.M_switch); 

            break;

        case 0x2015:
            sp350.R_switch = val_L;
            write_slave_06(R_AC_SWITCH,0,sp350.R_switch); 

            break;

        case 0x2016:
            sp350.LED_switch = val_L;
            write_slave_06(LED_ADDR,0,sp350.LED_switch); 

            break;

        case 0x2017:
            sp350.fan_level = val_L;
            write_slave_06(FAN_ADDR,0,sp350.fan_level); 

            break; 

        case 0x2018:
            sp350.fan_switch = val_L;
            write_slave_06(FAN_SWITCH,0,sp350.fan_switch); 

            break; 

        case 0x2100:

            break;

        case 0x2101:

            break;

        case 0x2102:

            break;

        case 0x2103:
            write_slave_06_MC01(0x00,val_H,val_L);
            break;

        case 0x2104:

            break;

        case 0x2105:
            write_slave_06_MC01(0x01,val_H,val_L);
            break;

        case 0x2110:
            write_slave_06_MC01(0x02,val_H,val_L);
            break;

        case 0x2111:
            write_slave_06_MC01(0x03,val_H,val_L);
            break;

        case 0x2112:
            write_slave_06_MC01(0x04,val_H,val_L);
            break;

        case 0x2113:
            write_slave_06_MC01(0x05,val_H,val_L);
            break;

        case 0x2114:
            write_slave_06_MC01(0x06,val_H,val_L);
            break;

        case 0x2115:
            write_slave_06_MC01(0x07,val_H,val_L);
            break;

        case 0x2116:
            write_slave_06_MC01(0x08,val_H,val_L);
            break;

        case 0x2117:
            write_slave_06_MC01(0x09,val_H,val_L);
            break;

        case 0x2118:
            write_slave_06_MC01(0x0a,val_H,val_L);
            break;

        case 0x2119:
            write_slave_06_MC01(0x0b,val_H,val_L);
            break;

        case 0x211a:
            write_slave_06_MC01(0x0c,val_H,val_L);
            break;
        default:
            break;
    }
}


void jump_page( uint8_t page_num )
{
    Write_Dgus(0x0085,page_num);

    Write_Dgus(0x0084,0x5A01);
}

void time_trans( uint16_t time_val ,uint8_t num )
{
    if( num == 0 )
    {
        dayin_t.cnt_h = time_val / 3600;
        dayin_t.cnt_min = (time_val % 3600) / 60;
        dayin_t.cnt_s = time_val % 60;
    }else
    {
        dayin_t.remain_h = time_val / 3600;
        dayin_t.remain_min = (time_val % 3600) / 60;
        dayin_t.remain_s = time_val % 60;
    }
}