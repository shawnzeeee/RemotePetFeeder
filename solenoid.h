#ifndef _SOLENOID_H_
#define _SOLENOID_H_

// Function to export the GPIO pin
void export_gpio();

// Function to unexport the GPIO pin
void unexport_gpio();

// Function to set the GPIO pin direction to "out"
void set_gpio_direction_out();

// Function to set the GPIO pin value to 1
void pin_on();

// Function to set the GPIO pin value to 0
void pin_off();

#endif