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

    /* 3, temp 上报 1s/次                             */
    if( temp.scan_flag == 0 )
    {
        temp_scan_cnt++;
        if( temp_scan_cnt == 100 )
        {
            temp.scan_flag = 1;
            temp_scan_cnt  = 0;
        }
    }

}

/**
 * @brief	Timer1中断处理函数
 *
 * @param   
 *
 * @return  void
**/
void Tim1_ISR( void ) interrupt 3   //100us
{
    static uint16_t sf_cnt = 0;
    static uint16_t df_cnt = 0;

    sf_cnt++;
    if( sf_cnt == slave_06.sf_level )
    {
        SF_24V = 0;
    }
    if( sf_cnt == 100 )
    {
        SF_24V = 1;
        sf_cnt = 0;
    }

    df_cnt++;
    if( df_cnt == slave_06.df_level )
    {
        DF_24V = 0;
    }
    if( df_cnt == 100 )
    {
        DF_24V = 1;
        df_cnt = 0;
    }
}