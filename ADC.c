

#include <p24F16KA101.h>

void do_ADC(void){
    // Auto converts (SW controlled) 
    AD1CON1bits.SSRC = 7;
    // Sampling begins after SAMP is set
    AD1CON1bits.ASAM = 0;
    AD1CON1bits.FORM = 0;
    //Sets voltage reference to VR+ for VDD and VR- to VSS
    AD1CON2bits.VCFG = 0;
    //Do not scan inputs for MUXA
    AD1CON2bits.CSCNA = 0;
    //Interrupts happen after each sample and conversion sequence
    AD1CON2bits.SMPI = 0;
    AD1CON2bits.BUFM = 0;
    //use mux A
    AD1CON2bits.ALTS = 0;
    // clock from system clock
    AD1CON3bits.ADRC = 0;
    //Slowest sampling time 31*2/fclk
    AD1CON3bits.SAMC = 31;
    //Channel 0 neg input is VR
    AD1CHSbits.CH0NA = 0;
    //Channel 0 is AN5
    AD1CHSbits.CH0SA = 5;
    //Sets AN5 to analog
    AD1PCFGbits.PCFG5 = 0;
    AD1CSSL = 0;
    
    //Enables ADC interrupt
    IPC3bits.AD1IP = 3;
    IEC0bits.AD1IE = 1;
    // Turns ADC on
    AD1CON1bits.ADON = 1;
    AD1CON1bits.SAMP = 1;
}   