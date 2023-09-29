/*
 * main.c
 *
 * Created: 9/7/2023 3:08:19 PM
 *  Author: Wafaa
 */ 

#include <avr/io.h>
//#include <util/setbaud.h>
#include <string.h>
#define LED_PIN  PB1  
#define BUFFER_SIZE 20
//const  BAUD 9600

char received_status[BUFFER_SIZE];

void uart_init() {
	//UBRR0H = UBRRH_VALUE;
	//UBRR0L = UBRRL_VALUE;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //set data frame to 8-bit: https://www.appelsiini.net/2011/simple-usart-with-avr-libc/#registers:~:text=bit%202%20bit,9%2Dbit%20(111).
}
void uart_putchar(char c) {
	while (!(UCSR0A & (1 << UDRE0))); //wait for register TX to be empty
	UDR0 = c;
}
char uart_getchar() {
	while (!(UCSR0A & (1 << RXC0))); //wait for register RX to be empty
	return UDR0;
}
void receive_status() {
	uint8_t i = 0;
while (i < (BUFFER_SIZE - 1)) {
	char received_char = uart_getchar();
		received_status[i++] = received_char;
		received_status[i] = '\0'; //écrit un NULL caracter pour indiquer la fin d'un message (voir prochaine ligne) 
		if (strcmp(received_status, "code_ok") == 0) { //check pour voir si la ligne de caractère avant le caractère NULL est similaire à "code ok"
			PORTB |= (1 << LED_PIN);
			break; 
		}
	}
}
int main() {
	uart_init;
	DDRB |= (1 << LED_PIN);
	while (1) {
		receive_status();	
	}
	return 0;
}
