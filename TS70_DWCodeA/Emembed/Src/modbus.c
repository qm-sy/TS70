#include "modbus.h"

MODBIS5_INFO modbus5;

void Modbus_Event_Uart2( void )
{
    uint16_t crc,rccrc = 0;

    /*1.接收完毕                                           */
    if( rs485_2.RX2_rev_end_Flag == 1 )
    {
        /*2.清空接收完毕标志位                              */    
        rs485_2.RX2_rev_end_Flag = 0;

        /*3.CRC校验                                         */
        crc = MODBUS_CRC16(rs485_2.RX2_buf, rs485_2.RX2_rev_cnt-2);
        rccrc = (rs485_2.RX2_buf[rs485_2.RX2_rev_cnt-1]) | (rs485_2.RX2_buf[rs485_2.RX2_rev_cnt-2]<<8);

        /*4.清空接收计数                                    */
        rs485_2.RX2_rev_cnt = 0; 

        /*5.CRC校验通过，进行地址域校验                      */
        if( crc == rccrc )
        {  
            /*6.地址域校验通过，进入相应功能函数进行处理      */
            if( rs485_2.RX2_buf[0] == 0x01 )    
            {
                switch ( rs485_2.RX2_buf[1] )
                {
                    case 0x06:
                        printf("uart2 is ok \r\n");
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
    if( rs485_4.RX4_rev_end_Flag == 1 )
    {
        /*2.清空接收完毕标志位                              */    
        rs485_4.RX4_rev_end_Flag = 0;

        /*3.CRC校验                                         */
        crc = MODBUS_CRC16(rs485_4.RX4_buf, rs485_4.RX4_rev_cnt-2);
        rccrc = (rs485_4.RX4_buf[rs485_4.RX4_rev_cnt-1]) | (rs485_4.RX4_buf[rs485_4.RX4_rev_cnt-2]<<8);

        /*4.清空接收计数                                    */
        rs485_4.RX4_rev_cnt = 0; 

        /*5.CRC校验通过，进行地址域校验                      */
        if( crc == rccrc )
        {
            /*6.地址域校验通过，进入相应功能函数进行处理      */
            if( rs485_4.RX4_buf[0] == 0x01 )
            {
                switch ( rs485_4.RX4_buf[1] )
                {
                    case 0x06:

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
        /*2.清空接收完毕标志位                              */    
        rs485_5.RX_rcv_end_Flag = 0;

        /*3.CRC校验                                         */
        crc = MODBUS_CRC16(rs485_5.RX_buf, rs485_5.RX_rcv_cnt-2);
        rccrc = (rs485_5.RX_buf[rs485_5.RX_rcv_cnt - 2]) | (rs485_5.RX_buf[rs485_5.RX_rcv_cnt - 1] << 8);

        /*4.清空接收计数                                    */
        rs485_5.RX_rcv_cnt = 0; 

        /*5.CRC校验通过，进行地址域校验                      */
        if( crc == rccrc )
        {
            /*6.地址域校验通过，进入相应功能函数进行处理      */
            if( rs485_5.RX_buf[0] == 0x01 )
            {
                switch ( rs485_5.RX_buf[1] )
                {    
                    case FUN_03:        Modbus_Fun03();         break; 

                    case FUN_06:        Modbus_Fun06();         break; 
                        
                    case FUN_16:        Modbus_Fun16();         break;  

                    default:                                    break;
                }
            }
        }
    }
}

void Modbus_Fun03( void )
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
                modbus5.byte_info_H  = (uint8_t)hansen.addr_0x00 >> 8;
                modbus5.byte_info_L  = (uint8_t)hansen.addr_0x00 & 0xFF; 

                break;
            /*  y白边              */
            case 0x02:  
                modbus5.byte_info_H  = (uint8_t)hansen.addr_0x02 >> 8;
                modbus5.byte_info_L  = (uint8_t)hansen.addr_0x02 & 0xFF; 

                break;

            /*  获取当前主板语言              */
            case 0x06:  
                modbus5.byte_info_H  = (uint8_t)(hansen.addr_0x06 >> 8);
                modbus5.byte_info_L  = (uint8_t)(hansen.addr_0x06 & 0xFF); 

                break;

            /*  获取当前主板语言              */
            case 0x10:  
                modbus5.byte_info_H  = 0x00;
                modbus5.byte_info_L  = 0x20; 

                break;

            /*  马达操作                      */
            case 0x20:
                modbus5.byte_info_H  = (uint8_t)hansen.addr_0x20 >> 8;
                modbus5.byte_info_L  = (uint8_t)hansen.addr_0x20 & 0xFF; 

                break;

            /*  喷头操作                       */    
            case 0x21:
                modbus5.byte_info_H  = (uint8_t)hansen.addr_0x21 >> 8;
                modbus5.byte_info_L  = (uint8_t)hansen.addr_0x21 & 0xFF;

                break;

            /*  喷头强度                  */
            case 0x22:    
                modbus5.byte_info_H  = (uint8_t)hansen.addr_0x22 >> 8;
                modbus5.byte_info_L  = (uint8_t)hansen.addr_0x22 & 0xFF; 

                break;

            /*  喷头数量                 */
            case 0x23:   
                modbus5.byte_info_H  = (uint8_t)hansen.addr_0x23 >> 8;
                modbus5.byte_info_L  = (uint8_t)hansen.addr_0x23 & 0xFF; 

                break;

            /*  信号                 */
            case 0x2d:    
                modbus5.byte_info_H  = (uint8_t)hansen.addr_0x2d >> 8;
                modbus5.byte_info_L  = (uint8_t)hansen.addr_0x2d & 0xFF; 

                break;

            /*  校准图类型                 */
            case 0x30:   
                modbus5.byte_info_H  = (uint8_t)hansen.addr_0x30 >> 8;
                modbus5.byte_info_L  = (uint8_t)hansen.addr_0x30 & 0xFF; 

                break; 

            default:
                break;
        }
        rs485_5.TX_buf[modbus5.send_val_addr++] = modbus5.byte_info_H;
        rs485_5.TX_buf[modbus5.send_val_addr++] = modbus5.byte_info_L;
    }
    slave_to_master(0x03,3 + modbus5.byte_cnt);
}

void Modbus_Fun06( void )
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

    slave_to_master(0x06,8);

}

/**
 * @brief	写多个输出寄存器  16
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun16( void )
{
    uint16_t i;

    modbus5.rcv_value_addr = 7;                  //DATA1 H位置
    modbus5.byte_cnt   = rs485_5.RX_buf[6];
    modbus5.start_addr = rs485_5.RX_buf[2]<<8 | rs485_5.RX_buf[3];

    for( i = modbus5.start_addr; i < modbus5.start_addr + modbus5.byte_cnt/2; i++)
    {
        modbus5.byte_info_H = rs485_5.RX_buf[modbus5.rcv_value_addr];
        modbus5.byte_info_L = rs485_5.RX_buf[modbus5.rcv_value_addr + 1];
        switch (i)
        {
            /*  40001  24V LED开关状态设置                  */
            case 0:


                break;
            
            /*  40002  两路PWM 开关状态及风速设置           */
            case 1:


                break;

            /*  40003  220V 开关设置                        */
            case 2:

                break;

            /*  40004  烘干功率及风扇档位 设置              */
            case 3:


                break;

            /*  40005  NTC1 NTC2 alarm value 设置           */
            case 4:


                break;
            
            /*  40006  NTC3 alarm value 设置                */
            case 5:


                break;

            /*  40007  同步开关设置                         */
            case 6:


                break;

            default:
                break;
        }
        modbus5.rcv_value_addr += 2;         //从Value1_H →→ 从Value2_H
    }
    
    slave_to_master(0x10,8);  

}

