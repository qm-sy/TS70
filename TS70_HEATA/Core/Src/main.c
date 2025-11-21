#include "main.h"

void main( void )
{
    P_SW2 |= 0x80;
    
    GPIO_Init();
    Power_Init();

    /*  调试使用 printf  */
    Uart1_Init();

    /*  485控制  */
    Uart4_Init();               //串口4用作485
    Uart4_Send_Statu_Init();    //接收发送初始化
    Timer0_Init();              //不定长数据接收

    /*  PWM控制  */
    PWM_Init();

    /*  3路220输出控制  */
    Timer1_Init();
    Temp_Init();
    
    /*  定时事件  */
    Timer3_Init();

    EA = 1;     //中断总开关

    eeprom_statu_judge();       //EEPROM初始化

    printf("========== code start ========== \r\n");
    printf("========== TS70_HEATA 2025.11.21 ========== \r\n");

    while (1)
    {
        Modbus_Event();
        ac_dc_ctrl();
        temp_scan();
    }  
}