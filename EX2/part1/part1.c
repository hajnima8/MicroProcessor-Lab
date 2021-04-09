#include <mega16.h>
#include <lcd.h>
#include <stdio.h>
#include <delay.h>
#define xtal 8000000
#asm
   .equ __lcd_port=0x1B ;PORTA
#endasm
  unsigned char H=12,M=0,S=0;
  unsigned int Y=1389,MO=11,D=11;
  
  
    void date_calc(){
     unsigned int d;
     if(MO<=6) d=31;
     if(MO>=7) d=30;
     if(MO==12) d=29;
        D++;
        if(D>d){
         D=1;
         MO++;
          if(MO==13){
           MO=1;
           Y++;
          }
        }
    }
    
      
    interrupt [TIM2_OVF] void timer2_ovf_isr(void){
         S++;
       if(S==59){
        S=0;
        M++;
         if(M==59){
           M=0;
           H++;
            if(H==24){
             H=0;
             date_calc();
            }
         }
       }  
    }

   
 void main(void){
    char buffer[32];
    lcd_init(16);
    ASSR=0x08;   
    TCCR2=0x05; 
    TCNT2=0x00;
    OCR2=0x00;
    TIMSK=0x40; 
    #asm("sei")
    
    while (1){
    sprintf(buffer,"TIME %d:%d:%d\nDATE %d/%d/%d",H,M,S,Y,MO,D);
    lcd_clear(); 
    lcd_puts(buffer);
    delay_ms(300);
    }
 } 