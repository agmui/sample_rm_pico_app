#include "rm_pico_dev/src/algorithms/smooth_pid.hpp"
#include "rm_pico_dev/include/board.h"
//#include "rm_pico_dev/src/architecture/periodic_timer.hpp"
#include "rm_pico_dev/include/DjiMotor.h"
#include <cmath>
#include <iostream>
#include <string>

pico::Drivers *drivers = new pico::Drivers();

void initialize() {
    Board::initialize();
    drivers->can.initialize();
    drivers->remote.initialize();
    drivers->bmi088.initialize(500, 0.0, 0.0);

    //TODO: Include ThornBots classes and initialize them
}