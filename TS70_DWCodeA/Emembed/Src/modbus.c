#include "modbus.h"

MODBIS5_INFO modbus5;
MODBIS4_INFO modbus4;

uint8_t fuyin_flag = 0;

void Modbus_Event_Uart2( void )
{
    uint16_t crc,rccrc = 0;

    /*1.接收完毕                                           */
    if( rs485_2.rcv_end_flag == 1 )
    {
        /*2.清空接收完毕标志位                              */    
        rs485_2.rcv_end_flag = 0;

        /*3.CRC校验                                         */
        crc = MODBUS_CRC16(rs485_2.rcv_buf, rs485_2.rcv_cnt-2);
        rccrc = (rs485_2.rcv_buf[rs485_2.rcv_cnt-1]) | (rs485_2.rcv_buf[rs485_2.rcv_cnt-2]<<8);

        /*4.清空接收计数                                    */
        rs485_2.rcv_cnt = 0; 

        /*5.CRC校验通过，进行地址域校验                      */
        if( crc == rccrc )
        {  
            /*6.地址域校验通过，进入相应功能函数进行处理      */
            if( rs485_2.rcv_buf[0] == DFJ_ADDR )    
            {
                switch ( rs485_2.rcv_buf[1] )
                {
                    case 0x03:
                        Modbus_Fun03_DFG();
                        break;  

                    case 0x04:
                        Modbus_Fun04_DFG();
                        break;  

                    default:
                        break;
                }
            }
        }
    }
}

void Modbus_Event_Uart4( void )
{
    uint16_t crc,rccrc = 0;

    /*1.接收完毕                                           */
    if( rs485_4.RX_rcv_end_Flag == 1 )
    {
        /*2.清空接收完毕标志位                              */    
        rs485_4.RX_rcv_end_Flag = 0;

        /*3.CRC校验                                         */
        crc = MODBUS_CRC16(rs485_4.RX_buf, rs485_4.RX_rcv_cnt-2);
        rccrc = (rs485_4.RX_buf[rs485_4.RX_rcv_cnt-1]) | (rs485_4.RX_buf[rs485_4.RX_rcv_cnt-2]<<8);

        /*4.清空接收计数                                    */
        rs485_4.RX_rcv_cnt = 0; 

        /*5.CRC校验通过，进行地址域校验                      */
        if( crc == rccrc )
        {
            /*6.地址域校验通过，进入相应功能函数进行处理      */
            if( rs485_4.RX_buf[0] == SP350P_ADDR )
            {
                switch ( rs485_4.RX_buf[1] )
                {
                    case FUN_03:        Modbus_Fun03_slave2();         break; 

                        break;  

                    default:
                        break;
                }
            }
        }
    }
}

void Modbus_Event_Uart5( void )
{
    uint16_t crc,rccrc = 0;

    /*1.接收完毕                                           */
    if( rs485_5.RX_rcv_end_Flag == 1 )
    {
        /*2.CRC校验                                         */
        crc = MODBUS_CRC16(rs485_5.RX_buf, rs485_5.RX_rcv_cnt-2);
        rccrc = (rs485_5.RX_buf[rs485_5.RX_rcv_cnt - 2]) | (rs485_5.RX_buf[rs485_5.RX_rcv_cnt - 1] << 8);

        /*3.CRC校验通过，进行地址域校验                      */
        if( crc == rccrc )
        {
            /*4.地址域校验通过，进入相应功能函数进行处理      */
            if( rs485_5.RX_buf[0] == HANSEN_ADDR )
            {
                switch ( rs485_5.RX_buf[1] )
                {    
                    case FUN_03:        Modbus_Fun03_slave1();         break; 

                    case FUN_06:        Modbus_Fun06_slave1();         break; 
                        
                    case FUN_16:        Modbus_Fun16_slave1();         break;  

                    default:                                    break;
                }
            }
        }
        /*5.清空接收计数                                    */
        rs485_5.RX_rcv_cnt = 0; 
        /*6.清空接收完毕标志位                              */    
        rs485_5.RX_rcv_end_Flag = 0;
    }
}

