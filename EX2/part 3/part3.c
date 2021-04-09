#include <mega32.h>
 #include <ctype.h>
 #include <string.h>
 #include <delay.h>

 #define c_row PORTA
 #define c_clom PORTB

 unsigned int speed=500;
 unsigned char R_data[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
 unsigned char Aa=0,locat;
 
 
 flash unsigned char A1_alephba[][8]={
 {0X18,0X3C,0X66,0X66,0X7E,0X66,0X66,0X00}, 
 {0X78,0X64,0X64,0X7C,0X7C,0X64,0X64,0X78}, 
 {0X04,0X3C,0X7C,0X64,0X60,0X60,0X7C,0X3C}, 
 
 flash unsigned char a0_alephba[][8]={
 {0X38,0X44,0X04,0X3C,0X44,0X44,0X3E,0X00}, 
 {0X20,0X20,0X20,0X38,0X24,0X24,0X38,0X00}, 
 {0X00,0X00,0X38,0X40,0X40,0X40,0X38,0X00}, 
 };
 
 flash char text1[]={"AaBbCcABCabc"};
                                       

    void lockup(char input){
        switch (input) {
            case 'a'  :
            locat=0;
            break;
            case 'b'  :
            locat=1;
            break;
            case 'c'  :
            locat=2;
            break;
        }; 
    }
    
    
    void refrash(){
     unsigned char i,d;
     unsigned int sp;
     sp=speed/16; if(sp<=0) sp=1;
     
        for(d=0; d<sp; d++){ 
            for(i=0; i<8; i++){ 
                c_row=R_data[i]; 
                if(Aa) c_clom=~A1_alephba[locat][i];
                else c_clom=~a0_alephba[locat][i];
                delay_ms(2);
            }
        }
    }
    
    

     
    void main(void){
        unsigned int len;
        unsigned char i;
        char c;
        
        PORTA=0x00;
        DDRA=0xFF;
        PORTB=0x00;
        DDRB=0xFF;
        
        while (1){
            len=strlenf(text1);  
            for(i=0; i<len; i++){
             c=text1[i];
                 if(islower(c)){
                    lockup(c);
                    Aa=0;
                 }else if(isupper(c)){
                    c=tolower(c);
                    lockup(c);
                    Aa=1;
                }
             refrash();
            }
            
        }
    }
