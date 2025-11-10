#include "main.h"

void main()
{
	sys_init();
	GPIO_Init();
	burn_params_init();

	Uart2_Init(115200);
	Uart2_Send_Statu_Init();

	Uart4_Init(115200);
	Uart4_Send_Statu_Init();

	Uart5_Init(115200);
	Uart5_Send_Statu_Init();

	Tim0_Init();
	Tim1_Init();
	
	gui_scan_flag = 0;
	sp350.params_get_flag1 = 1;
	sp350.params_get_flag2 = 1;
	mc01.params_get_flag1 = 1;
	mc01.params_get_flag2 = 1;
	mc01.temp_scan_flag = 0;
    rs485_2.comm_error_flag = 0;
	rs485_2.comm_error_flag2 = 0;
	rs485_2.fun06_rcv_out = 1;
	rs485_2.fun04_rcv_out = 1;
	rs485_2.press_flag1 = 0;
	rs485_2.press_flag2 = 0;
	rs485_4.fun06_rcv_out = 0;
	rs485_4.comm_error_flag = 0;
	delay_ms(200);

	diwen_parms_init();

	EA    = 1;              //总中断开关
	
	// printf(" ===== code start ====== \r\n");
	
	while(1)
	{
		uart_frame_deal();			//串口程序下载
		Modbus_Event_DFG();
		Modbus_Event_350P();
		Modbus_Event_HanSen();

		if( gui_scan_flag == 1 )		//50ms检测一次屏幕是否被按下
		{
			Sw_Data_Send();
			gui_scan_flag = 0;
		}
		
		if( hansen.paoji_send == 1 )
		{
			Write_Dgus(0x20a4,hansen.paoji_s);
			Write_Dgus(0x20a3,hansen.paoji_min);
			Write_Dgus(0x20a2,hansen.paoji_h);
			hansen.paoji_send = 0;
		}
		if( sp350.params_get_flag2 == 1 )
		{
			read_slave_03_350P();
			sp350.params_get_flag2 = 0;
		}
		if( mc01.params_get_flag2 == 1 )
		{
			read_slave_03_DFG();
			mc01.params_get_flag2 = 0;
		}
		if(( mc01.params_get_flag1 == 0 ) && ( mc01.temp_scan_flag == 1 ))
		{
			if(( rs485_2.fun06_rcv_out == 1 ) && (rs485_2.fun06_rcv_out == 1))
			{
				if( rs485_2.press_flag1 == 0 )
				{
					read_slave_04_DFG();
				}
			}

			mc01.temp_scan_flag = 0;
		}
		if( rs485_2.comm_error_flag == 1 )
		{
			mc01.params_get_flag1 = 1;
			mc01.params_get_flag2 = 1;
			rs485_2.comm_error_flag = 0;
			rs485_2.comm_error_flag2 = 1;
			Write_Dgusii_Vp_byChar(0x211b,"通讯失败",8);
		}
		if(( rs485_4.comm_error_flag == 1 ) && ( sp350.params_get_flag1 == 0))
		{
			sp350.params_get_flag1 = 1;
			sp350.params_get_flag2 = 1;
			rs485_4.comm_error_flag = 0;
			Write_Dgusii_Vp_byChar(0x212a,"通讯失败",8);
		}
	}
}