void Modbus_Fun03_DFG( void )
{
    uint16_t i = 0;

    uint8_t start_addr_03 = 3;              //Slave reply  DATA1_H address

    for( i = 0; i < 13; i++)
    {
        switch (i)
        {            
            /*  40001   后烘干开关                   */
            case 0x00:
                mc01.PostDry_switch    = rs485_2.rcv_buf[start_addr_03 + 1];   

                break;

            /*  40002   后烘干加热温度                   */
            case 0x01:
                mc01.PostDry_temp = rs485_2.rcv_buf[start_addr_03 + 1];   

                break; 

            /*  40003   撒粉开关及方向                   */
            case 0x02:
                mc01.SF_direction = rs485_2.rcv_buf[start_addr_03];   
                mc01.SF_switch    = rs485_2.rcv_buf[start_addr_03 + 1];   

                break;

            /*  40004   撒粉功率                   */
            case 0x03:
                mc01.SF_level = rs485_2.rcv_buf[start_addr_03 + 1];   

                break; 

            /*  40005   抖粉开关及方向                */
            case 0x04:
                mc01.DF_direction = rs485_2.rcv_buf[start_addr_03];   
                mc01.DF_switch    = rs485_2.rcv_buf[start_addr_03 + 1];   

                break;

            /*  40006   抖粉功率              */
            case 0x05:
                mc01.DF_level = rs485_2.rcv_buf[start_addr_03 + 1];   

                break;   

            /*  40007   吸风开关              */
            case 0x06:
                mc01.IW2_switch = rs485_2.rcv_buf[start_addr_03];  
                mc01.IW1_switch = rs485_2.rcv_buf[start_addr_03 + 1];   

                break;   

            /*  40008   冷风开关              */
            case 0x07:
                mc01.CW_switch = rs485_2.rcv_buf[start_addr_03 + 1];   

                break; 

            /*  40009   收料开关              */
            case 0x08:
                mc01.MR_switch = rs485_2.rcv_buf[start_addr_03 + 1];   

                break; 

            /*  40010   保温开关               */
            case 0x09:
                mc01.Insulation_switch = rs485_2.rcv_buf[start_addr_03 + 1];   

                break; 

            /*  40011   保温温度              */
            case 0x0a:
                mc01.Insulation_temp = rs485_2.rcv_buf[start_addr_03 + 1];   

                break; 

            /*  40012   同步开关              */
            case 0x0b:
                mc01.sync_switch = rs485_2.rcv_buf[start_addr_03 + 1];   

                break; 

            /*  40013   总开关               */
            case 0x0c:
                mc01.power_switch = rs485_2.rcv_buf[start_addr_03 + 1];   

                break; 

            default:
                break;
        }
        start_addr_03 += 2;
    }

    if( mc01.params_get_flag1 == 1 )
    {
        mc01.params_get_flag1 = 0;
        mc01_parms_init();
    }
    
}

void Modbus_Fun04_DFG( void )
{
    uint16_t i = 0;

    uint8_t start_addr_04 = 3;              //Slave reply  DATA1_H address

    for( i = 0; i < 1; i++)
    {
        switch (i)
        {
            /*  40001   撒粉开关及方向                   */
            case 0x00:  
                mc01.th_temp    = ((rs485_2.rcv_buf[start_addr_04] << 8) | (rs485_2.rcv_buf[start_addr_04 + 1]));   
                Write_Dgus(0X2104,mc01.th_temp);
                break;

            default:
                break;
        }
        start_addr_04 += 2;
    }
}

void Modbus_Fun03_slave1( void )
{
    uint16_t i;

    modbus5.send_val_addr  = 3;                //DATA1 H 位置
    modbus5.byte_cnt   = (rs485_5.RX_buf[4]<<8 | rs485_5.RX_buf[5]) *2;
    modbus5.start_addr = rs485_5.RX_buf[2]<<8 | rs485_5.RX_buf[3];

    rs485_5.TX_buf[0]  = HANSEN_ADDR;                //Addr
    rs485_5.TX_buf[1]  = FUN_03;                   //Fun
    rs485_5.TX_buf[2]  = modbus5.byte_cnt;       //Byte Count

    for( i = modbus5.start_addr; i < modbus5.start_addr + modbus5.byte_cnt/2; i++ )
    {
        /*    每次循环前初始化byte_info                       */
        modbus5.byte_info_H = modbus5.byte_info_L = 0X00;
        switch (i)
        {   
            /*  x白边              */
            case 0x00:  
                modbus5.byte_info_H  = (uint8_t)(hansen.addr_0x00 >> 8);
                modbus5.byte_info_L  = (uint8_t)(hansen.addr_0x00 & 0xFF);

                break;
            /*  y白边              */
            case 0x02:  
                modbus5.byte_info_H  = (uint8_t)(hansen.addr_0x02 >> 8);
                modbus5.byte_info_L  = (uint8_t)(hansen.addr_0x02 & 0xFF);

                break;

            /*  获取当前主板语言              */
            case 0x06:  
                modbus5.byte_info_H  = (uint8_t)(hansen.addr_0x06 >> 8);
                modbus5.byte_info_L  = (uint8_t)(hansen.addr_0x06 & 0xFF); 

                break;

            /*  获取当前主板语言              */
            case 0x10:  
                modbus5.byte_info_H  = 0x00;
                modbus5.byte_info_L  = (uint8_t)(hansen.addr_0x10 & 0xFF); 

                break;

            /*  获取当前主板语言              */
            case 0x0c:  
                modbus5.byte_info_H  = 0x00;
                modbus5.byte_info_L  = (uint8_t)(hansen.addr_0x0c & 0xFF); 

                break;

            /*  马达操作                      */
            case 0x20:
                modbus5.byte_info_H  = (uint8_t)(hansen.addr_0x20 >> 8);
                modbus5.byte_info_L  = (uint8_t)(hansen.addr_0x20 & 0xFF);

                break;

            /*  喷头操作                       */    
            case 0x21:
                modbus5.byte_info_H  = (uint8_t)(hansen.addr_0x21 >> 8);
                modbus5.byte_info_L  = (uint8_t)(hansen.addr_0x21 & 0xFF);

                break;

            /*  喷头强度                  */
            case 0x22:    
                modbus5.byte_info_H  = (uint8_t)(hansen.addr_0x22 >> 8);
                modbus5.byte_info_L  = (uint8_t)(hansen.addr_0x22 & 0xFF); 

                break;

            /*  喷头数量                 */
            case 0x23:   
                modbus5.byte_info_H  = (uint8_t)(hansen.addr_0x23 >> 8);
                modbus5.byte_info_L  = (uint8_t)(hansen.addr_0x23 & 0xFF); 

                break;

            /*  信号                 */
            case 0x2d:    
                modbus5.byte_info_H  = (uint8_t)(hansen.addr_0x2d >> 8);
                modbus5.byte_info_L  = (uint8_t)(hansen.addr_0x2d & 0xFF); 

                break;

            /*  校准图类型                 */
            case 0x30:   
                modbus5.byte_info_H  = (uint8_t)(hansen.addr_0x30 >> 8);
                modbus5.byte_info_L  = (uint8_t)(hansen.addr_0x30 & 0xFF); 

                break; 

            default:
                break;
        }
        rs485_5.TX_buf[modbus5.send_val_addr++] = modbus5.byte_info_H;
        rs485_5.TX_buf[modbus5.send_val_addr++] = modbus5.byte_info_L;
    }
    slave1_to_master(0x03,3 + modbus5.byte_cnt);
    if( hansen.connect_flag == 0 )
    {
        hansen.connect_flag = 1;
        Write_Dgus(0x2025,1);
    }
    
}

