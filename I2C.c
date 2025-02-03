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
}
