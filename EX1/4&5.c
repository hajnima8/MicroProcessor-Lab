#include <avr/io.h>


int main(void)
{
	char Reply=0;
    /* Replace with your application code */
	UCSR0B = (1<<4)|(1<<3);
	UCSR0C = (1<<2)|(1<<1);
	UBRR0L = 51;
	
    while (1) 
    {
		Reply = UDR0;
		UDR0 = Reply;	
    }
}