void Modbus_Fun06_slave1( void )
{
    switch(rs485_5.RX_buf[3])
    {
        /*  马达操作                      */
        case 0x20:                         
            hansen.addr_0x20 = (rs485_5.RX_buf[4] << 8) | rs485_5.RX_buf[5]; 

            break;  

        /*  喷头操作                       */    
        case 0x21:
            hansen.addr_0x21 = (rs485_5.RX_buf[4] << 8) | rs485_5.RX_buf[5]; 

            break;

        /*  喷头强度                  */
        case 0x22:    
            hansen.addr_0x22 = (rs485_5.RX_buf[4] << 8) | rs485_5.RX_buf[5]; 

            break;

        /*  喷头数量                 */
        case 0x23:   
            hansen.addr_0x23 = (rs485_5.RX_buf[4] << 8) | rs485_5.RX_buf[5]; 

            break;

        /*  信号                 */
        case 0x2d:    
            hansen.addr_0x2d = (rs485_5.RX_buf[4] << 8) | rs485_5.RX_buf[5]; 

            break;

        /*  校准图类型                 */
        case 0x30:   
            hansen.addr_0x30 = (rs485_5.RX_buf[4] << 8) | rs485_5.RX_buf[5]; 

            break;

        // /*                    */
        // case 0x100:   
        //     //hansen.addr_0x2 = (rs485_5.RX_buf[4] << 8) | rs485_5.RX_buf[5]; 

        //     break;

        // /*                    */
        // case 0x101:    
        //     //hansen.addr_0x24 = (rs485_5.RX_buf[4] << 8) | rs485_5.RX_buf[5]; 

        //     break;
 
        // /*                    */
        // case 0x102:   
        //     //hansen.addr_0x25 = (rs485_5.RX_buf[4] << 8) | rs485_5.RX_buf[5]; 

        //     break;

        default:
            break;   
    }

    slave1_to_master(FUN_06,8);

}

