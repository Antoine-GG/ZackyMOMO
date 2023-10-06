/*
 * learning.cpp
 *
 * Created: 2023-10-06 13:52:12
 * Author : 1922250
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED1 5 

int main(void)
{
   DDRB |= (1 << LED1); //OUTPUT
   uint8_t clavier_status; 

   while(1) {
	   PORTB |= (1 << LED1);
	   if (clavier_status == 1) {
		   PORTB &= ~(1 << LED1); 
		   _delay_ms(500); 
		   PORTB |= (1 << LED1); 
	        }  
	       for(int i;i <= 2; i++) {
			   PORTB |= (1 << LED1); 
			   _delay_ms(500); 
			   PORTB &= ~(1 << LED1); 
  
    } 
  } 
}

