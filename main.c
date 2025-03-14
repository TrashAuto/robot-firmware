
#include "config.h"
#include <xc.h>
#include <p24F16KA101.h>
//#include "I2C.h"
#include "PWM.h"
#include "ADC.h"
#include "clkchange.h"

#define Forwards 0
#define Backwards 1
#define Stop 3

uint8_t movement_state = 0;
uint8_t duty_cycle = 1;
uint16_t ADCval = 0;

void Timer1_init(void);
void Timer2_init(void);
void Timer3_init(void);

int main(void) {
    AD1PCFG = 0xFFFF; /* keep this line as it sets I/O pins that can also be analog to be digital */
    //data as output, output = 0
    LATBbits.LATB8 = 0;
    TRISBbits.TRISB8 = 0;
    newClk(8);
    Timer1_init();
    Timer3_init();
    PWM_Init();
    do_ADC();
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
    PADCFG1bits.OC1TRIS = 0;
    // turns on ADC
    AD1CON1bits.ADON = 1;
    AD1CON1bits.SAMP = 1;
    PR1 = 31250/10;
    /*
    // sets timer to 100Hz
    //Increments duty cycle and resets if >100
    if (duty_cycle > 100){
        duty_cycle = 0;
    }else{
        duty_cycle++;
    }
    */
    duty_cycle = ADCval/10;
    //OC1RS = (PR3 + 1) * duty_cycle / 100;
    OC1RS = 63 * duty_cycle / 100 + 63;
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void){
    //Don't forget to clear the timer 3 interrupt flag!
    IFS0bits.T2IF = 0;
    TMR2 = 0;
    
}

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void){
    //Don't forget to clear the timer 3 interrupt flag!
    //Used as timer for OC1
    IFS0bits.T3IF = 0;
    TMR3 = 0;
    
}
/*
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void){
    //Don't forget to clear the CN interrupt flag!
    IFS1bits.CNIF = 0;
}
*/

void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0; // Clear the ADC1 Interrupt Flag
    ADCval = ADC1BUF0; // reads the ADC value after conversion
    // Turns off adc
    AD1CON1bits.ADON = 0; 
    AD1CON1bits.SAMP = 0;
}

void Timer1_init(void){
    // Timer 2 setup
    T1CONbits.TCKPS = 2; // set prescaler to 1:64
    T1CONbits.TCS = 0; // use internal clock
    T1CONbits.TSIDL = 0; //operate in idle mode
    IPC0bits.T1IP = 2; //7 is highest and 1 is lowest pri.
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1; //enable timer interrupt
    T1CONbits.TON = 1;
    TMR1 = 0;
    PR1 = 31250;

}

void Timer2_init(void){
    // Timer 2 setup
    T2CONbits.TCKPS = 3; // set prescaler to 1:256
    T2CONbits.TCS = 0; // use internal clock
    T2CONbits.TSIDL = 0; //operate in idle mode
    IPC1bits.T2IP = 2; //7 is highest and 1 is lowest pri.
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1; //enable timer interrupt
    T2CONbits.TON = 1;
    T2CONbits.T32 = 0; // operate timer 2 as 16 bit timer
    TMR2 = 0;
    PR2 = 62500;
}

void Timer3_init(void){
    //T3CON config
    T2CONbits.T32 = 0; // operate timer 2 as 16 bit timer
    T3CONbits.TCKPS = 2; // set prescaler to 1:64
    T3CONbits.TCS = 0; // use internal clock
    T3CONbits.TSIDL = 0; //operate in idle mode
    IPC2bits.T3IP = 2; //7 is highest and 1 is lowest pri.
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 1; //enable timer interrupt
    PR3 = 1250; 
    TMR3 = 0;
    T3CONbits.TON = 1; 
}

//4 is forwards other is back
//control of angle and distance will be determined through communication with odometer
//maybe switch modes between manual and automatic
//look into how to interface with pi
void move_direction(uint8_t angle){
    LATBbits.LATB4 = 1;
    LATBbits.LATB7 = 0;
    LATAbits.LATA4 = 0;
    LATAbits.LATA2 = 1;
    OC1RS = (PR3 + 1) * angle;// + value of 0 degrees;

}

void move_forwards(uint8_t distance){
    LATBbits.LATB4 = 1;
    LATBbits.LATB7 = 1;
    LATAbits.LATA4 = 1;
    LATAbits.LATA2 = 1;
}

void move_backwards(uint8_t distance){
    LATBbits.LATB4 = 0;
    LATBbits.LATB7 = 0;
    LATAbits.LATA4 = 0;
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
    

    
    switch(movement_state){
        case(Stop):
            break;
            
        case(Forwards):
            move_forwards(distance);
            break;
            
        case(Backwards):
            move_backwards(distance);
            break;
    }     
}

// implements a delay with the timer
void delay_ms(uint16_t ms){
    uint16_t total = ms;
    //stores current PR2 value
    uint16_t holder = PR2;
    while(total>0){
        // if total ms is greater than 1000 it subtracts 1000 and loops again
        // mainly so there isn't integer overflow, PR2 is 16 bit
        if(total >= 4000){
            T2CONbits.TON = 1;
            //Calculation for 4s = 62500
            PR2 = 62500;
            total -= 4000;
        }else{
            //62500/4000 gives roughly 1ms
            T2CONbits.TON = 1;
            PR2 = (62500/4000) * total;
            total = 0;
        }
        Idle();
    }
    //returns PR2 value not sure if needed
    PR2 = holder;
}