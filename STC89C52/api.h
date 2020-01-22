// BYTE type definition
#ifndef _BYTE_DEF_
#define _BYTE_DEF_
typedef unsigned char BYTE;
#endif 

//****************************************************************//

#define READ_REG        0x00  // Define read command to register
#define WRITE_REG       0x20  // Define write command to register
#define RD_RX_PLOAD     0x61  // Define RX payload register address
#define WR_TX_PLOAD     0xA0  // Define TX payload register address
#define FLUSH_TX        0xE1  // Define flush TX register command
#define FLUSH_RX        0xE2  // Define flush RX register command
#define REUSE_TX_PL     0xE3  // Define reuse TX payload register command
#define NOP             0xFF  // Define No Operation, might be used to read status register

//***************************************************//
// SPI(nRF24L01) registers(addresses)
#define CONFIG          0x00  // 'Config' register address
#define EN_AA           0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR       0x02  // 'Enabled RX addresses' register address
#define SETUP_AW        0x03  // 'Setup address width' register address
#define SETUP_RETR      0x04  // 'Setup Auto. Retrans' register address
#define RF_CH           0x05  // 'RF channel' register address
#define RF_SETUP        0x06  // 'RF setup' register address
#define STATUS          0x07  // 'Status' register address
#define OBSERVE_TX      0x08  // 'Observe TX' register address
#define CD              0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0      0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1      0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2      0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3      0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4      0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5      0x0F  // 'RX address pipe5' register address
#define TX_ADDR         0x10  // 'TX address' register address
#define RX_PW_P0        0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1        0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2        0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3        0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4        0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5        0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS     0x17  // 'FIFO Status Register' register address

//***************************************************************//
//The others

#define uchar unsigned char
#define TX_ADR_WIDTH    5   // 5 bytes TX(RX) address width
#define RX_ADR_WIDTH    5
#define TX_PLOAD_WIDTH  1  // 10 bytes TX payload
#define RX_PLOAD_WIDTH  1

uchar const TX_ADDRESS[TX_ADR_WIDTH]  = {0x34,0x43,0x10,0x10,0x01}; // Define a static TX address		   /0x34是火焰0xb0是光敏
uchar const TX_ADDRESS1[TX_ADR_WIDTH]  = {0x35,0xa1,0xb3,0xc9,0xda}; // Define a static TX address		   /0x34是火焰0xb0是光敏
uchar code RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0x43,0x10,0x10,0x01};	//接收地址
uchar code RX_ADDRESS1[RX_ADR_WIDTH]= {0x35,0xa1,0xb3,0xc9,0xda};	//接收地址1
uchar code RX_ADDRESS2[1]= {0xb1};	//接收地址2
uchar code RX_ADDRESS3[1]= {0xb2};	//接收地址3
uchar code RX_ADDRESS4[1]= {0xb3};	//接收地址4
uchar code RX_ADDRESS5[1]= {0xb4};	//接收地址5
uchar rx_buf_1[TX_PLOAD_WIDTH];
uchar rx_buf_2[TX_PLOAD_WIDTH];
uchar tx_buf[TX_PLOAD_WIDTH];




uchar flag;
/**************************************************/

sbit CE =P1^0;	  //接在AT89S52的P0口
sbit CSN =P1^1;
sbit SCK =P1^2;
sbit MOSI =P1^3;
sbit MISO =P1^4;
sbit IRQ =P1^5;

sbit L1 = P2^3;




/**************************************************/
uchar 	bdata sta;
sbit	RX_DR	=sta^6;	//接收数据准备就绪
sbit	TX_DS	=sta^5;	 //已发送数据
sbit	MAX_RT	=sta^4;	  // 最大的TX重传＃中断

//***************************************************************//
//                   FUNCTION's PROTOTYPES  //
/****************************************************************/
 BYTE SPI_RW(BYTE byte);                                // Single SPI read/write
 BYTE SPI_Read(BYTE reg);                               // Read one byte from nRF24L01
 BYTE SPI_RW_Reg(BYTE reg, BYTE byte);                  // Write one byte to register 'reg'
 BYTE SPI_Write_Buf(BYTE reg, BYTE *pBuf, BYTE bytes);  // Writes multiply bytes to one register
 BYTE SPI_Read_Buf(BYTE reg, BYTE *pBuf, BYTE bytes);   // Read multiply bytes from one register
 BYTE NRF24L01_RxPacket(BYTE *rx_buf);
 void NRF24L01_TxPacket(BYTE *tx_buf);
 //void RX_Mode(void);
 //void TX_Mode(void);
 void NRF24L01_Config_1(void);
  void NRF24L01_Config_2(void);
 void check_ACK();
 void delay_ms(unsigned int x);
//*****************************************************************/