/**
 * @brief	写多个输出寄存器  16
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun16_slave1( void )
{
    uint16_t i;
    static uint8_t chip_id[32] = {0};
    static uint8_t FW_set[32] = {0};
    static uint8_t FW_params[32] = {0};
    static uint8_t HS_version[30] = {0};
    static uint8_t renwu_name[32] = {0};
    static uint8_t dayin_mode[20] = {0};

    modbus5.rcv_value_addr = 7;                  //DATA1 H位置
    modbus5.byte_cnt   = rs485_5.RX_buf[6];
    modbus5.start_addr = rs485_5.RX_buf[2]<<8 | rs485_5.RX_buf[3];

    for( i = modbus5.start_addr; i < modbus5.start_addr + modbus5.byte_cnt/2; i++)
    {
        modbus5.byte_info_H = rs485_5.RX_buf[modbus5.rcv_value_addr];
        modbus5.byte_info_L = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
        switch (i)
        {
            
            /*  0x0100  系统动作    */
            case 0x0100:
                hansen.addr_0x0100 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];

                switch(hansen.addr_0x0100)
                {
                    
                    case 0:         hansen.addr_0x20 = 0;   fuyin_flag = 0;                               break;      //清除跑机使能    
                    case 2:         hansen.addr_0x20 = 0;   Write_Dgus(0x2020,0);                         break;      //清除马达操作使能 
                    case 3:         hansen.addr_0x30 = 0;                                                 break;      //清除检测使能       
                    case 6:         hansen.addr_0x21 = 0;   hansen.addr_0x22 = 0;   hansen.addr_0x23 = 0; break;      //清除清洗、装墨使能         
                    case 10:        hansen.addr_0x21 = 0;   hansen.addr_0x23 = 0;                         break;      //开始装墨
                    case 12:        hansen.addr_0x20 = 0;                                                 break;      //开始装墨
                    default:                                                                              break;      //清除跑机使能      
                }

                break;

            /*  0x0102  打印状态    */
            case 0x0102:
                hansen.addr_0x0102 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];

                switch(hansen.addr_0x0102)
                { 
                    case 0:         Write_Dgusii_Vp_byChar(0x1600,"  空闲  ",8); 
                                    hansen.addr_0x2d = 0;
                                    if( hansen.ctrl_flag == 0 )
                                    {
                                        hansen.ctrl_flag = 1;
                                        jump_page(0);
                                    }     
                                    break;
                    case 1:         if( hansen.ctrl_flag == 0 )
                                    {
                                        Write_Dgusii_Vp_byChar(0x1600," 初始化 ",8);
                                    }
                                    break;     
                    case 2:         Write_Dgusii_Vp_byChar(0x1600,"  打印  ",8);       
                                    if( fuyin_flag == 0 )
                                    { 
                                        jump_page(11); 
                                    } 
                                    break;
                    case 3:         Write_Dgusii_Vp_byChar(0x1600,"  恢复  ",8);        break;     
                    case 4:         Write_Dgusii_Vp_byChar(0x1600,"  暂停  ",8);        break;
                    case 6:         Write_Dgusii_Vp_byChar(0x1600,"  保湿  ",8);        break;    
                    case 7:         Write_Dgusii_Vp_byChar(0x1600,"其他动作",8);        break;
                    default:                                                            break;
                }

                break;

            /*  0x0110  总打印份数    */
            case 0x0110:
                hansen.addr_0x0110 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1]; 
                Write_Dgus(0x20ce,hansen.addr_0x0110);   
                break;

            /*  0x0111  当前打印份数/打印幅数    */    
            case 0x0111:
                hansen.addr_0x0111 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1]; 
                Write_Dgus(0x20cd,hansen.addr_0x0111); 
                break;

            /*  0x0112  打印精度(XDPI)    */
            case 0x0112:
                hansen.addr_0x0112 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1]; 
                Write_Dgus(0x20c0,hansen.addr_0x0112); 
                break;   

            /*  0x0114  打印精度(YDPI)    */    
            case 0x0114:
                hansen.addr_0x0114 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1]; 
                Write_Dgus(0x20c2,hansen.addr_0x0114); 
                break; 

            /*  0x011A  图像宽度（mm）    */  
            case 0x011a:
                hansen.addr_0x011a = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1]; 
                Write_Dgus(0x20c4,hansen.addr_0x011a); 
                break;

            /*  0x011C  图像高度（mm）    */   
            case 0x011c:
                hansen.addr_0x011c = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1]; 
                Write_Dgus(0x20c6,hansen.addr_0x011c); 
                break;

            /*  0x0120~124  打印模式    */     
            case 0x0120:
                dayin_mode[0] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                dayin_mode[1] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0121:
                dayin_mode[2] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                dayin_mode[3] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0122:
                dayin_mode[4] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                dayin_mode[5] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0123:
                dayin_mode[6] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                dayin_mode[7] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0124:
                dayin_mode[8] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                dayin_mode[9] = rs485_5.RX_buf[modbus5.rcv_value_addr]; 
                Write_Dgusii_Vp_byChar(0x20b0,dayin_mode,10);           
                break;

            /*  0x0134  打印计时-秒    */   
            case 0x0134:
                hansen.addr_0x0134 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                time_trans(hansen.addr_0x0134,0);

                Write_Dgus(0x20d0,dayin_t.cnt_h); 
                Write_Dgus(0x20d1,dayin_t.cnt_min); 
                Write_Dgus(0x20d2,dayin_t.cnt_s); 
                break;
            
            /*  0x0136  剩余时间-秒    */    
            case 0x0136:
                hansen.addr_0x0136 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                time_trans(hansen.addr_0x0136,1);

                Write_Dgus(0x20d3,dayin_t.remain_h); 
                Write_Dgus(0x20d4,dayin_t.remain_min); 
                Write_Dgus(0x20d5,dayin_t.remain_s); 
                break;

            /*  0x0138  打印产能(面积)    */        
            case 0x0138:
                hansen.addr_0x0138 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];

                Write_Dgus(0x20cc,hansen.addr_0x0138); 
                break;

            /*  0x013A  打印产能(长度)    */ 
            case 0x013a:
                hansen.addr_0x013a = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];

                Write_Dgus(0x20c9,hansen.addr_0x013a); 
                break;

            /*  0x013C  打印产能(长度)    */ 
            case 0x013c:
                hansen.addr_0x013c = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                if( hansen.addr_0x013c == 100 )
                {
                    jump_page(0); 
                }
                Write_Dgus(0x20d9,hansen.addr_0x013c); 
                break;

            /*  0x0140~149  PRN任务名称    */    
            case 0x0140:
                renwu_name[0] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                renwu_name[1] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0141:
                renwu_name[2] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                renwu_name[3] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0142:
                renwu_name[4] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                renwu_name[5] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0143:
                renwu_name[6] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                renwu_name[7] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0144:
                renwu_name[8] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                renwu_name[9] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0145:
                renwu_name[10] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                renwu_name[11] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0146:
                renwu_name[12] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                renwu_name[13] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0147:
                renwu_name[14] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                renwu_name[15] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0148:
                renwu_name[16] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                renwu_name[17] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0149:
                renwu_name[18] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                renwu_name[19] = rs485_5.RX_buf[modbus5.rcv_value_addr];     
                //Write_Dgusii_Vp_byChar(0x20f0,renwu_name,20);   
                break;
            
            /*  0x0150~151  X马达位置    */ 
            case 0x0150:
                hansen.addr_0x0150 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                break;
            case 0x0151:
                hansen.addr_0x0151 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                Write_Dgus(0x2070,hansen.addr_0x0151);
                Write_Dgus(0x2071,hansen.addr_0x0150);
                break;

            /*  0x0152~153  Y马达位置    */     
            case 0x0152:
                hansen.addr_0x0152 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                break;
            case 0x0153:
                hansen.addr_0x0153 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                // Write_Dgus(0x2072,hansen.addr_0x0153);
                // Write_Dgus(0x2073,hansen.addr_0x0152);
                break;

            /*  0x0154~155  Z马达位置    */     
            case 0x0154:
                hansen.addr_0x0154 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                break;
            case 0x0155:
                hansen.addr_0x0155 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                // Write_Dgus(0x2074,hansen.addr_0x0155);
                // Write_Dgus(0x2075,hansen.addr_0x0154);
                break;

            /*  0x0156~157  主板IP    */ 
            case 0x0156:
                hansen.addr_0x0156_H = rs485_5.RX_buf[modbus5.rcv_value_addr];
                hansen.addr_0x0156_L = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                break;
            case 0x0157:
                hansen.addr_0x0157_H = rs485_5.RX_buf[modbus5.rcv_value_addr];
                hansen.addr_0x0157_L = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                Write_Dgus(0x2080,hansen.addr_0x0156_L);     
                Write_Dgus(0x2082,hansen.addr_0x0156_H);    
                Write_Dgus(0x2084,hansen.addr_0x0157_L);     
                Write_Dgus(0x2086,hansen.addr_0x0157_H);    
                break;

            /*  0x0158  X白边    */ 
            case 0x0158:
                hansen.addr_0x00 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                Write_Dgus(0x2060,hansen.addr_0x00);     
                break;

            /*  0x015A  Y白边    */ 
            case 0x015a:
                hansen.addr_0x02 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                Write_Dgus(0x2062,hansen.addr_0x02);  
                break;

            /*  0x015E  打印设置    */ 
            case 0x015e:
                hansen.addr_0x06 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                
                hansen.addr_0x06_02 = hansen.addr_0x06 & 0x04;

                hansen.addr_0x06_35 = (hansen.addr_0x06 & 0x38) >> 3;

                hansen.addr_0x06_67 = (hansen.addr_0x06 & 0xc0) >> 6;
                if( hansen.addr_0x06_67 == 3 )
                {
                    hansen.addr_0x06_67 = 4;
                }

                hansen.addr_0x06_8a = (hansen.addr_0x06 & 0x0700) >> 8;

                hansen.addr_0x06_bc = (hansen.addr_0x06 & 0x1800) >> 11;
                hansen.addr_0x06_bc = 0x01 << hansen.addr_0x06_bc;

                Write_Dgus(0x2051,hansen.addr_0x06_02);  
                Write_Dgus(0x2052,hansen.addr_0x06_35);
                Write_Dgus(0x2053,hansen.addr_0x06_67);
                Write_Dgus(0x2054,hansen.addr_0x06_8a);    
                Write_Dgus(0x2055,hansen.addr_0x06_bc);   
                break;

            /*  0x015F  羽化幅度    */     
            case 0x015f:
                hansen.addr_yuhua = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];

                break;

            /*  0x015F  当前实际喷头个数    */     
            case 0x0160:
                hansen.addr_sjpt = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];

                break;

            /*  0x0161  当前清洗类型    */     
            case 0x0161:
                hansen.addr_0x22 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];

                Write_Dgus(0x2022,hansen.addr_0x22);
                hansen.addr_0x22 = 0;    
                break;

            /*  0x0162  当前清洗/装墨喷头个数    */     
            case 0x0162:
                hansen.addr_0x23 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                Write_Dgus(0x2023,hansen.addr_0x23);
                hansen.addr_0x23 = 0;  
                break;

            
            /*  40007  同步开关设置                         */
            case 0x0169:
                hansen.addr_0x0169 = (rs485_5.RX_buf[modbus5.rcv_value_addr] << 8) | rs485_5.RX_buf[modbus5.rcv_value_addr + 1];

                switch(hansen.addr_0x0169)
                {
                    
                    case 0  :         hansen.addr_0x10 |= 0x20;           break;         
                    
                    default:                                            break;
                }

                break;

            case 0x0170:
                HS_version[0] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[1] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0171:
                HS_version[2] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[3] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0172:
                HS_version[4] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[5] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0173:
                HS_version[6] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[7] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0174:
                HS_version[8] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[9] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0175:
                HS_version[10] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[11] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;

            case 0x0176:
                HS_version[12] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[13] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0177:
                HS_version[14] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[15] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0178:
                HS_version[16] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[17] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0179:
                HS_version[18] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[19] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x017a:
                HS_version[20] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[21] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x017b:
                HS_version[22] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[23] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x017c:
                HS_version[24] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[25] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x017d:
                HS_version[26] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[27] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;

            case 0x017e:
                HS_version[28] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                HS_version[29] = rs485_5.RX_buf[modbus5.rcv_value_addr];   
                Write_Dgusii_Vp_byChar(0x1630,HS_version,30);       
                break;

            case 0x0190:
                chip_id[0] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[1] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0191:
                chip_id[2] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[3] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0192:
                chip_id[4] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[5] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0193:
                chip_id[6] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[7] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0194:
                chip_id[8] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[9] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0195:
                chip_id[10] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[11] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;

            case 0x0196:
                chip_id[12] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[13] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0197:
                chip_id[14] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[15] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0198:
                chip_id[16] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[17] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x0199:
                chip_id[18] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[19] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x019a:
                chip_id[20] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[21] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x019b:
                chip_id[22] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[23] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x019c:
                chip_id[24] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[25] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x019d:
                chip_id[26] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[27] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;

            case 0x019e:
                chip_id[28] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[29] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x019f:
                chip_id[30] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                chip_id[31] = rs485_5.RX_buf[modbus5.rcv_value_addr];
                Write_Dgusii_Vp_byChar(0x1650,chip_id,32);   
                break;

            case 0x01c0:
                FW_set[0] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[1] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01C1:
                FW_set[2] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[3] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01C2:
                FW_set[4] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[5] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01C3:
                FW_set[6] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[7] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01C4:
                FW_set[8] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[9] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01C5:
                FW_set[10] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[11] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;

            case 0x01C6:
                FW_set[12] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[13] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01C7:
                FW_set[14] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[15] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01C8:
                FW_set[16] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[17] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01C9:
                FW_set[18] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[19] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01Ca:
                FW_set[20] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[21] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01Cb:
                FW_set[22] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[23] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01Cc:
                FW_set[24] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[25] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01Cd:
                FW_set[26] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[27] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;

            case 0x01Ce:
                FW_set[28] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[29] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01Cf:
                FW_set[30] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_set[31] = rs485_5.RX_buf[modbus5.rcv_value_addr];
                Write_Dgusii_Vp_byChar(0x1670,FW_set,32);   
                break;

            case 0x01D0:
                FW_params[0] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[1] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01D1:
                FW_params[2] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[3] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01D2:
                FW_params[4] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[5] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01D3:
                FW_params[6] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[7] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01D4:
                FW_params[8] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[9] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01D5:
                FW_params[10] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[11] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;

            case 0x01D6:
                FW_params[12] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[13] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01D7:
                FW_params[14] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[15] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01D8:
                FW_params[16] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[17] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01D9:
                FW_params[18] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[19] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01Da:
                FW_params[20] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[21] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01Db:
                FW_params[22] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[23] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01Dc:
                FW_params[24] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[25] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01Dd:
                FW_params[26] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[27] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;

            case 0x01De:
                FW_params[28] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[29] = rs485_5.RX_buf[modbus5.rcv_value_addr];        
                break;
            case 0x01Df:
                FW_params[30] = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
                FW_params[31] = rs485_5.RX_buf[modbus5.rcv_value_addr];
                Write_Dgusii_Vp_byChar(0x1690,FW_params,32);   
                break;    
            default:
                break;
        }
        modbus5.rcv_value_addr += 2;         //从Value1_H →→ 从Value2_H
    }
    
    slave1_to_master(FUN_16,8);  
}


