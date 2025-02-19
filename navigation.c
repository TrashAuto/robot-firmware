#include <stdio.h>

// Pseudocode for robot navigation system

// Preset perimeter distance variables
float perimeter_y;
float perimeter_x;

// Distance tracking variables
float distance_travelled_y;
float distanced_travelled_x;

// Observable camera distance (facing forward)
float observed_distance;
float observed_angle;

// Horizontal distance covered by camera
float side_distance = cos(observed_angle) * observed_distance / sin(observed_angle)

// Default function - preset path that the robot loops through
void default() {
    // move_forward (track distance_travelled_y, distance_travelled_y)

    if (distance_travelled_y = 0.8 * perimeter_y) {
        // turn 90 degrees
        // move_forward(side_distance)
        // turn 90 degrees
    }

    if (distance_travelled_x = 0.8 * perimeter_x) {
        // turn 90 degrees
        // move_forward(perimeter_x)
        // turn 90 degrees
    }
}

// Garbage detection function
void garbage_event() {
    // var_distance: distance travelled to garbage
    // var_angle: angle adjusted to collect garbage (wrt original direction)

    // travel to garbage
    collection_mechanism()

    // reverse var_distance
    // turn -var_angle
}

// Garbage collection function
void collection_mechanism() {
    // sweep
    // delay(5s)
    // rotate motor up
    // delay(5s)
    // rotate motor down
}