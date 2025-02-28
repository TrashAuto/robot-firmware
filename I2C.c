/*
 * File:   I2C.c
 * Author: willi
 *
 * Created on January 22, 2025, 10:30 AM
 */


#include <p24F16KA101.h>


void initI2C(void) {
    I2C1CONbits.I2CEN = 1;
    I2C1CONbits.I2CSIDL = 0;
    // configures SMB bus delay
    PADCFG1bits.SMBUSDEL = 0;
    // turns on interrupts for slave and master
    IEC1bits.MI2C1IE = 1;
    IEC1bits.SI2C1IE = 1;

}

void I2C_Clock_Rate(uint16_t khz){
    //For 8mhz clock speed
    //Values from datasheet table 17-1
    switch(khz){
        // Actual Fscl = 100khz
        case(100):
            I2C1BRG = 0x4E;
            break;
        // Actual Fscl = 404khz
        case(400):
            I2C1BRG = 0x12;
            break;
        // Actual Fscl = 1.026Mhz
        case(1000):
            I2C1BRG = 0x06;
            break;    
    }


}


void Start_I2C (uint8_t address){
    
}


void __attribute__((interrupt, no_auto_psv)) _MI2CInterrupt(void){
    //Don't forget to clear the timer 1 interrupt flag!
    IFS1bits.MI2C1IF = 0;
    
}

void __attribute__((interrupt, no_auto_psv)) _SI2CInterrupt(void){
    //Don't forget to clear the timer 1 interrupt flag!
    IFS1bits.SI2C1IF = 0;
    
}