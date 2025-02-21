// Testing I2C communication between Raspberry Pi and PIC by blinking an LED
// Goal: Pi sends alternating 1 and 0 bits, turning the testing LED connected to the PIC on or off

#include <xc.h>

#define ADDRESS 0x08 // Same address as in Pi code

void I2C_Slave_Init() {
    SSPSTAT = 0x80;          // Slew rate control disabled
    SSPCON1 = 0x36;          // Enable I2C in slave mode
    SSPCON2 = 0x01;          // Enable clock stretching
    SSPADD = ADDRESS << 1;   // Set slave address
    SSPIF = 0;               // Clear interrupt flag
    SSPIE = 1;               // Enable I2C interrupt
    PEIE = 1;                // Enable peripheral interrupt
    GIE = 1;                 // Enable global interrupt
}

volatile uint8_t received_value = 0;  // Store received value from Pi

void __interrupt() I2C_Slave_ISR() {
    if (SSPIF) {                      // Interrupt flag raised
        if (!SSPSTATbits.R_nW) {      // Master is writing to slave (slave only reads if master is writing)
            received_value = SSPBUF;  // Read received byte (1 or 0)
            SSPIF = 0;                // Clear interrupt flag
        }
    }
}

// Initialize slave and blink LED on output RB0
void main() {
    I2C_Slave_Init();
    TRISBbits.TRISB0 = 0;

    while (1) {
        if (received_value == 1) {
            PORTBbits.RB0 = 1;
        } else {
            PORTBbits.RB0 = 0;
        }
    }
}