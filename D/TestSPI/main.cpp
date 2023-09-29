#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Broches SPI Maître
#define SS   2   // Broche Slave Select (SS) du Maître (à personnaliser)
#define MOSI 3   // Broche MOSI (Master Out Slave In)
#define MISO 4   // Broche MISO (Master In Slave Out)
#define SCK  5   // Broche SCK (Clock)

// Broches de contrôle des LED
#define LED1	    PINC0
#define LED2	    PINC1
#define LED3	    PINC2
#define LED_ANALOG  PINC5

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
	DDRC |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1<< LED_ANALOG);

	uint8_t receivedData;
	uint8_t receivedData_F;

	while (1) {
		/*Parler au Slave E*/
		receivedData = SPI_MasterTransmit(0xEE);// Envoyer la commande pour allumer les leds
		
		uint8_t porte    = 0b00000001 & receivedData;
		uint8_t fenetre1 = 0b00001000 & receivedData;
		uint8_t fenetre2 = 0b01000000 & receivedData;

		//LED1
		if(porte == 0b00000001){
			PORTC |= (1 << LED1);
		}
		else{PORTC &= ~(1 << LED1);}
		//LED2
		if(fenetre1 == 0b00001000){
			PORTC |= (1 << LED2);
		}
		else{PORTC &= ~(1 << LED2);}
		//LED3
		if(fenetre2 == 0b01000000){
			PORTC |= (1 << LED3);
		}
		else{PORTC &= ~(1 << LED3);}


		_delay_ms(50);
		
//////////////////////////////// Vérifier que le slave envoi bien la valeur demandé
		/*Parler au Slave F*/
		receivedData_F = SPI_MasterTransmit(0xFF);// Envoyer la commande pour allumer les leds
		if(receivedData_F == 0b11111111){
			PORTC |= (1<<LED_ANALOG);
		}
		else{PORTC &= ~(1<<LED_ANALOG);}
			
		_delay_ms(50);
		

		
	}

	return 0;
}


