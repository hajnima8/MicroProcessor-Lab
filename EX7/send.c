
#include <mega16.h>
#include <delay.h>
#include <stdio.h>
 
void main(void){
UBRRH = 0x00;
UBRRL = 51;
UCSRA = 0x00;
UCSRB = 0x08;
UCSRC = 0x86;
 
    while(1){ 
    delay_ms(1000);
    putsf("nima");
    delay_ms(1000);
    putsf("Hello");
    }
}