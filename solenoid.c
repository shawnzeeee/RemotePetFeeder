#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GPIO_PATH "/sys/class/gpio"
#define GPIO_PIN "51"  // Pin 16 on the P9 header

// Function to export the GPIO pin
void export_gpio() {
    FILE *export_file = fopen(GPIO_PATH "/export", "w");
    if (export_file == NULL) {
        perror("Error exporting GPIO pin");
        exit(EXIT_FAILURE);
    }

    fprintf(export_file, "%s", GPIO_PIN);
    fclose(export_file);
}

// Function to unexport the GPIO pin
void unexport_gpio() {
    FILE *unexport_file = fopen(GPIO_PATH "/unexport", "w");
    if (unexport_file == NULL) {
        perror("Error unexporting GPIO pin");
        exit(EXIT_FAILURE);
    }

    fprintf(unexport_file, "%s", GPIO_PIN);
    fclose(unexport_file);
}

// Function to set the GPIO pin direction to "out"
void set_gpio_direction_out() {
    char direction_path[100];
    sprintf(direction_path, GPIO_PATH "/gpio%s/direction", GPIO_PIN);

    FILE *direction_file = fopen(direction_path, "w");
    if (direction_file == NULL) {
        perror("Error setting GPIO direction");
        exit(EXIT_FAILURE);
    }

    fprintf(direction_file, "out");
    fclose(direction_file);
}

// Function to set the GPIO pin value to 1
void pin_on() {
    char value_path[100];
    sprintf(value_path, GPIO_PATH "/gpio%s/value", GPIO_PIN);

    FILE *value_file = fopen(value_path, "w");
    if (value_file == NULL) {
        perror("Error setting GPIO pin value");
        exit(EXIT_FAILURE);
    }

    fprintf(value_file, "1");
    fclose(value_file);
}

// Function to set the GPIO pin value to 0
void pin_off() {
    char value_path[100];
    sprintf(value_path, GPIO_PATH "/gpio%s/value", GPIO_PIN);

    FILE *value_file = fopen(value_path, "w");
    if (value_file == NULL) {
        perror("Error setting GPIO pin value");
        exit(EXIT_FAILURE);
    }

    fprintf(value_file, "0");
    fclose(value_file);
}

/*int main() {
    // Export GPIO pin
    unexport_gpio();
    export_gpio();

    // Set GPIO pin direction to "out"
    set_gpio_direction_out();

    // Example: Turn the pin on for 3 seconds, then off
    pin_on();
    sleep(1);
    pin_off();

    return 0;
}*/