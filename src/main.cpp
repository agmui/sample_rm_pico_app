#include <iostream>
#include "pico/stdlib.h" // the pico-sdk lib
#include <stdio.h>
#include "DriveTrainCoNtroller.h"
#include "TurretController.h"

//NOTE: icecream mutexes are turned off
// #include "icecream.hpp"//TODO: Make so it only happens for debug build

int main(int argc, char const *argv[])
{
    stdio_init_all();// allows printing to terminal

    gpio_init(25);// init pin 25(the led)
    gpio_set_dir(25, GPIO_OUT);//set pin 25 to output
    auto* drivers = new pico::Drivers(); //TODO: get singleton
    auto *tc = new ThornBots::TurretController(drivers);

    while (1)
    {
        // IC();
        //print hello world
        std::cout << "hello world" << std::endl;
        tc->startShooting();

        // Turn On LED
        gpio_put(25, 1); // Set pin 25 to high
        sleep_ms(250);//wait for 250 ms
        printf("LED switched on!\n");// print 
        // Turn Off LED
        gpio_put(25, 0); // Set pin 25 to high.
        sleep_ms(250);
        printf("LED switched off!\n");

    }
}