/**
 * @brief	写单个输出寄存器-06
 *
 * @param   reg_addr：要写的寄存器地址
 *          reg_val： 要写的值
 *
 * @return  void
 */
void write_slave_06( uint8_t uart_num, uint16_t reg_addr, uint8_t reg_val_H, uint8_t reg_val_L)
{
    uint8_t send_buf[8];
    uint16_t crc;

    delay_ms(10);
    download_flag = 0;

    send_buf[0] = SLAVE_ADDR;       //Addr
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

    memcpy(rs485_5.TX_buf,send_buf,8);
    /*   发送，后使能接收    */
    rs485_5.TX_send_bytelength = 8;

    TR5 = 1;

    delay_ms(2);
    SCON3T |= S5TI;                             //开始发送
    delay_ms(1);
}


/**
 * @brief	从机回复主机
 *  
 * @param   code_num:功能码       
 * @param   length:数据长度        
 * 
  @return  crc16:crc校验的值 2byte
 */
void slave_to_master(uint8_t code_num,uint8_t length)
{
    uint16_t crc;

    switch (code_num)
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
            // memcpy(rs485_5.TX_buf,rs485_5.RX_buf,8);
            rs485_5.TX_buf[0] = 1;
            rs485_5.TX_buf[1] = 1;
            rs485_5.TX_buf[2] = 1;
            rs485_5.TX_buf[3] = 1;
            rs485_5.TX_buf[4] = 1;
            rs485_5.TX_buf[5] = 1;
            rs485_5.TX_buf[6] = 1;
            rs485_5.TX_buf[7] = 1;
            rs485_5.TX_send_bytelength = length;
            
            break;    

        case 0x10:
            memcpy(rs485_5.TX_buf,rs485_5.RX_buf,6);
        
            crc = MODBUS_CRC16(rs485_5.TX_buf,6);

            rs485_5.TX_buf[7] = crc;                 //CRC H
            rs485_5.TX_buf[6] = crc>>8;              //CRC L
        
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
uint16_t MODBUS_CRC16(uint8_t *buf, uint8_t length)
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