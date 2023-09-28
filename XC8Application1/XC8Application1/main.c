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
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
void uart_putchar(char c) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}
char uart_getchar() {
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}
void receive_status() {
	uint8_t i = 0;
while (i < (BUFFER_SIZE - 1)) {
	char received_char = uart_getchar();
		received_status[i++] = received_char;
		received_status[i] = '\0'; 
		if (strcmp(received_status, "code_ok") == 0) {
			PORTB |= (1 << LED_PIN);
			break; 
		}
	}
5}
int main() {
	uart_init;
	DDRB |= (1 << LED_PIN);
	while (1) {
		receive_status();	
	}
	return 0;
}
