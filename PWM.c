/*
 * File:   PWM.c
 * Author: willi
 *
 * Created on February 27, 2025, 11:30 PM
 */


#include "xc.h"

void PWM_Init(void) {
    PR3 = 16; // Calculated PR3 value for desired frequency

    OC1RS = 0; // Start with 0% duty cycle
    OC1R = 0;  // Initial duty cycle value

    OC1CONbits.OCM = 0b110; // PWM mode on OC1, Fault pin disabled
    OC1CONbits.OCTSEL = 1;  // Use Timer3 as the clock source
    //AD1PCFGbits.PCFG14 = 0; 
    PADCFG1bits.OC1TRIS = 0; // Enable OC1
    //Makes sure LED is on during idle
}
