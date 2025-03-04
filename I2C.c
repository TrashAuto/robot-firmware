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
    
}

void I2C_Clock_Rate(uint8_t khz){
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
