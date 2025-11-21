#include "common.h"

/**
 * @brief	一些定时执行的事件   Timer3：10ms
 *
 * @param   
 *
 * @return  void
**/
void Tim3_ISR( void ) interrupt 19
{
    static uint16_t temp_scan_cnt = 0;
    static uint16_t sync_signal_cnt  = 0;
    static uint16_t sync_switch_cnt  = 0;
    static uint16_t sync_delay_cnt  = 0;
    /* 1, temp 上报 1s/次           */
    if( temp.scan_flag == 0 )
    {
        temp_scan_cnt++;
        if( temp_scan_cnt == 100 )
        {
            temp_scan_cnt  = 0;
            temp.scan_flag = 1;
        }
    }
    if( slave_06.sync_signal_turndown == 1 )
    {
        sync_signal_cnt++;
        if( sync_signal_cnt == 500 )
        {
            slave_06.sync_signal_turndown = 0;
            sync_signal_cnt = 0;
            PWMB_ENO &= 0xfe;
        }
    }

    if(( slave_06.hf_reset_flag == 1 ) && ( slave_06.HF_Switch == 1 )) 
    {
        sync_switch_cnt++;
        if( sync_switch_cnt == 1 )      
        {
            PWMB_ENO &= 0x01;           //J2 J3停止
        }
        if( sync_switch_cnt == 100 )    //停止1s 100-1
        {
            PWMB_ENO |= 0x04;           //J2运行    
        }   
        if( sync_switch_cnt == 400 )    //J2运行3s 400-100
        {
            PWMB_ENO &= 0xfb;           //J2 J3停止
        }
        if( sync_switch_cnt == 500 )    //停止1s  500-400
        {
            PWMB_ENO |= 0x10;           //J3运行    
            slave_06.hf_reset_flag = 0;
            sync_switch_cnt = 0;
        }
        if( slave_06.SF_Switch == 1 )
        {
            PWMB_ENO |= 0X01;
        }
    }

    if( slave_06.sync_switch_delay == 1 )
    {
        sync_delay_cnt++;
        if( sync_delay_cnt == 100 )
        {
            slave_06.sync_switch_delay = 0;
            sync_delay_cnt = 0;
        }
    }
}
