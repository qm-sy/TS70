#include "modbus_rtu.h"

MODBIS_INFO modbus;

/**
 * @brief	modbus_rtu  无奇偶校验
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Event( void )
{
    uint16_t crc,rccrc;
    
    /*1.接收完毕                                           */
    if( rs485_4.rcv_end_flag == 1 )
    {
        /*2.CRC校验                                         */
        crc = MODBUS_CRC16(rs485_4.rcv_buf, rs485_4.rcv_cnt - 2);
        rccrc = (rs485_4.rcv_buf[rs485_4.rcv_cnt - 1]) | (rs485_4.rcv_buf[rs485_4.rcv_cnt - 2] << 8);
        

        /*3.CRC校验通过，进行地址域校验                      */
        if( crc == rccrc )
        {
            /*3-1.地址域校验通过，进入相应功能函数进行处理      */
            if( rs485_4.rcv_buf[0] == MY_ADDR )
            {
                switch (rs485_4.rcv_buf[1])
                {
                    case FUN_03:      Modbus_Fun3();      break;
                    case FUN_04:      Modbus_Fun4();      break;
                    case FUN_06:      Modbus_Fun6();      break;

                    default:                            break;
                }
            }
        }
        /*4.清空接收完毕标志位  清空接收计数        */    
        rs485_4.rcv_end_flag = 0;
        rs485_4.rcv_cnt = 0; 
    }
}

/**
 * @brief	读输入寄存器  03
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun3( void )
{
    uint16_t i;

    modbus.rcv_addr1_valH  = 3;                //DATA1 H 位置
    modbus.start_reg_03    = rs485_4.rcv_buf[2] << 8 | rs485_4.rcv_buf[3];
    modbus.reg_num_03      = rs485_4.rcv_buf[4] << 8 | rs485_4.rcv_buf[5];

    rs485_4.send_buf[0]  = MY_ADDR;                  //Addr
    rs485_4.send_buf[1]  = FUN_03;                   //Fun
    rs485_4.send_buf[2]  = modbus.reg_num_03 * 2;    //Byte Count

    for( i = modbus.start_reg_03; i < modbus.start_reg_03 + modbus.reg_num_03; i++ )
    {
        switch (i)
        {             
            /*  40001 后烘干开关    */
            case 0x00:  
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.PostDry_switch;  
                break;

            /*  40002 后烘干加热温度                      */
            case 0x01:
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.PostDry_temp;; 
                break;

            /*  40003 撒粉开关及方向    */
            case 0x02:  
                modbus.byte_info_H  = slave_06.SF_direction;
                modbus.byte_info_L  = slave_06.SF_switch;  
                break;

            /*  40004 撒粉功率                      */
            case 0x03:
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.SF_level;; 
                break;

            /*  40005 抖粉开关及方向                  */    
            case 0x04:
                modbus.byte_info_H  = slave_06.DF_direction;
                modbus.byte_info_L  = slave_06.DF_switch; 
                break;
 
            /*  40006 抖粉功率                        */
            case 0x05:    
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.DF_level;; 
                break;

            /*  40007 吸风开关                      */
            case 0x06:   
                modbus.byte_info_H  = slave_06.IW2_switch;
                modbus.byte_info_L  = slave_06.IW1_switch; 
                break;
                
            /*  40008 冷风开关                      */
            case 0x07:   
                modbus.byte_info_H  = 0X00;
                modbus.byte_info_L  = slave_06.CW_switch; 
                break;

            /*  40009 收料开关                      */
            case 0x08:   
                modbus.byte_info_H  = 0X00; 
                modbus.byte_info_L  = slave_06.MR_switch; 
                break;

            /*  40010 保温开关                      */
            case 0x09:   
                modbus.byte_info_H  = 0X00;
                modbus.byte_info_L  = slave_06.Insulation_switch; 
                break;

            /*  400011 保温温度                      */
            case 0x0a:   
                modbus.byte_info_H  = 0X00; 
                modbus.byte_info_L  = slave_06.Insulation_temp; 
                break;

            /*  40012 同步开关                      */
            case 0x0b:   
                modbus.byte_info_H  = 0X00; 
                modbus.byte_info_L  = slave_06.sync_switch; 
                break;

            /*  40013 总开关                      */
            case 0x0c:   
                modbus.byte_info_H  = 0X00; 
                modbus.byte_info_L  = slave_06.power_switch; 
                break;

            default:
                modbus.byte_info_H = 0x00;
                modbus.byte_info_L = 0x00;
                break;
        }
        rs485_4.send_buf[modbus.rcv_addr1_valH++] = modbus.byte_info_H;
        rs485_4.send_buf[modbus.rcv_addr1_valH++] = modbus.byte_info_L;
    }
    slave_to_master(FUN_03,3 + modbus.reg_num_03 * 2);
}

