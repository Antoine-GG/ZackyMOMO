#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Broches SPI Maître
#define SS   2   // Broche Slave Select (SS) du Maître (à personnaliser)
#define MOSI 3   // Broche MOSI (Master Out Slave In)
#define MISO 4   // Broche MISO (Master In Slave Out)
#define SCK  5   // Broche SCK (Clock)

// Broches de contrôle des LED
#define LED1 PINC0
#define LED2 PINC1
#define LED3 PINC2

void SPI_MasterInit() {
	// Set MOSI, SCK, and SS as outputs
	DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);
	// Enable SPI, Set as Master, clock rate fck/16
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

// Fonction pour transférer des données via SPI
uint8_t SPI_MasterTransmit(uint8_t data) {
	PORTB &= ~(1<<SS);
	// Start transmission
	SPDR = data;
	// Wait for transmission to complete
	while (!(SPSR & (1 << SPIF)));
	PORTB |= (1<<SS);
	// Return received data
	return SPDR;
}

int main() {
	// Initialize SPI as master
	SPI_MasterInit();

	// Configuration des broches de contrôle des LED comme sorties
	DDRC |= (1 << LED1) | (1 << LED2) | (1 << LED3);

	uint8_t receivedData;

	while (1) {
		// Envoyer la commande pour allumer la LED 1
		SPI_MasterTransmit(0b10000000);
		_delay_ms(10);
		receivedData = SPI_MasterTransmit(0xFF);
		
		uint8_t porte    = 0b00000001 & receivedData;
		uint8_t fenetre1 = 0b00000010 & receivedData;
		uint8_t fenetre2 = 0b00000100 & receivedData;

		//LED1
		if(porte > 0){
			PORTC |= (1 << LED1);
		}
		else{PORTC &= ~(1 << LED1);}
		//LED2
		if(fenetre1 > 0){
			PORTC |= (1 << LED2);
		}
		else{PORTC &= ~(1 << LED2);}
		//LED3
		if(fenetre2 > 0){
			PORTC |= (1 << LED3);
		}
		else{PORTC &= ~(1 << LED3);}


		_delay_ms(1000); // Attendre 1 seconde
				

		
	}

	return 0;
}


/*#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Broches SPI Maître
#define SS   2   // Broche Slave Select (SS) du Maître (à personnaliser)
#define MOSI 3   // Broche MOSI (Master Out Slave In)
#define MISO 4   // Broche MISO (Master In Slave Out)
#define SCK  5   // Broche SCK (Clock)

void SPI_MasterInit() {
	// Set MOSI, SCK, and SS as outputs
	DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);

	// Enable SPI, Set as Master, clock rate fck/16
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

// Fonction pour transférer des données via SPI
uint8_t SPI_MasterTransmit(uint8_t data) {
	// Start transmission
	SPDR = data;

	// Wait for transmission to complete
	while (!(SPSR & (1 << SPIF)))
	;

	// Return received data
	return SPDR;
}

int main() {
	// Initialize SPI as master
	SPI_MasterInit();

	// Variable pour stocker les données reçues
	uint8_t receivedData;
	uint8_t sendData;

	while (1) {
		// Envoyer une demande de données via SPI
		uint8_t sendData = 'R'; // Envoyer le caractère 'R' pour demander des données (à personnaliser)
		PORTB &= ~(1 << SS);    // Abaisser SS (activer l'esclave)

		receivedData = SPI_MasterTransmit(sendData);

		PORTB |= (1 << SS); // Lever SS (désactiver l'esclave)
		
		DDRC |= (1 << PINC0)|(1 << PINC1)|(1 << PINC2);
		if(receivedData=='D'){
			PORTC |= (1 << PINC0);
			PORTC &= ~(1 << PINC1);
			PORTC &= ~(1 << PINC2);
		}
		else{
			if(receivedData=='E'){
				PORTC &= ~(1 << PINC0);
				PORTC |= (1 << PINC1);
				PORTC &= ~(1 << PINC2);
			}
				else{
					if(receivedData=='F'){
						PORTC &= ~(1 << PINC0);
						PORTC &= ~(1 << PINC1);
						PORTC |= (1 << PINC2);
						}
					}
		}
				
	
				
		// Attendre un court délai pour éviter une communication trop rapide
		_delay_ms(1000);
		
		sendData = 'A';
		PORTB &= ~(1 << SS);    // Abaisser SS (activer l'esclave)
		
		SPI_MasterTransmit(sendData);

		PORTB |= (1 << SS); // Lever SS (désactiver l'esclave)
		_delay_ms(1000);
		// Utiliser receivedData selon vos besoins
		// ...
	}
	

	return 0;
}
*/