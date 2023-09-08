/*
 * TestSPI.cpp
 *
 * Created: 2023-09-08 12:39:33
 * Author : Zachary Simard
 * inspiration: http://www.rjhcoding.com/avrc-spi.php
 */ 

#include <avr/io.h>
#define SPI_DDR DDRB
#define CS      PINB2
#define MOSI    PINB3
#define MISO    PINB4
#define SCK     PINB5
#define SS1		PINB6 //
#define SS2		PINB7 //

void SPI_init()
{
	// set CS, MOSI and SCK to output
	SPI_DDR |= (1 << CS) | (1 << MOSI) | (1 << SCK);

	// enable SPI, set as master, and clock to fosc/128
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
}

void SPI_masterTransmitByte(uint8_t data,uint8_t SelectionSlave)
{
    // drive slave select low
    SPI_DDR &= ~(1 << SelectionSlave);
		
	// load data into register
	SPDR = data;

	// Wait for transmission complete
	while(!(SPSR & (1 << SPIF)));
	
    // return slave select to high
    SPI_DDR |= (1 << SelectionSlave);
}

int main(void)
{SPI_init();
    while (1) 
    {
		SPI_masterTransmitByte(1, SS1);
    }
}

