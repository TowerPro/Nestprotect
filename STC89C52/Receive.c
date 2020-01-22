//Nrf24l01 receive mode test
//MCU AT89S52

#include <reg52.h>
#include <intrins.h>
#include "api.h"
#include "nrf24l01.h"


sbit play_1=P3^4;
sbit play_2=P3^5;
unsigned int i;
unsigned char flag;


/**************************************************
Function: main();

/**************************************************/

void main(void)
{
unsigned char DATA;
    NRF24L01_Config_1();
	delay_ms(100);
    NRF24L01_RxPacket(rx_buf_1);
   	delay_ms(100);

	
	while(1)
	{
	  DATA=0x00;
	  delay_ms(100);
	  check_ACK(); 
	/*
		CE=0;
	SPI_RW_Reg(WRITE_REG + EN_AA,0X01);//频道0自动，ack应答允许
  	SPI_RW_Reg(WRITE_REG + EN_RXADDR,0X01);//允许pipe0
		 CE=1;	 

	*/	
	 	 if(NRF24L01_RxPacket(rx_buf_1)) 
		 {
		 DATA=rx_buf_1[0];
		/* if(DATA==0x0f) play_1=1;*/	if(DATA==0x0f) P2=0x08;
		/*  if(DATA==0xf0) play_1=0;*/	if(DATA==0xf0) P2=0;
	 	  }
		 delay_ms(100);
	/*	 
		 CE=0;
		SPI_RW_Reg(WRITE_REG + EN_AA,0X02);//频道0自动，ack应答允许
		SPI_RW_Reg(WRITE_REG + EN_RXADDR,0X02);//允许pipe0
		 CE=1;
		 
		 delay_ms(100); 	 
	 	 if(NRF24L01_RxPacket(rx_buf_2)) 
		 {
		 DATA=rx_buf_2[0];
		 if(DATA==0x0e) play_2=1;
		 if(DATA==0xe0) play_2=0;
	 	  }
		  */
		  P2=0;
		  delay_ms(100);
	
		  //delay_ms(250); 
	   	  play_1=0;
		  play_2=0;
	 																					
	   
	} 
} 
  
/*
void main(void)
{
	int j=0;

    LCD_Init();
	L1=0;//LED亮标志开始工作
	RX_Mode();//接收模式 
	while(1)
	{																							
	   CE=0;
    
		sta=SPI_Read(READ_REG +STATUS);//检测状态寄存器状态

	  if(RX_DR)
	   	{
		
			SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);//读取接收缓冲区数值
		    flag=1;

		}
		if(MAX_RT)
		{
		 SPI_RW_Reg(FLUSH_TX,0);
		}
		SPI_RW_Reg(WRITE_REG+STATUS,sta);
		if(flag)
		{  
		    flag=0; 
		 	L1=1;//LED闪烁标志接收成功
			delay_ms(100);
			L1=0;
		  LCD_POS(0X40);
         for(i=0;i<10;i++)
		   {  
	  		LCD_WRITE_DATA(b[rx_buf[i]]);
	  	   }
		} 
		SPI_RW_Reg(WRITE_REG+STATUS,0xff);//清中断标志
	} 
}  */
  
/**************************************************
Function: delay_ms(unsigned int x)

/**************************************************/
void delay_ms(unsigned int x)
{
    unsigned int i,j;
    i=0;
    for(i=0;i<x;i++)
    {
       j=108;
       while(j--);
    }
}
/**************************************************/


