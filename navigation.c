#include <stdio.h>
#include <math.h>

// Robot navigation system code/pseudocode on a PIC microcontroller

// Function prototypes
void loop(const int perimeter_x, const int perimeter_y, double distance_travelled_y, 
    double distance_travelled_x, double side_distance);
void garbage_event();
void collection_mechanism();
int detect_garbage();

int main() {
    // Preset perimeter distance variables
    const int perimeter_y = 20; // Declare as a 20x20 square for now
    const int perimeter_x = 20;

    // Distance tracking variables
    double distance_travelled_y = 0;
    double distance_travelled_x = 0;

    // Observable camera distance (facing forward)
    const int observed_distance = 1;
    const double observed_angle = 0.785398163; // 45 degrees, TODO: import pi from math.h

    // Horizontal distance covered by camera
    double side_distance = cos(observed_angle) * observed_distance / sin(observed_angle);

    loop(perimeter_x, perimeter_y, distance_travelled_y, distance_travelled_x, side_distance);
    return 0;
}

// Preset path that the robot loops through
void loop(const int perimeter_x, const int perimeter_y, double distance_travelled_y, 
    double distance_travelled_x, double side_distance) {

    while(1) { // Infinite loop
        // NEED LOGIC: move_forward and track distance_travelled_y, distance_travelled_y

        if (distance_travelled_y == 0.8 * perimeter_y) {
            // NEED LOGIC: turn 90 degrees
            // NEED LOGIC: move_forward(side_distance)
            // NEED LOGIC: turn 90 degrees
        }
        
        if (distance_travelled_x == 0.8 * perimeter_x) {
            // NEED LOGIC: turn 90 degrees
            // NEED LOGIC: move_forward(perimeter_x)
            // NEED LOGIC: turn 90 degrees
        }

        if (detect_garbage()) {
            garbage_event(); // Calls garbage collection function if garbage detection flag == 1
        }
    }
}

// Garbage detection function
int detect_garbage() {
    // NEED LOGIC: garbage detection with machine learning
    // Set if statement to return 1 if true, otherwise function returns 0

    return 0;
}

// Garbage collection function
void garbage_event() {
    double event_distance_travelled; // Distance travelled to garbage
    double event_angle; // Angle adjusted to collect garbage (wrt original direction)

    // NEED LOGIC: travel to garbage, track and update event_distance_travelled and event_angle
    
    // NEED LOGIC: sweep (motors)
    __delay_ms(5000); // Delay 5 s
    // NEED LOGIC: rotate up (motors)
    __delay_ms(5000);
    // NEED LOGIC: rotate down (motors)

    // NEED LOGIC: reverse by distance event_distance_travelled
    // NEED LOGIC: turn by -event_angle
}

// Separate garbage collection function, call this in loop or main for testing purposes
void collection_mechanism() {
    // NEED LOGIC: sweep (motors)
    __delay_ms(5000); // Delay 5 s
    // NEED LOGIC: rotate up (motors)
    __delay_ms(5000);
    // NEED LOGIC: rotate down (motors)
}