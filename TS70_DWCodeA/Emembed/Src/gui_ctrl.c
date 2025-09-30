#include "gui_ctrl.h"

SP350 sp350;
HANSEN hansen;

void sp350_parms_init( void )
{
    sp350.alarm_tempF = 50;         
    sp350.alarm_tempM = 55;         
    sp350.alarm_tempR = 60;         
    sp350.F_switch    = 1;          
    sp350.M_switch    = 1;          
    sp350.R_switch    = 1;          
    sp350.LED_switch  = 1;          
    sp350.fan_switch  = 1;         
    sp350.fan_level   = 1;

    sys_write_vp(0x2010,(uint8_t*)&sp350.alarm_tempF,1);
    sys_write_vp(0x2011,(uint8_t*)&sp350.alarm_tempM,1);
    sys_write_vp(0x2012,(uint8_t*)&sp350.alarm_tempR,1);

    sys_write_vp(0x2013,(uint8_t*)&sp350.F_switch,1);
    sys_write_vp(0x2014,(uint8_t*)&sp350.M_switch,1);
    sys_write_vp(0x2015,(uint8_t*)&sp350.R_switch,1);

    sys_write_vp(0x2016,(uint8_t*)&sp350.LED_switch,1);

    sys_write_vp(0x2017,(uint8_t*)&sp350.fan_switch,1);
    sys_write_vp(0x201a,(uint8_t*)&sp350.fan_level,1);
}

void diwen_parms_init( void )
{
    hansen.addr_0x00 = 0x00;
    hansen.addr_0x02 = 0x00;
    hansen.addr_0x06 = 0x1949;
    hansen.addr_0x20 = 0x00;
    hansen.addr_0x21 = 0x00;
    hansen.addr_0x22 = 0x00;
    hansen.addr_0x23 = 0x0f;
    hansen.addr_0x2d = 0x00;
    hansen.addr_0x30 = 0x00;

    hansen.addr_0x20_02 = hansen.addr_0x06 & 0x03;
    hansen.addr_0x20_35 = (hansen.addr_0x06 & 0x38) >> 3;
    hansen.addr_0x20_67 = (hansen.addr_0x06 & 0xc0) >> 6;
    hansen.addr_0x20_8a = (hansen.addr_0x06 & 0x0700) >> 8;
    hansen.addr_0x20_bc = (hansen.addr_0x06 & 0x1800) >> 11;

    sys_write_vp(0x2051,(uint8_t*)&(hansen.addr_0x20_02),1);
    sys_write_vp(0x2052,(uint8_t*)&(hansen.addr_0x20_35),1);
    sys_write_vp(0x2053,(uint8_t*)&(hansen.addr_0x20_67),1);
    sys_write_vp(0x2054,(uint8_t*)&(hansen.addr_0x20_8a),1);    
    sys_write_vp(0x2055,(uint8_t*)&(hansen.addr_0x20_bc),1);


    sys_write_vp(0x2020,(uint8_t*)&hansen.addr_0x20,1);
    sys_write_vp(0x2021,(uint8_t*)&hansen.addr_0x21,1);
    sys_write_vp(0x2022,(uint8_t*)&hansen.addr_0x22,1);
    sys_write_vp(0x2023,(uint8_t*)&hansen.addr_0x23,1);

    sys_write_vp(0x2060,(uint8_t*)&hansen.addr_0x00,1);
    sys_write_vp(0x2062,(uint8_t*)&hansen.addr_0x02,1);
}

void gui_vol_ctrl( uint16_t addr, uint8_t val_H, uint8_t val_L)
{
    uint8_t val_tab[2] = {0};

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

        case 0x2051:
            hansen.addr_0x06 |= ((val_H << 8) |  val_L & 0x03);
            
            break;

        case 0x2052:
            hansen.addr_0x06 |= ((val_H << 8) |  val_L & 0x38);
            
            break;

        case 0x2053:
            hansen.addr_0x06 |= ((val_H << 8) |  val_L & 0xC0);
            
            break;

        case 0x2054:
            hansen.addr_0x06 |= ((val_H << 8) |  val_L & 0x0700);
            
            break;

        case 0x2055:
            hansen.addr_0x06 |= ((val_H << 8) |  val_L & 0x1800);
            
            break;

        case 0x2060:
            hansen.addr_0x00 = (val_H << 8) |  val_L;
            
            break;

        case 0x2062:
            hansen.addr_0x02 = (val_H << 8) |  val_L;
            
            break;

        case 0x2033:
            Write_Dgusii_Vp_byChar(0x1600,"乔铭",4);
            
            break;
        /*          40001 设置alarm_tempF(val_L) alarm_tempM(val_H)          */
        case 0x2010:
            sp350.alarm_tempF = val_L;
            write_slave_06(UART_5,ALARM_TEMP12_ADDR,(uint8_t)sp350.alarm_tempM,(uint8_t)sp350.alarm_tempF);  

            break;
        
        case 0x2011:
            sp350.alarm_tempM = val_L;
            write_slave_06(UART_5,ALARM_TEMP12_ADDR,(uint8_t)sp350.alarm_tempM,(uint8_t)sp350.alarm_tempF);   

            break;

        case 0x2012:
            sp350.alarm_tempR = val_L;
            write_slave_06(UART_5,ALARM_TEMP3_ADDR,0,(uint8_t)sp350.alarm_tempR);  
            
            break;

				 
        /*          40002 设置 F\M\R  Switch                                 */
        case 0x2013:
            sp350.F_switch = val_L;
            write_slave_06(UART_5,FM_SWITCH_ADDR,(uint8_t)sp350.M_switch,(uint8_t)sp350.F_switch);  

            break;
        
        case 0x2014:
            sp350.M_switch = val_L;
            write_slave_06(UART_5,FM_SWITCH_ADDR,(uint8_t)sp350.M_switch,(uint8_t)sp350.F_switch); 

            break;

        case 0x2015:
            sp350.R_switch = val_L;
            write_slave_06(UART_5,R_SWITCH_ADDR,0,(uint8_t)sp350.R_switch); 

            break;

        case 0x2016:
            sp350.LED_switch = val_L;
            write_slave_06(UART_5,LED_SWITCH_ADDR,0,(uint8_t)sp350.LED_switch); 

            break;

        case 0x2017:
            sp350.fan_switch = val_L;
            write_slave_06(UART_5,LED_SWITCH_ADDR,(uint8_t)sp350.fan_switch,(uint8_t)sp350.fan_level); 

            break; 

        case 0x3018:
            sp350.fan_level = val_L;
            write_slave_06(UART_5,FAN_ADDR,(uint8_t)sp350.fan_switch,(uint8_t)sp350.fan_level); 

            break; 

        default:
            break;
    }
}