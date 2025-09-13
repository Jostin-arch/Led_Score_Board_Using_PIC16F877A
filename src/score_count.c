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
unsigned char score1=0;
unsigned char score2=0;
unsigned char i,j,k,l;
unsigned char seg[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x6F};
unsigned char x,y;
void main()
{
    TRISB=0x00;
    TRISC=0x30;
    TRISD=0x00;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    INTCONbits.INTE=1;
    OPTION_REGbits.INTEDG=1;
    while(1)
    {
        if(PORTCbits.RC4==1)     
        {
            score1++;
           __delay_ms(500);
           if(score1==99)
           {
               score1=0;
           }
            x=score1;
        }
        score1=x;
        if(PORTCbits.RC5==1)
        {
            score2++;
           __delay_ms(500);
           if(score2==99)
           {
               score2=0;
           }
            y=score2;
        }
        score2=y;
    i=score1/10;
    j=score1%10;
    k=score2/10;
    l=score2%10;
    PORTCbits.RC0=1;
    PORTCbits.RC1=0;
    PORTB=seg[i];
    __delay_ms(1);
    PORTCbits.RC0=0;
    PORTCbits.RC1=1;
    PORTB=seg[j];
    __delay_ms(1);
    PORTCbits.RC2=1;
    PORTCbits.RC3=0;
    PORTD=seg[k];
    __delay_ms(1);
    PORTCbits.RC2=0;
    PORTCbits.RC3=1;
    PORTD=seg[l];
    __delay_ms(1); 
}
    return;
}