/**
 * @brief	读输出寄存器  04
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun4( void )
{
    uint16_t i;

    modbus.rcv_addr1_valH  = 3;                    //DATA1 H 位置
    modbus.start_reg_04 = rs485_4.rcv_buf[2] << 8 | rs485_4.rcv_buf[3];
    modbus.reg_num_04   = rs485_4.rcv_buf[4] << 8 | rs485_4.rcv_buf[5];

    rs485_4.send_buf[0]  = MY_ADDR;                  //Addr
    rs485_4.send_buf[1]  = FUN_04;                   //Fun
    rs485_4.send_buf[2]  = modbus.reg_num_04 * 2;    //Byte Count

    for( i = modbus.start_reg_04; i < modbus.start_reg_04 + modbus.reg_num_04; i++ )
    {
        switch (i)
        {
            /*  30001  热电偶温度                       */
            case 0x00:
                modbus.byte_info_H = temp.th_temp >> 8;
                modbus.byte_info_L = temp.th_temp;
                break;

            default:
                modbus.byte_info_H = 0X00;
                modbus.byte_info_L = 0X00;
                break;
        }
        rs485_4.send_buf[modbus.rcv_addr1_valH++] = modbus.byte_info_H;
        rs485_4.send_buf[modbus.rcv_addr1_valH++] = modbus.byte_info_L;
    }
    slave_to_master(FUN_04,3 + modbus.reg_num_04 * 2);
}

/**
 * @brief	写单个输出寄存器  06
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Fun6( void )
{
    modbus.reg_addr_06 = rs485_4.rcv_buf[2] << 8 | rs485_4.rcv_buf[3];
    modbus.byte_info_H = rs485_4.rcv_buf[4];
    modbus.byte_info_L = rs485_4.rcv_buf[5];

    switch (rs485_4.rcv_buf[3])
    {
        /*  40001   后烘干开关                   */
        case 0x00:
            slave_06.PostDry_switch = modbus.byte_info_L;   

            break;

        /*  40002   后烘干温度                   */
        case 0x01:
            slave_06.PostDry_temp = modbus.byte_info_L;   

            break; 

        /*  40003   撒粉开关及方向                   */
        case 0x02:
            slave_06.SF_direction = modbus.byte_info_H;   
            slave_06.SF_switch    = modbus.byte_info_L;   

            break;

        /*  40004   撒粉功率                   */
        case 0x03:
            slave_06.SF_level = modbus.byte_info_L;   

            break; 

        /*  40005   抖粉开关及方向                */
        case 0x04:
            slave_06.DF_direction = modbus.byte_info_H;   
            slave_06.DF_switch    = modbus.byte_info_L;   

            break;

        /*  40006   抖粉功率              */
        case 0x05:
            slave_06.DF_level = modbus.byte_info_L;   

            break;   

        /*  40007   吸风开关              */
        case 0x06:
            slave_06.IW2_switch = modbus.byte_info_H;  
            slave_06.IW1_switch = modbus.byte_info_L;   
            IW_ctrl();
            break;   

        /*  40008   冷风开关              */
        case 0x07:
            slave_06.CW_switch = modbus.byte_info_L;   
            break; 

        /*  40009   收料开关              */
        case 0x08:
            slave_06.MR_switch = modbus.byte_info_L;   
            break; 

        /*  40010   保温开关               */
        case 0x09:
            slave_06.Insulation_switch = modbus.byte_info_L;   
            break; 

        /*  40011   保温温度              */
        case 0x0a:
            slave_06.Insulation_temp = modbus.byte_info_L;   

            break; 

        /*  40012   同步开关              */
        case 0x0b:
            slave_06.sync_switch = modbus.byte_info_L;   

            break; 

        /*  40013   总开关               */
        case 0x0c:
            slave_06.power_switch = modbus.byte_info_L;   

            break; 

        default:
            break;
    }

    slave_to_master(FUN_06,8);

    eeprom_data_record();
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
        case FUN_03:
            crc = MODBUS_CRC16(rs485_4.send_buf,length);

            rs485_4.send_buf[length + 1] = crc;             //CRC H
            rs485_4.send_buf[length]     = crc >> 8;            //CRC L

            rs485_4.send_bytelength = length + 2;
            
            break;
        case FUN_04:
            crc = MODBUS_CRC16(rs485_4.send_buf,length);

            rs485_4.send_buf[length + 1] = crc;             //CRC H
            rs485_4.send_buf[length]     = crc >> 8;            //CRC L


            rs485_4.send_bytelength = length + 2;
            
            break;    

        case FUN_06:
            memcpy(rs485_4.send_buf,rs485_4.rcv_buf,8);

            rs485_4.send_bytelength = length;
            
            break;    

        // case 0x10:
        //     memcpy(rs485_4.send_buf,rs485_4.rcv_buf,6);
        
        //     crc = MODBUS_CRC16(rs485_4.send_buf,6);

        //     rs485_4.send_buf[7] = crc;                 //CRC H
        //     rs485_4.send_buf[6] = crc>>8;              //CRC L
        
        //     rs485_4.send_bytelength = length;
            
        //     break; 

        default:
            break;
    }

    DR4_485 = 1;                                 //485可以发送
    S4CON |= S4TI;                              //开始发送
    delay_ms(2);
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
