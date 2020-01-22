/**************************************************
Function: SPI_RW();

Description:
  Writes one byte to nRF24L01, and return the byte read
  from nRF24L01 during write, according to SPI protocol
���������8λ�Ĵ���װ���Ǵ����͵�����10101010�������ط��͡��½��ؽ��ա���λ�ȷ��͡�
��ô��һ������������ʱ�� ���ݽ�����sdo=1��
�Ĵ����е�10101010����һλ�����油��������һλδ֪��x������0101010x��
�½��ص�����ʱ��sdi�ϵĵ�ƽ�����浽�Ĵ�����ȥ����ô��ʱ�Ĵ���=0101010sdi��
������ 8��ʱ�������Ժ������Ĵ��������ݻ��ཻ��һ�Ρ������������һ��spiʱ��
/**************************************************/
uchar SPI_RW(uchar byte)
{
	uchar bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++)   // output 8-bit    // ��� 8 λ
   	{
   		MOSI = (byte & 0x80);         // output 'byte', MSB to MOSI		   // ��MOSI�����,�Ӹ�λ����λ.��BYTE ���λΪ1ʱ�߼�����Ϊ1,���1.����Ϊ0ʱ���0
   		byte = (byte << 1);           // shift next bit into MSB..	    // ����1λ.����λ���λת��.
   		SCK = 1;                      // Set SCK high..	   // ��SCK������,
   		byte |= MISO;       		  //byte=byte|MISO  capture current MISO bit	 	// ��MISO �ж���״̬λ����BYTE��.
   		SCK = 0;            		  // ..then set SCK low again		// ��SCK������.����һλ���.
   	}
    return(byte);           		  // return read byte	  	// ����״̬λ
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

  	CSN = 0;                   // CSN low, init SPI transaction	 // CSΪ��,��ʼSPI����
  	status = SPI_RW(reg);      // select register  // �����������ַ
  	SPI_RW(value);             // ..and write value to it..	 // д1 BYTE ֵ
  	CSN = 1;                   // CSN high again    // ���SPI����

  	return(status);      // ���� status        // return nRF24L01 status byte
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

  	CSN = 0;                // CSN low, initialize SPI communication...  // CSΪ��,��ʼSPI����
  	SPI_RW(reg);            // Select register to read from..  // ���ö���ַ
  	reg_val = SPI_RW(0);    // ..then read registervalue	  // ������
  	CSN = 1;                // CSN high, terminate SPI communication   // ���SPI����

  	return(reg_val);        // return register value	// ��������
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

  	CSN = 0;          	            // CSΪ��,��ʼSPI����// Set CSN low, init SPI tranaction
  	status = SPI_RW(reg);         	// ������������ݵ�����.	   // Select register to write to and read status byte

  	for(byte_ctr=0;byte_ctr<bytes;byte_ctr++)
    pBuf[byte_ctr] = SPI_RW(0);      // �� 1 BYTE����   // Perform SPI_RW to read byte from nRF24L01

  	CSN = 1;                         // ���ݴ������. // Set CSN high again

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

  	CSN = 0;               // CSΪ��,��ʼSPI����  // Set CSN low, init SPI tranaction
  	status = SPI_RW(reg);  // ����д�������ݵ�����.	  // Select register to write to and read status byte
  	for(byte_ctr=0; byte_ctr<bytes; byte_ctr++) // ���ͷ������� // then write all byte in buffer(*pBuf)
    	SPI_RW(*pBuf++);
  	CSN = 1;              // ���ݴ������.     // Set CSN high again
  	return(status);          // return nRF24L01 status byte
}
//���ú���
void NRF24L01_Config_1(void)
{
 //initial io
  CE=0;   //оƬʹ��
  CSN=1; //SPI����
  SCK=0; //SPIʱ��������
  CE=0;
  SPI_RW_Reg(WRITE_REG + CONFIG,0X0F);//�ϵ�ģʽ��ʹ��CRC(2���ֽ�)��RX_DRʹ��
  SPI_RW_Reg(WRITE_REG + EN_AA,0X3f);//Ƶ��0�Զ���ackӦ������
  SPI_RW_Reg(WRITE_REG + EN_RXADDR,0X3f);//����pipe0
  SPI_RW_Reg(WRITE_REG + RF_CH, 0);        //   �����ŵ�����Ϊ2.4GHZ���շ�����һ��
  SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB	
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ�շ�����ж���Ӧ��16λCRC��������
  SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ32�ֽ�
  SPI_RW_Reg(WRITE_REG + RX_PW_P1, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ32�ֽ�
//  SPI_RW_Reg(WRITE_REG + RX_PW_P2, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ32�ֽ�
//  SPI_RW_Reg(WRITE_REG + RX_PW_P3, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ32�ֽ�
//  SPI_RW_Reg(WRITE_REG + RX_PW_P4, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ32�ֽ�
//SPI_RW_Reg(WRITE_REG + RX_PW_P5, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ32�ֽ�
//SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 
  SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS1, TX_ADR_WIDTH);    // д���ص�ַ	
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // д���ն˵�ַ0
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P1, RX_ADDRESS1, RX_ADR_WIDTH); // д���ն˵�ַ1
 // SPI_Write_Buf(WRITE_REG + RX_ADDR_P2, RX_ADDRESS2, 1); // д���ն˵�ַ2
 // SPI_Write_Buf(WRITE_REG + RX_ADDR_P3, RX_ADDRESS3, 1); // д���ն˵�ַ3
 // SPI_Write_Buf(WRITE_REG + RX_ADDR_P4, RX_ADDRESS4, 1); // д���ն˵�ַ4
 // SPI_Write_Buf(WRITE_REG + RX_ADDR_P5, RX_ADDRESS5, 1); // д���ն˵�ַ5
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ�շ�����ж���Ӧ��16λCRC��������
  CE=1;/////////////
}



/////��������
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
//��������
void nRF24L01_TxPacket(unsigned char * tx_buf)
{
	CE=0;			//StandBy Iģʽ	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS1, TX_ADR_WIDTH); // װ�ؽ��ն˵�ַ
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 // װ������	
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ�շ�����ж���Ӧ��16λCRC��������
	CE=1;		 //�ø�CE���������ݷ���
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