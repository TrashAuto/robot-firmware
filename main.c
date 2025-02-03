/*
 * File:   main.c
 * Author: William,
 *
 * Created on: USE THE INFORMATION FROM THE HEADER MPLAB X IDE GENERATES FOR YOU
 */

// FBS
#pragma config BWRP = OFF               // Table Write Protect Boot (Boot segment may be written)
#pragma config BSS = OFF                // Boot segment Protect (No boot program Flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Code Flash Write Protection bit (General segment may be written)
#pragma config GCP = OFF                // General Segment Code Flash Code Protection bit (No protection)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Select (Fast RC oscillator (FRC))
#pragma config IESO = OFF               // Internal External Switch Over bit (Internal External Switchover mode disabled (Two-Speed Start-up disabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = ON            // CLKO Enable Configuration bit (CLKO output disabled; pin functions as port I/O)
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8 MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary oscillator configured for high-power operation)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor Selection (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (WDT prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected; windowed WDT disabled)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware; SBOREN bit disabled)
#pragma config PWRTEN = ON              // Power-up Timer Enable bit (PWRT enabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Default location for SCL1/SDA1 pins)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (1.8V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (MCLR pin enabled; RA5 input pin disabled)

// FICD
#pragma config ICS = PGx2               // ICD Pin Placement Select bits (PGC2/PGD2 are used for programming and debugging the device)

// FDS
#pragma config DSWDTPS = DSWDTPSF       // Deep Sleep Watchdog Timer Postscale Select bits (1:2,147,483,648 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select bit (DSWDT uses LPRC as reference clock)
#pragma config RTCOSC = SOSC            // RTCC Reference Clock Select bit (RTCC uses SOSC as reference clock)
#pragma config DSBOREN = ON             // Deep Sleep Zero-Power BOR Enable bit (Deep Sleep BOR enabled in Deep Sleep)
#pragma config DSWDTEN = ON             // Deep Sleep Watchdog Timer Enable bit (DSWDT enabled)

// #pragma config statements should precede project file includes.

#include <xc.h>
#include <p24F16KA101.h>

#define Stop 0
#define Left 1
#define Forwards 2
#define Backwards 3
#define Right 4

uint8_t movement_state = 0;

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

//4 is forwards other is back
//control of angle and distance will be determined through communication with odometer
//maybe switch modes between manual and automatic
//look into how to interface with pi
void move_left(uint8_t angle){
    LATBbits.LATB4 = 1;
    LATBbits.LATB7 = 0;
    LATAbits.LATA4 = 0;
    LATAbits.LATA2 = 1;
}

void move_forwards(uint8_t distance){
    LATBbits.LATB4 = 1;
    LATBbits.LATB7 = 0;
    LATAbits.LATA4 = 1;
    LATAbits.LATA2 = 0;
}

void move_backwards(uint8_t distance){
    LATBbits.LATB4 = 0;
    LATBbits.LATB7 = 1;
    LATAbits.LATA4 = 0;
    LATAbits.LATA2 = 1;
}

void move_right(uint8_t angle){
    LATBbits.LATB4 = 0;
    LATBbits.LATB7 = 1;
    LATAbits.LATA4 = 1;
    LATAbits.LATA2 = 0;
}


void movement(void){
    uint8_t angle = 0;
    uint8_t distance = 0;
    
    if (distance > 1){
        movement_state = Forwards;
    }else if (distance < -1){
        movement_state = Backwards;
    }
    
    if (angle > 1){
        movement_state = Right;
    }else if (angle < -1){
        movement_state = Left;
    }
    
    switch(movement_state){
        case(Stop):
            break;
        case(Left):
            move_left(angle);
            break;
            
        case(Right):
            move_right(angle);
            break;
            
        case(Forwards):
            move_forwards(distance);
            break;
            
        case(Backwards):
            move_backwards(distance);
            break;
    }     
}