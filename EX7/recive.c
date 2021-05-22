#include <mega16.h>
#include <delay.h>
#include <stdio.h>
#include <alcd.h>
unsigned char Array[17];
 
void main(void){
lcd_init(16);
lcd_clear();
UBRRH = 0;
UBRRL = 51;
UCSRA = 0x00;
UCSRB = 0x10;
UCSRC = 0x86;
 
    while(1){
    gets(Array,15);
    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_puts(Array);
    gets(Array,6);
    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_puts(Array);
    }
}