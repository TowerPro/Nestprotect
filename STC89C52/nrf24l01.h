/**************************************************
Function: SPI_RW();

Description:
  Writes one byte to nRF24L01, and return the byte read
  from nRF24L01 during write, according to SPI protocol
假设下面的8位寄存器装的是待发送的数据10101010，上升沿发送、下降沿接收、高位先发送。
那么第一个上升沿来的时候 数据将会是sdo=1；
寄存器中的10101010左移一位，后面补入送来的一位未知数x，成了0101010x。
下降沿到来的时候，sdi上的电平将锁存到寄存器中去，那么这时寄存器=0101010sdi，
这样在 8个时钟脉冲以后，两个寄存器的内容互相交换一次。这样就完成里一个spi时序
/**************************************************/
uchar SPI_RW(uchar byte)
{
	uchar bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++)   // output 8-bit    // 输出 8 位
   	{
   		MOSI = (byte & 0x80);         // output 'byte', MSB to MOSI		   // 从MOSI脚输出,从高位到低位.当BYTE 最高位为1时逻辑运算为1,输出1.运算为0时输出0
   		byte = (byte << 1);           // shift next bit into MSB..	    // 左移1位.将低位向高位转移.
   		SCK = 1;                      // Set SCK high..	   // 将SCK脚拉高,
   		byte |= MISO;       		  //byte=byte|MISO  capture current MISO bit	 	// 从MISO 中读出状态位存入BYTE中.
   		SCK = 0;            		  // ..then set SCK low again		// 将SCK脚拉低.发送一位完成.
   	}
    return(byte);           		  // return read byte	  	// 返回状态位
}
/**************************************************/
void inerDelay_us(unsigned char n)
{
	for(;n>0;n--)
		_nop_();
}
/**************************************************
Function: SPI_RW_Reg();

Description:
  Writes value 'value' to register 'reg'
/**************************************************/
uchar SPI_RW_Reg(BYTE reg, BYTE value)
{
	uchar status;

  	CSN = 0;                   // CSN low, init SPI transaction	 // CS为低,开始SPI传输
  	status = SPI_RW(reg);      // select register  // 传送命令与地址
  	SPI_RW(value);             // ..and write value to it..	 // 写1 BYTE 值
  	CSN = 1;                   // CSN high again    // 完成SPI传输

  	return(status);      // 返回 status        // return nRF24L01 status byte
}
/**************************************************/

/**************************************************
Function: SPI_Read();

Description:
  Read one byte from nRF24L01 register, 'reg'
/**************************************************/
BYTE SPI_Read(BYTE reg)
{
	BYTE reg_val;

  	CSN = 0;                // CSN low, initialize SPI communication...  // CS为低,开始SPI传输
  	SPI_RW(reg);            // Select register to read from..  // 设置读地址
  	reg_val = SPI_RW(0);    // ..then read registervalue	  // 读数据
  	CSN = 1;                // CSN high, terminate SPI communication   // 完成SPI传输

  	return(reg_val);        // return register value	// 返回数据
}
/**************************************************/

/**************************************************
Function: SPI_Read_Buf();

Description:
  Reads 'bytes' #of bytes from register 'reg'
  Typically used to read RX payload, Rx/Tx address
/**************************************************/
uchar SPI_Read_Buf(BYTE reg, BYTE *pBuf, BYTE bytes)
{
	uchar status,byte_ctr;

  	CSN = 0;          	            // CS为低,开始SPI传输// Set CSN low, init SPI tranaction
  	status = SPI_RW(reg);         	// 传输读接收数据的命令.	   // Select register to write to and read status byte

  	for(byte_ctr=0;byte_ctr<bytes;byte_ctr++)
    pBuf[byte_ctr] = SPI_RW(0);      // 读 1 BYTE数据   // Perform SPI_RW to read byte from nRF24L01

  	CSN = 1;                         // 数据传送完成. // Set CSN high again

  	return(status);                    // return nRF24L01 status byte
}
/**************************************************/

