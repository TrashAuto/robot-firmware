/*
 * File:   main.c
 * Author: William,
 *
 * Created on: USE THE INFORMATION FROM THE HEADER MPLAB X IDE GENERATES FOR YOU
 */

#include <xc.h>
#include <p24F16KA101.h>
#include <config.h>

int main(void) {
    AD1PCFG = 0xFFFF; /* keep this line as it sets I/O pins that can also be analog to be digital */
    //data as output, output = 0
    LATBbits.LATB8 = 0;
    TRISBbits.TRISB8 = 0;
    
    //data is input, turn on pull up resistor, enable CN interrupts
    TRISAbits.TRISA4 = 0;
    //CNPU1bits.CN0PUE = 1;
    CNEN1bits.CN0IE = 1;
    
    TRISBbits.TRISB4 = 0;
    //CNPU1bits.CN1PUE = 1;
    CNEN1bits.CN1IE = 1;
    
    TRISAbits.TRISA2 = 0;
    //CNPU2bits.CN30PUE = 1;
    CNEN2bits.CN30IE = 1;
    
    TRISBbits.TRISB7 = 0;
    //CNPU2bits.CN23PUE = 1;
    CNEN2bits.CN23IE = 1;
    
    // set CN interrupt, priority, clear flag, and enable cn interrupts
    IPC4bits.CNIP = 7;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
    int i = 0;
    while(1) { 
        if (i != 0){
            i = 0;
        }else{
            Idle();
        } 
     
    }
    
    return 0;
}
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void){
    //Don't forget to clear the timer 1 interrupt flag!
    IFS0bits.T1IF = 0;
}

/*
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void){
    //Don't forget to clear the CN interrupt flag!
    IFS1bits.CNIF = 0;
}
*/
void Timer1_init(void){
    // Timer 2 setup
    T1CONbits.TCKPS = 1; // set prescaler to 1:8
    T1CONbits.TCS = 0; // use internal clock
    T1CONbits.TSIDL = 0; //operate in idle mode
    IPC0bits.T1IP = 2; //7 is highest and 1 is lowest pri.
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1; //enable timer interrupt
    T1CONbits.TON = 1;
    TMR1 = 0;
    PR1 = 31250;
}