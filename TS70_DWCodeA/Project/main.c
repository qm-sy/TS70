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
	delay_ms(200);

	EA    = 1;              //总中断开关
	
	sp350_parms_init();
	diwen_parms_init();
	
	printf(" ===== code start ====== \r\n");
	
	while(1)
	{
		uart_frame_deal();			//串口程序下载
		Modbus_Event_Uart2();
		Modbus_Event_Uart4();
		Modbus_Event_Uart5();
		if( gui_scan_flag == 1 )		//50ms检测一次屏幕是否被按下
		{
			Sw_Data_Send();
			gui_scan_flag = 0;
		}
	}
}