void Modbus_Fun03_slave2( void )
{
    uint16_t i = 0;

    uint8_t start_addr_03 = 3;              //Slave reply  DATA1_H address

    for( i = 0; i < 9; i++)
    {
        switch (i)
        {

            /*  40001 三路220V输出使能设置          */
            case 0x00:
                sp350.F_switch = rs485_4.RX_buf[start_addr_03 + 1];   

                break;

            /*  40002   风速12设置                   */
            case 0x01:
                sp350.M_switch = rs485_4.RX_buf[start_addr_03 + 1];   

                break;

            /*  40003   风速3设置                   */
            case 0x02:
                sp350.R_switch = rs485_4.RX_buf[start_addr_03 + 1];   

                break; 

            /*  40004   同步状态设置                */
            case 0x03:
                sp350.F_alarm_val = rs485_4.RX_buf[start_addr_03 + 1];   

                break;

            /*  40005   预加热开关              */
            case 0x04:
                sp350.M_alarm_val = rs485_4.RX_buf[start_addr_03 + 1];   

                break;   

            /*  40006   预加热温度设置              */
            case 0x05:
                sp350.R_alarm_val = rs485_4.RX_buf[start_addr_03 + 1];   

                break;   

            /*  40007   预加热时间设置              */
            case 0x06:
                sp350.LED_switch = rs485_4.RX_buf[start_addr_03 + 1];   

                break; 

            /*  40008   负载总功率设置              */
            case 0x07:
                sp350.fan_level = rs485_4.RX_buf[start_addr_03 + 1];   

                break; 

            /*  40009   报警温度设置               */
            case 0x08:
                sp350.fan_switch = rs485_4.RX_buf[start_addr_03 + 1];   

                break; 

            default:
                break;
        }
        start_addr_03 += 2;
    }

    if( sp350.params_get_flag1 == 1 )
    {
        sp350.params_get_flag1 = 0;
        sp350_parms_init();
    }
    
}

