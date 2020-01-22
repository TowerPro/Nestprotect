//Nrf24l01 transmit mode test
//MCU AT89S52


#include <reg52.h>
#include <intrins.h>
#include "api.h"
#include "nrf24l01.h"

sbit GM=P3^2;
sbit Key=P3^3;
/**************************************************
Function: main();

/**************************************************/
void main(void)
{
	NRF24L01_Config_1();
	delay_ms(100);
	while(1)
	{	
	
		
		if(GM==0) tx_buf[0]=0x0f;
		else  tx_buf[0]=0xf0;
		delay_ms(100);
	 	CE=1;
		NRF24L01_TxPacket(tx_buf);
		delay_ms(10);
		check_ACK();//发送应答信号检测，LED闪烁标志发送成功

		SPI_RW_Reg(WRITE_REG+STATUS,0xff);//清中断标志		  
	
		delay_ms(100);
		delay_ms(100);
		delay_ms(100);  
	}

}


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




