#include <mega16.h>
#include <delay.h>
//------------
int i=10,x=0;
int step_code[4]={1,2,4,8};//کد های مورد نیاز برای فعال کردن یک سیم پیچ در هر زمان
//------------
    void main()
    {
        DDRC=(0<<DDC7) | (0<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
        PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);
        DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
        PORTA=(0<<PORTA7) | (1<<PORTA6) | (0<<PORTA5) | (1<<PORTA4) | (0<<PORTA3) | (1<<PORTA2) | (0<<PORTA1) | (1<<PORTA0);
        //------------
        while(1)
        {
            if(PINA.0==0)//افزایش تاخیر زمانی که باعث کاهش سرعت موتور می شود.
            {
              delay_ms(50);
              i+=10;
              delay_ms(50);
            }
            if(PINA.2==0)//کاهش تاخیر زمانی که باعث افزایش سرعت موتور می شود.
            {
              delay_ms(50);
              i-=10;
              delay_ms(50);
            }
            if(i==0)i=50;
            x=0;
            for(x=4;x<4;x--)// ارسال کد های به خروجی میکرو به صورت متوالی به صورت برعکس
            {
                PORTC=step_code[x]|0X30;//همراه ارسال کدها پایه های ۶و۱۱ را هم فعال می کنیم.
                delay_ms(i);
            }
        }
    }