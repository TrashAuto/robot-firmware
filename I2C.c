/*
 * File:   I2C.c
 * Author: willi
 *
 * Created on January 22, 2025, 10:30 AM
 */

#include <xc.h>
#include <p24F16KA101.h>

uint16_t navigation_data[4] = {0,0,0,0};

void initI2C(void) {
    I2C1CONbits.I2CEN = 1;
    I2C1CONbits.I2CSIDL = 0;
    // configures SMB bus delay 
    PADCFG1bits.SMBUSDEL = 0;
    // turns on interrupts for slave and master
    IEC1bits.SI2C1IE = 1;
    //sets I2C1ADD as 7bit slave address
    I2C1CONbits.A10M = 0;
    //sets the I2C Slave address
    I2C1ADD = 0x3F;
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
//Not sure if this is needed
void Slave_I2C (void){
    uint8_t pass = 0;
}


#define Address 0
#define Data 1
uint8_t slave_state = 0;
uint8_t received_byte = 0;
//States would be nice in naming but implementing rn is bad
#define Byte1 0
#define Byte2 1
#define Byte3 2
#define Byte4 3
//note down interrupt conditions

void __attribute__((interrupt, no_auto_psv)) _SI2C1Interrupt(void){
    //Don't forget to clear the timer 1 interrupt flag!
    IFS1bits.SI2C1IF = 0;
    if(I2C1STATbits.D_A == Address){
        slave_state = Address;
        recieved_byte = 0;
    }else if (I2C1STATbits.D_A == Data && received_byte < 4){
        slave_state = Data;
        navigation_data[Byte1 + received_byte] = I2C1RCV
        received_byte += 1;
    }
}

/*
 * #define Left 1
 * #define Center 2
 * #define Right 3
 * 
 void I2C_data_decoder(void){
 * Switch(navigation_data[1]){
 *      case(Left):
 *          direction = -1;
 *          break;
 *      case(Center):
 *          direction = 0;
 *          break;
 *      case(Right):
 *          direction = 1;
 *          break;
 * }
 * angle = navigation_data[2]; //Add math after
 * distance = navigation_data[3]; //Add distance tracker
 * if (navigation_data[0] == STOP){
 *      stop_movement();
 * }
 }
 */