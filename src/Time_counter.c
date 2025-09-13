#include <xc.h>
#define _XTAL_FREQ 20000000
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF      // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF 
unsigned char j,i,k,l,temp=0,num1,num2,num3,num4,num5,num6,sum1,sum2,sum3, a,b,c,d,e,f,timer_count=0,pause=0;
unsigned int sec = 0,min = 0,stop,x,flag=0;
unsigned char seg[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x6F};
void interrupt timer_0()
{
    if(PIR1bits.RCIF==1)
    {
        x=RCREG;
        flag++;
        PIR1bits.RCIF=0;    }
   if( INTCONbits.TMR0IF==1)
   {
       if(timer_count>=4)
       {
           timer_count=0;       }
       if(timer_count==0)
       {
           PORTCbits.RC0=1;
           PORTCbits.RC1=0;
           PORTCbits.RC2=0;
           PORTCbits.RC3=0;
           PORTB=seg[l];       }
           if(timer_count==1)
       {
           PORTCbits.RC0=0;
           PORTCbits.RC1=1;
           PORTCbits.RC2=0;
           PORTCbits.RC3=0;
           PORTB=seg[k];       }
            if(timer_count==2)
       {    
           PORTCbits.RC0=0;
           PORTCbits.RC1=0;
           PORTCbits.RC2=1;
           PORTCbits.RC3=0;
           PORTB=seg[j];       }
            if(timer_count==3)
       {  
           PORTCbits.RC0=0;
           PORTCbits.RC1=0;
           PORTCbits.RC2=0;
           PORTCbits.RC3=1;
           PORTB=seg[i];       }
        timer_count++;
        INTCONbits.TMR0IF=0;
        TMR0=59;     }}
void main()
{
    TRISB=0x00;
    TRISD=0x30;
    TRISC=0x080;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    INTCONbits.TMR0IE=1;
    OPTION_REG=0x07;
    TMR0=59;
    PIE1bits.RCIE = 1;      // Enable USART receive interrupt
    TXSTA = 0x24;           // Transmit enabled, asynchronous mode
    RCSTA = 0x90;           // Serial port enabled, continuous receive enabled
    SPBRG = 129;
     while(1)
    {
         if(flag==1)
        {
            a=x;
            num1=a-'0' ;             }
        else if(flag==2)
        {
            b=x;
             num2=b-'0' ;         }
          else if(flag==3)
        {
              c=x;
               num3=c-'0' ;        }
          else if(flag==4)
        {
            d=x;
            num4=d-'0' ;        }
           else if(flag>5)
        {
            e=x;
            num5=e-'0' ;           
        }
        else if(flag==6)
        {
            f=x;
           num6=f-'0' ; 
            flag=0;        }
        sum1=(num1*10)+num2;
        sum2=(num3*10)+num4;
        sum3=(num5*10)+num6;      
        if(PORTDbits.RD4==1)
        {
            pause=1;        }
        else
        {
            pause=0;        }
        if(!pause)
        {
        l=(min/10)%10;
        k=min%10;
        j=(sec/10)%10;
        i=sec%10;
        if(PORTDbits.RD5==1)
        {
        if(sec==0 && min==0 )
           {
               sum1--;
               sec=60;
               min=sum1;          }           
         sec--;
            if(sec==0)
            {
                sec=60;
                min--;            }
            if(min==0)
            {
                min=sum1;            }        }
        else
        {
          if(sec==0 && min==0 && stop==0 )
            {
             sec=sum1;
             min=sum2;
             stop=sum3;            }
         sec++;
        if(sec==60)
        {
          sec=0;
            min++;        }
        if(min==stop)
        {
           min=0;  
               }        }
        __delay_ms(250);        }    }
    return;
}
