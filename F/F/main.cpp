#include <avr/io.h>
#include <avr/interrupt.h>

// Broches SPI Esclave
#define SS   2   // Broche Slave Select (SS) de l'Esclave (� personnaliser)
#define MOSI 3   // Broche MOSI (Master Out Slave In)
#define MISO 4   // Broche MISO (Master In Slave Out)
#define SCK  5   // Broche SCK (Clock)

#define ANALOG_PIN 0 //ADC0 

void ADC_Init() {
	// Configuration de la r�f�rence de tension (AVCC comme r�f�rence)
	ADMUX = (1 << REFS0);

	// Activation du convertisseur analogique-num�rique (CAN)
	ADCSRA |= (1 << ADEN);

	// Configuration de la fr�quence d'horloge de l'ADC (division par 128)
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_Read(uint8_t channel) {
	// S�lection de la broche analogique � lire
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

	// D�marrage de la conversion
	ADCSRA |= (1 << ADSC);

	// Attendre la fin de la conversion
	while (ADCSRA & (1 << ADSC))
	;

	// Lecture des donn�es de conversion (16 bits)
	uint16_t adcValue = ADC;

	return adcValue;
}

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
	// Initialisation de l'ADC
	ADC_Init();
	// Configuration de la broche de lecture comme entr�e
	DDRC &= ~(1 << ANALOG_PIN);
	// Variable pour stocker la valeur lue du capteur
	uint16_t sensorValue;
	uint8_t sensorValue8Bit;
	// Initialize SPI as slave
	SPI_SlaveInit();
	
	// Variable pour stocker les donn�es re�ues
	uint8_t receivedData;
	
	while (1) {
		// Attendre la demande du ma�tre
		receivedData = SPI_SlaveReceive();
		
		if(receivedData==0xFF){
			sensorValue = ADC_Read(ANALOG_PIN);
			sensorValue8Bit = (uint8_t)(sensorValue >> 2);
			SPDR = sensorValue8Bit;				//mettre le data dans le registre SPI
		}
	}

	return 0;
}