/**
 * @brief	写单个输出寄存器-06
 *
 * @param   reg_addr：要写的寄存器地址
 *          reg_val： 要写的值
 *
 * @return  void
 */
void write_slave_06(uint16_t reg_addr, uint8_t reg_val_H, uint8_t reg_val_L)
{
    uint8_t send_buf[8];
    uint16_t crc;

    delay_ms(10);

    send_buf[0] = SP350P_ADDR;       //Addr
    send_buf[1] = FUN_06;           //Fun

    /*   Value_H  && Value_L    */
    send_buf[2] = reg_addr >> 8;
    send_buf[3] = reg_addr;
    send_buf[4] = reg_val_H ;
    send_buf[5] = reg_val_L;

    /*   crc    */
    crc = MODBUS_CRC16(send_buf,6);
    send_buf[6] = crc >> 8;
    send_buf[7] = crc;

    memcpy(rs485_4.TX_buf,send_buf,8);
    /*   发送，后使能接收    */
    rs485_4.TX_send_bytelength = 8;

    TR4 = 1;

    delay_ms(2);
    SCON2T |= S4TI;                             //开始发送
    delay_ms(1);
}


/**
 * @brief	写单个输出寄存器-03
 *
 * @param   reg_addr：要写的寄存器地址
 *          reg_val： 要写的值
 *
 * @return  void
 */
