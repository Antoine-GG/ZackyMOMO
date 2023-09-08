/*
 * testSPI_slave.cpp
 *
 * Created: 2023-09-08 13:34:00
 * Author : 2132249
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Broches SPI Esclave
#define SS   2   // Broche Slave Select (SS) de l'Esclave (à personnaliser)
#define MOSI 3   // Broche MOSI (Master Out Slave In)
#define MISO 4   // Broche MISO (Master In Slave Out)
#define SCK  5   // Broche SCK (Clock)

void SPI_SlaveInit() {
	// Set MISO as output
	DDRB |= (1 << MISO);
	
	// Enable SPI, Set as Slave
	SPCR |= (1 << SPE);
}

// Fonction pour recevoir des données via SPI
uint8_t SPI_SlaveReceive() {
	// Wait for reception to complete
	while (!(SPSR & (1 << SPIF)))
	;

	// Return received data
	return SPDR;
}

int main() {
	// Initialize SPI as slave
	SPI_SlaveInit();
	DDRC |= (1 << PINC0);

	uint8_t receivedData;

	while (1) {
		receivedData = SPI_SlaveReceive();

		// Utilisez receivedData selon vos besoins
				if(receivedData == 'A'){
					PORTC |= (1 << PINC0);
				}
	}

	return 0;
}


