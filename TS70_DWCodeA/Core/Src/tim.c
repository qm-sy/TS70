#include "tim.h"

bit gui_scan_flag;
uint16_t scan_03_cnt_350p = 0;
uint16_t scan_03_cnt_mc01 = 0;

void Tim0_Init( void )      //1ms
{
    TMOD &= 0xfc;           //设置为16bit的定时器工作模式
    TMOD |= 0x01;           //T0_M1 = 0 T0_M0 = 0: 16位自动重装载模式 

    TH0   = (uint8_t)(T0_PERIOD_1MS>>8);
    TL0   = (uint8_t)T0_PERIOD_1MS;   

    ET0   = 1;              //使能中断
    TR0   = 1;              //启动T0定时器
    //TF0 = 0;              //硬件自动清0
}

void Tim1_Init( void )      //1ms
{
    TMOD &= 0xcf;           //设置为16bit的定时器工作模式
    TMOD |= 0x10;           //T1_M1 = 0 T1_M0 = 0: 16位自动重装载模式 

    TH1   = (uint8_t)(T0_PERIOD_1MS>>8);
    TL1   = (uint8_t)T0_PERIOD_1MS;        

    ET1   = 1;              //使能中断
    TR1   = 1;              //启动T1定时器
    //TF1 = 0;              //硬件自动清0
}

void Tim0_Isr( void ) interrupt 1
{
    static uint8_t press_scan_cnt = 0;
    static uint16_t paoji_cnt = 0;
    static uint16_t temp_scan_cnt = 0;
    static uint16_t send04_cnt = 0;
    static uint16_t send06_cnt = 0;
    static uint16_t press_cnt = 0;

    TH0   = (uint8_t)(T0_PERIOD_1MS>>8);
    TL0   = (uint8_t)T0_PERIOD_1MS;      

	if(T_O2 > 0)
    {
        T_O2--;
    }

    if( gui_scan_flag == 0 )
    {
        press_scan_cnt++;
        if( press_scan_cnt == 50 )
        {
            press_scan_cnt = 0;
            gui_scan_flag = 1;
        }
    }

    if( hansen.paoji_flag  == 1 )
    {
        paoji_cnt++;
        if( paoji_cnt == 1000 )
        {
            paoji_cnt = 0;
            hansen.paoji_s++;
            if( hansen.paoji_s == 60 )
            {
                hansen.paoji_s = 0;
                hansen.paoji_min++;
                if( hansen.paoji_min == 60 )
                {
                    hansen.paoji_min = 0;
                    hansen.paoji_h++;
                }
            }
            hansen.paoji_send = 1;
        }
    }else
    {
        hansen.paoji_send = 0;
        hansen.paoji_h = hansen.paoji_min = hansen.paoji_s = 0;
        paoji_cnt = 0;
    }

    if(( sp350.params_get_flag1 == 1 ) && ( sp350.params_get_flag2 == 0 ))
    {
        scan_03_cnt_350p++;
        if( scan_03_cnt_350p == 200 )
        {
            sp350.params_get_flag2 = 1;
            scan_03_cnt_350p = 0;
        }
    }else
    {
        scan_03_cnt_350p = 0;
    }

    if(( mc01.params_get_flag1 == 1 ) && ( mc01.params_get_flag2 == 0 ))
    {
        scan_03_cnt_mc01++;
        if( scan_03_cnt_mc01 == 500 )
        {
            mc01.params_get_flag2 = 1;
            scan_03_cnt_mc01 = 0;
        }
    }else
    {
        scan_03_cnt_mc01 = 0;
    }


    if( mc01.temp_scan_flag == 0 )
    {
        temp_scan_cnt++;
        if( temp_scan_cnt == 1000 )
        {
            mc01.temp_scan_flag = 1;
            temp_scan_cnt = 0;
        }
    }
    if(( temp_scan_cnt >= 1000 ) || ( temp_scan_cnt < 0 ))
    {
        temp_scan_cnt = 0;
    }

    if(( rs485_2.fun06_rcv_out == 0 ) && ( rs485_2.comm_error_flag == 0))
    {
        send06_cnt++;
        if( send06_cnt == 500 )
        {
            rs485_2.comm_error_flag = 1;
            rs485_2.fun04_rcv_out   = 0;
            send06_cnt = 0;
        }
    }else
    {
        send06_cnt = 0;
    }

    if(( rs485_2.fun04_rcv_out == 0 ) && ( rs485_2.comm_error_flag == 0))
    {
        send04_cnt++;
        if( send04_cnt == 500 )
        {
            rs485_2.comm_error_flag = 1;
            rs485_2.fun06_rcv_out   = 0;
            send04_cnt = 0;
        }
    }else
    {
        send04_cnt = 0;
    }

    if(( rs485_2.press_flag1 == 1 ) && ( rs485_2.press_flag2 == 0 ))
    {
        press_cnt++;
        if( press_cnt == 3000 )
        {
            rs485_2.press_flag1 = 0;
        }
    }else
    {
        press_cnt = 0;
    }
}