void get_slave_03_350p( void )
{
    uint8_t send_buf[8];
    uint16_t crc;

    delay_ms(10);

    send_buf[0] = SP350P_ADDR;       //Addr
    send_buf[1] = FUN_03;           //Fun

    /*   Value_H  && Value_L    */
    send_buf[2] = 0x00;
    send_buf[3] = 0x00;
    send_buf[4] = 0x00 ;
    send_buf[5] = 0x09;

    /*   crc    */
    crc = MODBUS_CRC16(send_buf,6);
    send_buf[6] = crc >> 8;
    send_buf[7] = crc;

    memcpy(rs485_4.TX_buf,send_buf,8);
    /*   发送，后使能接收    */
    rs485_4.TX_send_bytelength = 8;

    TR4 = 1;

    delay_ms(2);
    SCON2T |= S4TI;                             //开始发送
    delay_ms(1);
}

/**
 * @brief	写单个输出寄存器-03
 *
 * @param   reg_addr：要写的寄存器地址
 *          reg_val： 要写的值
 *
 * @return  void
 */
void get_slave_03_MC01( void )
{
    uint8_t send_buf[8];
    uint16_t crc;

    download_flag = 0;
    delay_ms(10);

    send_buf[0] = DFJ_ADDR;       //Addr
    send_buf[1] = FUN_03;           //Fun

    /*   Value_H  && Value_L    */
    send_buf[2] = 0x00;
    send_buf[3] = 0x00;
    send_buf[4] = 0x00 ;
    send_buf[5] = 0x0d;

    /*   crc    */
    crc = MODBUS_CRC16(send_buf,6);
    send_buf[6] = crc >> 8;
    send_buf[7] = crc;

    memcpy(rs485_2.send_buf,send_buf,8);
    /*   发送，后使能接收    */
    rs485_2.send_bytelength = 8;

    DR2_485 = 1;

    delay_ms(2);
    TI0 = 1;                            //开始发送
    delay_ms(1);
}

/**
 * @brief	写单个输出寄存器-03
 *
 * @param   reg_addr：要写的寄存器地址
 *          reg_val： 要写的值
 *
 * @return  void
 */
