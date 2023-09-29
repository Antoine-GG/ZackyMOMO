#include <avr/io.h>
#include <avr/interrupt.h>

// Broches SPI Esclave
#define SS   2   // Broche Slave Select (SS) de l'Esclave (à personnaliser)
#define MOSI 3   // Broche MOSI (Master Out Slave In)
#define MISO 4   // Broche MISO (Master In Slave Out)
#define SCK  5   // Broche SCK (Clock)

#define fenetre1 0
#define fenetre2 3
#define porte    6

void SPI_SlaveInit() {
	// Set MISO as output
	DDRB |= (1 << MISO);
	// Enable SPI, Set as Slave
	SPCR |= (1 << SPE);
}

// Fonction pour recevoir des données via SPI
uint8_t SPI_SlaveReceive() {
	// Wait for reception to complete
	while (!(SPSR & (1 << SPIF)));
	// Return received data
	return SPDR;
}

int main() {
	// Initialize SPI as slave
	SPI_SlaveInit();
	
	// Variable pour stocker les données reçues
	uint8_t receivedData;
	
	DDRD &= ~(1<<fenetre1); DDRD &= ~(1<<fenetre2); DDRD &= ~(1<<porte);
	PORTD = 0xFF;
	while (1) {		
		// Attendre la demande du maître
		receivedData = SPI_SlaveReceive();
		
		uint8_t datatogo;					//récupère les données des INPUTs PIND
		
		if(receivedData==0xEE){
			uint8_t datatogo = PIND & 0x49; //ne regarder que les bits 0b0X00X00X
			SPDR = datatogo;				//mettre le data dans le registre SPI
		}
	}

	return 0;
}