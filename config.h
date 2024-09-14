#pragma once

// uncomment to enable test mode to ensure all components working
//#define TEST_MODE

#define ROBOT_SPEED          20      // percentage of total speed
#define ROBOT_INIT_DELAY     3000    // how long to wait before initializing the robot (helps with putting it on the ground) 
#define ROBOT_MOVE_DELAY     0       // delay after issuing move commands, defines speed at which the main loop runs

// Servo motor pins
#define MOTOR_RIGHT_PIN       5      // left motor digital pin, swap with below if the robot is going in reverse
#define MOTOR_LEFT_PIN        4      // right motor digital pin, swap with above if the robot is going in reverse
#define MOTOR_MIN_PERCENT     0      // minimum speed percent where motors spin

// TCRT5000 IR sensor
#define IRSENSOR_LEFT_PIN       1      // left IR sensor
#define IRSENSOR_RIGHT_PIN      0      // right IR sensor
#define IRSENSOR_DELTA_THRESH   5        // how much change from base to detect black line
#define IRSENSOR_READ_WINDOW    10  // how many values to average
#define IRSENSOR_RECALIBERATION 10000     // recaliberate after this many reads