/**************************************************
Function: SPI_Write_Buf();

Description:
  Writes contents of buffer '*pBuf' to nRF24L01
  Typically used to write TX payload, Rx/Tx address
/**************************************************/
uchar SPI_Write_Buf(BYTE reg, BYTE *pBuf, BYTE bytes)
{
	uchar status,byte_ctr;

  	CSN = 0;               // CS为低,开始SPI传输  // Set CSN low, init SPI tranaction
  	status = SPI_RW(reg);  // 传输写发送数据的命令.	  // Select register to write to and read status byte
  	for(byte_ctr=0; byte_ctr<bytes; byte_ctr++) // 传送发送数据 // then write all byte in buffer(*pBuf)
    	SPI_RW(*pBuf++);
  	CSN = 1;              // 数据传送完成.     // Set CSN high again
  	return(status);          // return nRF24L01 status byte
}
//配置函数
void NRF24L01_Config_1(void)
{
 //initial io
  CE=0;   //芯片使能
  CSN=1; //SPI禁能
  SCK=0; //SPI时钟线拉高
  CE=0;
  SPI_RW_Reg(WRITE_REG + CONFIG,0X0F);//上电模式，使能CRC(2个字节)和RX_DR使能
  SPI_RW_Reg(WRITE_REG + EN_AA,0X3f);//频道0自动，ack应答允许
  SPI_RW_Reg(WRITE_REG + EN_RXADDR,0X3f);//允许pipe0
  SPI_RW_Reg(WRITE_REG + RF_CH, 0);        //   设置信道工作为2.4GHZ，收发必须一致
  SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//设置发射速率为1MHZ，发射功率为最大值0dB	
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ收发完成中断响应，16位CRC，主发送
  SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
  SPI_RW_Reg(WRITE_REG + RX_PW_P1, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
//  SPI_RW_Reg(WRITE_REG + RX_PW_P2, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
//  SPI_RW_Reg(WRITE_REG + RX_PW_P3, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
//  SPI_RW_Reg(WRITE_REG + RX_PW_P4, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
//SPI_RW_Reg(WRITE_REG + RX_PW_P5, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
//SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 
  SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS1, TX_ADR_WIDTH);    // 写本地地址	
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址0
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P1, RX_ADDRESS1, RX_ADR_WIDTH); // 写接收端地址1
 // SPI_Write_Buf(WRITE_REG + RX_ADDR_P2, RX_ADDRESS2, 1); // 写接收端地址2
 // SPI_Write_Buf(WRITE_REG + RX_ADDR_P3, RX_ADDRESS3, 1); // 写接收端地址3
 // SPI_Write_Buf(WRITE_REG + RX_ADDR_P4, RX_ADDRESS4, 1); // 写接收端地址4
 // SPI_Write_Buf(WRITE_REG + RX_ADDR_P5, RX_ADDRESS5, 1); // 写接收端地址5
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ收发完成中断响应，16位CRC，主发送
  CE=1;/////////////
}



/////接收数据
BYTE NRF24L01_RxPacket(BYTE *rx_buf)
{
  uchar revale=0;
  SPI_RW_Reg(WRITE_REG + CONFIG,0X0F);
  CE=1;
  delay_ms(10);
  sta=SPI_Read(STATUS);
  if(RX_DR)
  {
  	CE=0;
	SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);
    revale=1; 
  }
 SPI_RW_Reg(WRITE_REG + STATUS,sta);
 return revale;
}
//发送数据
void nRF24L01_TxPacket(unsigned char * tx_buf)
{
	CE=0;			//StandBy I模式	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS1, TX_ADR_WIDTH); // 装载接收端地址
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 // 装载数据	
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ收发完成中断响应，16位CRC，主发送
	CE=1;		 //置高CE，激发数据发送
	inerDelay_us(10);
}






/**************************************************/

/**************************************************
Function: RX_Mode();

Description:
  This function initializes one nRF24L01 device to
  RX Mode, set RX address, writes RX payload width,
  select RF channel, datarate & LNA HCURR.
  After init, CE is toggled high, which means that
  this device is now ready to receive a datapacket.
/**************************************************/
/*
void RX_Mode(void)
{
	CE=0;
 
  	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // Use the same address on the RX device as the TX device

  	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      // Enable Auto.Ack:Pipe0
  	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  // Enable Pipe0
  	SPI_RW_Reg(WRITE_REG + RF_CH, 40);        // Select RF channel 40
  	SPI_RW_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH); // Select same RX payload width as TX Payload width
  	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR
  	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);     // Set PWR_UP bit, enable CRC(2 bytes) & Prim:RX. RX_DR enabled..

  	CE = 1; // Set CE pin high to enable RX device
	delay_ms(10);
	CE=0;
  //  This device is now ready to receive one packet of 16 bytes payload from a TX device sending to address
  //  '3443101001', with auto acknowledgment, retransmit count of 10, RF channel 40 and datarate = 2Mbps.

}	*/
/**************************************************/

/**************************************************
Function: TX_Mode();

Description:
  This function initializes one nRF24L01 device to
  TX mode, set TX address, set RX address for auto.ack,
  fill TX payload, select RF channel, datarate & TX pwr.
  PWR_UP is set, CRC(2 bytes) is enabled, & PRIM:TX.

  ToDo: One high pulse(>10us) on CE will now send this
  packet and expext an acknowledgment from the RX device.
/**************************************************/
/*
void TX_Mode(void)
{
	CE=0;

  	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // Writes TX_Address to nRF24L01
  	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // RX_Addr0 same as TX_Adr for Auto.Ack
  	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); // Writes data to TX payload

  	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      // Enable Auto.Ack:Pipe0
  	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  // Enable Pipe0
  	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x1a); // 500us + 86us, 10 retrans...
  	SPI_RW_Reg(WRITE_REG + RF_CH, 40);        // Select RF channel 40
  	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR
  	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);     // Set PWR_UP bit, enable CRC(2 bytes) & Prim:TX. MAX_RT & TX_DS enabled..
	
	CE=1;
	delay_ms(10);
	CE=0;
} */
/**************************************************/

/**************************************************
Function: check_ACK();

Description:
  check if have "Data sent TX FIFO interrupt",if TX_DS=1,
  all led light and after delay 100ms all led close
/**************************************************/
void check_ACK()
{
	uchar test;
	test=SPI_Read(READ_REG+STATUS);	// read register STATUS's
	test=test&0x20;					// check if have Data sent TX FIFO interrupt (TX_DS=1)
	if(test==0x20)					// TX_DS =1
	{
		L1=1;					
	    delay_ms(100);					// delay 100ms
		L1=0;
	}
}