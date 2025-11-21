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
    if( rs485.rcv_end_Flag == 1 )
    {

        /*2.CRC校验                                         */
        crc = MODBUS_CRC16(rs485.rcv_buf, rs485.rcv_cnt-2);
        rccrc = (rs485.rcv_buf[rs485.rcv_cnt - 1]) | (rs485.rcv_buf[rs485.rcv_cnt -2 ] << 8);

        /*3.CRC校验通过，进行地址域校验                      */
        if( crc == rccrc )
        {
            /*3-1.地址域校验通过，进入相应功能函数进行处理      */
            if( rs485.rcv_buf[0] == MY_ADDR )
            {
                switch ( rs485.rcv_buf[1] )
                {
                    case FUN_03:      Modbus_Fun3();          break;
                    case FUN_04:      Modbus_Fun4();          break;
                    case FUN_06:      Modbus_Fun6();          break;
                    case FUN_16:      Modbus_Fun16();         break;

                    default:                                  break;
                }
            }
        }
        /*4.清空接收完毕标志位  清空接收计数        */    
        rs485.rcv_end_Flag = 0;
        rs485.rcv_cnt = 0; 
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
    modbus.start_reg_03    = rs485.rcv_buf[2] << 8 | rs485.rcv_buf[3];
    modbus.reg_num_03      = rs485.rcv_buf[4] << 8 | rs485.rcv_buf[5];

    rs485.send_buf[0]  = MY_ADDR;                  //Addr
    rs485.send_buf[1]  = FUN_03;                   //Fun
    rs485.send_buf[2]  = modbus.reg_num_03 * 2;    //Byte Count

    for( i = modbus.start_reg_03; i < modbus.start_reg_03 + modbus.reg_num_03; i++ )
    {
        switch (i)
        {               
            /*  40001 前烘干停止温度                    */
            case 0x00:
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.F_HeatTemp;
                break;

            /*  40002 前烘干开关                    */
            case 0x01:
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.F_HeatSwitch;
                break;

            /*  40003 中烘干停止温度                    */
            case 0x02:
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.M_HeatTemp;
                break;

            /*  40004 中烘干开关                    */
            case 0x03:
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.M_HeatSwitch;
                break;

            /*  40005 后加热停止温度                     */    
            case 0x04:
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.R_HeatTemp;
                break;

            /*  40006 后加热开关                     */    
            case 0x05:
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.R_HeatSwitch;
                break;

            /*  40007 撒粉电机转速                 */
            case 0x06:   
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.SF_level;
                break;

            /*  40008 撒粉电机开关                 */
            case 0x07:   
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.SF_Switch;
                break;    

            /*  40009 回粉电机方向                */
            case 0x08:   
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.HF_Direction;
                break;

            /*  40010 回粉电机转速                */
            case 0x09:   
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.HF_level;
                break;

            /*  40011 回粉电机转速                */
            case 0x0a:   
                modbus.byte_info_H  = 0x00;
                modbus.byte_info_L  = slave_06.HF_Switch;
                break;

            default:
                modbus.byte_info_H = 0x00;
                modbus.byte_info_L = 0x00;
                break;
        }
        rs485.send_buf[modbus.rcv_addr1_valH++] = modbus.byte_info_H;
        rs485.send_buf[modbus.rcv_addr1_valH++] = modbus.byte_info_L;
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

    modbus.rcv_addr1_valH  = 3;                 //DATA1 H 位置
    modbus.start_reg_04 = rs485.rcv_buf[2] << 8 | rs485.rcv_buf[3];
    modbus.reg_num_04   = rs485.rcv_buf[4] << 8 | rs485.rcv_buf[5];

    rs485.send_buf[0]  = MY_ADDR;                  //Addr
    rs485.send_buf[1]  = FUN_04;                   //Fun
    rs485.send_buf[2]  = modbus.reg_num_04 * 2;    //Byte Count

    for( i = modbus.start_reg_04; i < modbus.start_reg_04 + modbus.reg_num_04; i++ )
    {
        switch (i)
        {
            /*  30001  thermopile1温度                        */
            case 0x00:
                modbus.byte_info_H = temp.thermo1_temp >> 8;
                modbus.byte_info_L = temp.thermo1_temp;
                break;

            /*  30002  thermopile2温度                        */
            case 0x01:
                modbus.byte_info_H = temp.thermo2_temp >> 8;
                modbus.byte_info_L = temp.thermo2_temp;
                break;

            /*  30003  thermopile3温度                        */
            case 0x02:
                modbus.byte_info_H = temp.thermo3_temp >> 8;
                modbus.byte_info_L = temp.thermo3_temp;
                break;

            default:
                modbus.byte_info_H = 0X00;
                modbus.byte_info_L = 0X00;
                break;
        }
        rs485.send_buf[modbus.rcv_addr1_valH++] = modbus.byte_info_H;
        rs485.send_buf[modbus.rcv_addr1_valH++] = modbus.byte_info_L;
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
    modbus.reg_addr_06 = rs485.rcv_buf[2] << 8 | rs485.rcv_buf[3];
    modbus.byte_info_H = rs485.rcv_buf[4];
    modbus.byte_info_L = rs485.rcv_buf[5];

    switch (rs485.rcv_buf[3])
    {
        /*  40001 前烘干停止温度                    */
        case 0x00:
            slave_06.F_HeatTemp = modbus.byte_info_L;
            break;

        /*  40002 前烘干开关                    */
        case 0x01:
            slave_06.F_HeatSwitch = modbus.byte_info_L;
            break;

        /*  40003 中烘干停止温度                    */
        case 0x02:
            slave_06.M_HeatTemp = modbus.byte_info_L;
            break;

        /*  40004 中烘干开关                    */
        case 0x03:
            slave_06.M_HeatSwitch = modbus.byte_info_L;
            break;

        /*  40005 后加热停止温度                     */    
        case 0x04:
            slave_06.R_HeatTemp = modbus.byte_info_L;
            break;

        /*  40006 后加热开关                     */    
        case 0x05:
            slave_06.R_HeatSwitch = modbus.byte_info_L;
            break;

        /*  40007 撒粉电机转速                 */
        case 0x06:   
            slave_06.SF_level = modbus.byte_info_L;
            break;

        /*  40008 撒粉电机开关                 */
        case 0x07:   
            slave_06.SF_Switch = modbus.byte_info_L;
            break;    

        /*  40009 回粉电机方向                */
        case 0x08:   
            slave_06.HF_Direction = modbus.byte_info_L;
            break;

        /*  40010 回粉电机转速                */
        case 0x09:   
            slave_06.HF_level = modbus.byte_info_L;
            break;

        /*  40011 回粉电机开关                */
        case 0x0a:   
            slave_06.HF_Switch = modbus.byte_info_L;
            break;

        /*  40012 同步开关              */
        case 0x0b:                                         
            slave_06.sync_switch = modbus.byte_info_L;
            break;

        /*  40013 同步开关信号             */
        case 0x0c:                                             
            slave_06.sync_signal = modbus.byte_info_L;
            break;

        /*  40014 回到原点信号              */
        case 0x0d:                                         
            slave_06.signal_back = modbus.byte_info_L;
            break;

        /*  40015 总电源开关             */
        case 0x0e:                                             
            power_ctrl.power_switch = modbus.byte_info_L;
            break;

        default:
            break;   
    }

    slave_to_master(FUN_06,8);

    eeprom_data_record();
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

    modbus.rcv_addr1_valH = 7;                  //DATA1 H位置
    modbus.start_reg_16 = rs485.rcv_buf[2] << 8 | rs485.rcv_buf[3];
    modbus.reg_num_16   = rs485.rcv_buf[4] << 8 | rs485.rcv_buf[5];


    for( i = modbus.rcv_addr1_valH; i < modbus.rcv_addr1_valH + modbus.reg_num_16; i++)
    {
        modbus.byte_info_H = rs485.rcv_buf[modbus.rcv_addr1_valH];
        modbus.byte_info_L = rs485.rcv_buf[modbus.rcv_addr1_valH + 1];
        switch (i)
        {
            /*  40012 同步开关              */
            case 0x0b:                                         
                slave_06.sync_switch = modbus.byte_info_L;
                break;

            /*  40013 同步开关信号             */
            case 0x0c:                                             
                slave_06.sync_signal = modbus.byte_info_L;
                break;

            /*  40014 回到原点信号              */
            case 0x0d:                                         
                slave_06.signal_back = modbus.byte_info_L;
                break;

                default:
                    break;
        }
        modbus.rcv_addr1_valH += 2;         //从Value1_H →→ 从Value2_H
    }

    slave_to_master(FUN_16,8);
}

/**
 * @brief	从机回复主机
 *  
 * @param   code_num:功能码       
 * @param   length:数据长度        
 * 
  @return  crc16:crc校验的值 2byte
 */
void slave_to_master( uint8_t code_num, uint8_t length )
{
    uint16_t crc;

    switch (code_num)
    {
        case FUN_03:
            crc = MODBUS_CRC16(rs485.send_buf,length);

            rs485.send_buf[length+1] = crc;             //CRC H
            rs485.send_buf[length]   = crc >> 8;        //CRC L

            rs485.send_bytelength = length + 2;
            break;

        case FUN_04:
            crc = MODBUS_CRC16(rs485.send_buf,length);

            rs485.send_buf[length+1] = crc;              //CRC H
            rs485.send_buf[length]   = crc >> 8;         //CRC L

            rs485.send_bytelength = length + 2;
            break;    

        case FUN_06:
            memcpy(rs485.send_buf,rs485.rcv_buf,8);

            rs485.send_bytelength = length;
            break;    

        case FUN_16:
            memcpy(rs485.send_buf,rs485.rcv_buf,6);
        
            crc = MODBUS_CRC16(rs485.send_buf,6);

            rs485.send_buf[7] = crc;                 //CRC H
            rs485.send_buf[6] = crc >> 8;            //CRC L
        
            rs485.send_bytelength = length;
            break; 

        default:
            break;
    }

    DR_485 = 1;                                 //485可以发送
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