void get_slave_04_MC01( void )
{
    uint8_t send_buf[8];
    uint16_t crc;

    download_flag = 0;

    send_buf[0] = DFJ_ADDR;     //Addr
    send_buf[1] = FUN_04;       //Fun

    /*   Value_H  && Value_L    */
    send_buf[2] = 0x00;
    send_buf[3] = 0x00;
    send_buf[4] = 0x00 ;
    send_buf[5] = 0x01;

    /*   crc    */
    crc = MODBUS_CRC16(send_buf,6);
    send_buf[6] = crc >> 8;
    send_buf[7] = crc;

    memcpy(rs485_2.send_buf,send_buf,8);
    /*   发送，后使能接收    */
    rs485_2.send_bytelength = 8;

    DR2_485 = 1;

    delay_ms(2);
    TI0 = 1;                            //开始发送
    delay_ms(1);
}


/**
 * @brief	写单个输出寄存器-06
 *
 * @param   reg_addr：要写的寄存器地址
 *          reg_val： 要写的值
 *
 * @return  void
 */
void write_slave_06_MC01(uint16_t reg_addr, uint8_t reg_val_H, uint8_t reg_val_L)
{
    uint8_t send_buf[8];
    uint16_t crc;

    delay_ms(10);
    download_flag = 0;

    send_buf[0] = DFJ_ADDR;       //Addr
    send_buf[1] = FUN_06;           //Fun

    /*   Value_H  && Value_L    */
    send_buf[2] = reg_addr >> 8;
    send_buf[3] = reg_addr;
    send_buf[4] = reg_val_H ;
    send_buf[5] = reg_val_L;

    /*   crc    */
    crc = MODBUS_CRC16(send_buf,6);
    send_buf[6] = crc >> 8;
    send_buf[7] = crc;

    memcpy(rs485_2.send_buf,send_buf,8);
    /*   发送，后使能接收    */
    rs485_2.send_bytelength = 8;

    DR2_485 = 1;
    TI0 = 1;
    delay_ms(2);
}

/**
 * @brief	从机回复主机
 *  
 * @param   code_num:功能码       
 * @param   length:数据长度        
 * 
  @return  crc16:crc校验的值 2byte
 */
void slave1_to_master(uint8_t code_num, uint8_t length)
{
    uint16_t crc;

    switch(code_num)
    {
        case 0x03:
            crc = MODBUS_CRC16(rs485_5.TX_buf,length);

            // rs485_5.TX_buf[length+1] = crc;             //CRC H
            // rs485_5.TX_buf[length] = crc>>8;            //CRC L

            rs485_5.TX_buf[length] = crc;             //CRC H
            rs485_5.TX_buf[length+1] = crc>>8;            //CRC L
            
            rs485_5.TX_send_bytelength = length + 2;
            
            break;

        case 0x04:
            crc = MODBUS_CRC16(rs485_5.TX_buf,length);

            rs485_5.TX_buf[length+1] = crc;              //CRC H
            rs485_5.TX_buf[length] = crc>>8;             //CRC L

            rs485_5.TX_send_bytelength = length + 2;
            
            break;    

        case 0x06:
            memcpy(rs485_5.TX_buf,rs485_5.RX_buf,length);
            rs485_5.TX_send_bytelength = length;

            break;    

        case 0x10:
            memcpy(rs485_5.TX_buf,rs485_5.RX_buf,6);
        
            crc = MODBUS_CRC16(rs485_5.TX_buf,6);

            rs485_5.TX_buf[6] = crc;                 //CRC H
            rs485_5.TX_buf[7] = crc>>8;              //CRC L
        
            rs485_5.TX_send_bytelength = length;
            
            break; 

        default:
            break;
    }

    TR5 = 1;                                //485可以发送
    delay_ms(2);
    SCON3T |= S5TI;                             //开始发送
    delay_ms(1);
}

/**
 * @brief	crc校验函数
 * 
 * @param   buf：  Address(1 byte) +Funtion(1 byte) ）+Data(n byte)   
 * @param   length:数据长度           
 * 
  @return  crc16:crc校验的值 2byte
 */
uint16_t MODBUS_CRC16(uint8_t *buf, uint16_t length)
{
	uint8_t	i;
	uint16_t	crc16;

    /* 1, 预置16位CRC寄存器为0xffff（即全为1）                          */
	crc16 = 0xffff;	

	do
	{
        /* 2, 把8位数据与16位CRC寄存器的低位相异或，把结果放于CRC寄存器     */        
		crc16 ^= (uint16_t)*buf;		//
		for(i=0; i<8; i++)		
		{
            /* 3, 如果最低位为1，把CRC寄存器的内容右移一位(朝低位)，用0填补最高位 再异或0xA001    */
			if(crc16 & 1)
            {
                crc16 = (crc16 >> 1) ^ 0xA001;
            }
            /* 4, 如果最低位为0，把CRC寄存器的内容右移一位(朝低位)，用0填补最高位                */
            else
            {
                crc16 >>= 1;
            }		
		}
		buf++;
	}while(--length != 0);

	return	(crc16);
}