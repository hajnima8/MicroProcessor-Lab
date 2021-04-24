#include 
#include 
#include 
#include "config.h" 
#include "I2C.h"  
#include"RTC.h"  
#define digit1 PORTCbits.RC0
#define digit2 PORTCbits.RC1
#define digit3 PORTCbits.RC2
#define digit4 PORTCbits.RC5
char H1,M1; 
char DH1,DH2,DM1,DM2;   
unsigned char hexvalue[10]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned int i ,j;
int main(){
   unsigned int i ,j;        
    TRISD=0;         
    TRISC=0;
    digit1 = 1; 
    digit2 = 1; 
    digit3 = 1; 
    digit4 = 1; 
    InitI2C();  
      
    Set_DS1307_RTC_Time(AM_Time,11, 28, 59);
    
    Set_DS1307_RTC_Date(30,8,20, Sunday`);  
    while(1)
    {  
    Read_Bytes_From_DS1307_RTC(0x00, pRTCArray, 3); 
	M1 = pRTCArray[1];
	pRTCArray[1] = (M1>>4)*10 + (M1&0x0F); 
	if(pRTCArray[2]&0x40)	
	{
		if(pRTCArray[2]&0x20)	
			pRTCArray[3] = PM_Time;
		else		
			pRTCArray[3] = AM_Time;

		H1 = pRTCArray[2];
		pRTCArray[2] = ((H1&0x1F)>>4)*10 + (H1&0x0F);
	}
	else		
	{
		H1 = pRTCArray[2];
		pRTCArray[2] = (H1>>4)*10 + (H1&0x0F);
		pRTCArray[3] = TwentyFourHoursMode;
    }
      DH1= (pRTCArray[2]/10)+0x30; 
      DH2= (pRTCArray[2]%10)+0x30; 
      DM1= (pRTCArray[1]/10)+0x30; 
      DM2= (pRTCArray[1]%10)+0x30; 
	  unsigned char str1[5]; 
	  str1[0] = DH1;
      str1[1] = DH2;
      str1[2] = DM1; 
      str1[3] = DM2; 
      str1[5]="/0";
     i= atoi(str1);     
       unsigned int a1,a2,a3,a4;
            a1 = i / 1000;   
            a2 = ((i/100)%10); 
            a3 = ((i/10)%10);  
            a4 = (i%10);   
            
 PORTD=hexvalue[a1]; 
digit1=0;   
__delay_ms(1);
digit1=1;   
PORTD=hexvalue[a2];  
digit2=0;   
__delay_ms(1);
digit2=1;  
PORTD=hexvalue[a3];  
digit3 = 0;  
__delay_ms(1);
 digit3 = 1;   
PORTD=hexvalue[a4];  
digit4 = 0;  
__delay_ms(1);
digit4 = 1;  
 }         
}
