#include <stdio.h>
#include <math.h>
#include <movement.h>
#include <bno055.h>

// Function prototypes
void loop(const int perimeter_x, const int perimeter_y);
void garbage_event();
void collection_mechanism();
int detect_garbage();
double get_distance();
double get_yaw();
void move(double distance); // Forward: +, backward: -
void turn(double angle); // Right: +, backward: -
void obstacle_event();

// Global variables
double distance_travelled_y = 0;
double distance_travelled_x = 0;
double current_angle = 0;

int main() {
    // Preset perimeter distance variables (20x20 square for now)
    const int perimeter_y = 20;
    const int perimeter_x = 20;

    BNO055_Init(); // Initialize IMU

    loop(perimeter_x, perimeter_y);
    return 0;
}

// Preset path that the robot loops through
void loop(const int perimeter_x, const int perimeter_y) {
    // Calculate horizontal distance in robot field of view
    const int observed_distance = 1;
    const double observed_angle = 0.785398163; // 45 degrees, TODO: import pi from math.h
    double side_distance = cos(observed_angle) * observed_distance / sin(observed_angle);

    while(1) {
        double distance = get_distance();
        current_angle = get_yaw();

        distance_travelled_x += distance * cos(current_angle * M_PI / 180);
        distance_travelled_y += distance * sin(current_angle * M_PI / 180);

        move(0.5);

        if (distance_travelled_y >= 0.8 * perimeter_y) {
            turn(90);
            move(side_distance * 2);
            turn(90);
        }
        
        if (distance_travelled_x >= 0.8 * perimeter_x) {
            turn(90);
            move(perimeter_x);
            turn(90);
        }

        if (detect_garbage()) {
            garbage_event();
        }

        if (detect_obstacle()) {
            obstacle_event();
        }
    }
}

// Garbage collection event
void garbage_event() {
    // Travel to garbage
    turn(45); // Assumed angle, figure out how to get this angle from cameras
    move(2.0); // Assumed distance, figure out how to get this angle from cameras
    
    // Collect garbage
    collection_mechanism(); // Actual function should be defined elsewhere

    // Return to original path
    move(-2.0);
    turn(-45);
}

// Obstacle avoidance event
void obstacle_event() {
    // Go right and drive around obstacle (assumed distances)
    turn(90);
    move(3.0);
    turn(-90);
    move(3.0);
    turn(-90);
    move(3.0);
    turn(90);
}

int detect_garbage() {
    // Garbage detection ML logic
    return 0;
}

int detect_obstacle() {
    // Obstacle detection ML logic
    return 0;
}