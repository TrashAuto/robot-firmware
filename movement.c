#include <movement.h>
#include <xc.h>
#include <p24F16KA101.h>

uint8_t movement_state = 0;

//4 is forwards other is back
//control of angle and distance will be determined through communication with odometer
//maybe switch modes between manual and automatic
//look into how to interface with pi

// Movement function definitions

void move_left(uint8_t angle) {
    LATBbits.LATB4 = 1;
    LATBbits.LATB7 = 0;
    LATAbits.LATA4 = 0;
    LATAbits.LATA2 = 1;
}

void move_forwards(uint8_t distance) {
    LATBbits.LATB4 = 1;
    LATBbits.LATB7 = 0;
    LATAbits.LATA4 = 1;
    LATAbits.LATA2 = 0;
}

void move_backwards(uint8_t distance) {
    LATBbits.LATB4 = 0;
    LATBbits.LATB7 = 1;
    LATAbits.LATA4 = 0;
    LATAbits.LATA2 = 1;
}

void move_right(uint8_t angle) {
    LATBbits.LATB4 = 0;
    LATBbits.LATB7 = 1;
    LATAbits.LATA4 = 1;
    LATAbits.LATA2 = 0;
}

void movement(void) {
    uint8_t angle = 0;
    uint8_t distance = 0;
    
    if (distance > 1) {
        movement_state = Forwards;
    }
    else if (distance < -1) {
        movement_state = Backwards;
    }
    
    if (angle > 1) {
        movement_state = Right;
    }
    else if (angle < -1) {
        movement_state = Left;
    }
    
    switch(movement_state) {
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