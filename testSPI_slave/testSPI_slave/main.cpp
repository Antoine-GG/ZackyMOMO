#include <avr/io.h>
#include <avr/interrupt.h>

// Broches SPI Esclave
#define SS   2   // Broche Slave Select (SS) de l'Esclave (� personnaliser)
#define MOSI 3   // Broche MOSI (Master Out Slave In)
#define MISO 4   // Broche MISO (Master In Slave Out)
#define SCK  5   // Broche SCK (Clock)

#define fenetre1 PC3;
#define fenetre2 PC5;
#define porte    PC7;

void SPI_SlaveInit() {
	// Set MISO as output
	DDRB |= (1 << MISO);
	// Enable SPI, Set as Slave
	SPCR |= (1 << SPE);
}

// Fonction pour recevoir des donn�es via SPI
uint8_t SPI_SlaveReceive() {
	// Wait for reception to complete
	while (!(SPSR & (1 << SPIF)));
	// Return received data
	return SPDR;
}

int main() {
	// Initialize SPI as slave
	SPI_SlaveInit();
	
	// Variable pour stocker les donn�es re�ues
	uint8_t receivedData;
	
	DDRC &= ~(1<<fenetre1) | ~(1<<fenetre2) | ~(1<<porte);
	while (1) {
		
/////////////////////////////////////////////////////////////////////////////////rendu a faire le code pour allumer les dels 		
		
		// Attendre la demande du ma�tre
		receivedData = SPI_SlaveReceive();
		if(receivedData==0b10000000){
			SPDR = 
		}

		// R�agir en fonction des donn�es re�ues (pas n�cessaire pour l'esclave)
	}

	return 0;
}

/*#include <avr/io.h>
#include <avr/interrupt.h>

// Broches SPI Esclave
#define SS   2   // Broche Slave Select (SS) de l'Esclave (� personnaliser)
#define MOSI 3   // Broche MOSI (Master Out Slave In)
#define MISO 4   // Broche MISO (Master In Slave Out)
#define SCK  5   // Broche SCK (Clock)
int flag = 0;

void SPI_SlaveInit() {
	// Set MISO as output
	DDRB |= (1 << MISO);

	// Enable SPI, Set as Slave
	SPCR |= (1 << SPE);
}

// Fonction pour recevoir des donn�es via SPI
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

	uint8_t receivedData;
	uint8_t sendData;

	while (1) {
		// Attendre la demande de donn�es
		while (SPI_SlaveReceive() != 'R')
		;

		// Envoyer les donn�es demand�es via SPI
		if(flag==0){
			uint8_t sendData = 'D';
			flag++;
		}
		else{
			if(flag==1){
				uint8_t sendData = 'E';
				flag++;
			}
			else{
				if(flag==2){
					uint8_t sendData = 'F';
					flag=0;
				}
			}
		}

		//uint8_t sendData = 'D'; // Envoyer le caract�re 'D' comme donn�es (� personnaliser)

		SPDR = sendData; // Commencer la transmission

		// Attendre la fin de la transmission
		while (!(SPSR & (1 << SPIF)))
		;

		// R�p�ter le processus pour d'autres demandes de donn�es
	}

	return 0;
}
*/
