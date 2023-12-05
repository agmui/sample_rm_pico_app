#pragma once
#include "rm_pico_dev/src/algorithms/smooth_pid.hpp"
#include "rm_pico_dev/include/board.h"
#include <cmath>
#include <drivers.h>
#include <iostream>
#include <string>
//#include "rm_pico_dev/src/architecture/periodic_timer.hpp"
#include "rm_pico_dev/include/DjiMotor.h"
#include <cmath>
#include "Core.h"

static pico::algorithms::SmoothPidConfig pid_conf_dt = { 20, 0, 0, 0, 8000, 1, 0, 1, 0, 0, 0 };
static constexpr float REFINED_ANGLE_OFFSET = 110.0f;


namespace ThornBots {
    class DriveTrainController {
    public:
        DriveTrainController(pico::Drivers* driver);
        ~DriveTrainController();
        void setMotorValues(bool useWASD, bool doBeyblading, double right_stick_vert, double right_stick_horz, double left_stick_vert, double left_stick_horz, std::string input, float yaw_angle);
        void setMotorSpeeds(bool sendMotorTimeout);
        void stopMotors(bool sendMotorTimeout);
        pico::motor::DjiMotor motor_one = pico::motor::DjiMotor(drivers, pico::motor::MotorId::MOTOR1, pico::can::CAN_BUS0, true, "ID1", 0, 0);
        pico::motor::DjiMotor motor_four = pico::motor::DjiMotor(drivers, pico::motor::MotorId::MOTOR4, pico::can::CAN_BUS0, false, "Call 858-267-8107 for a good time!", 0, 0);


    private:
        //START getters and setters
        inline int getMotorOneSpeed() { return motor_one_speed; }
        inline int getMotorTwoSpeed() { return motor_two_speed; }
        inline int getMotorThreeSpeed() { return motor_three_speed; }
        inline int getMotorFourSpeed() { return motor_four_speed; }
        inline void setMotorOneSpeed(int speed) { motor_one_speed = speed; }
        inline void setMotorTwoSpeed(int speed) { motor_two_speed = speed; }
        inline void setMotorThreeSpeed(int speed) { motor_three_speed = speed; }
        inline void setMotorFourSpeed(int speed) { motor_four_speed = speed; }
        inline int getTranslationSpeed() { return translation_speed; }
        inline int getRotationSpeed() { return rotation_speed; }
        inline int getBeybladingSpeed() { return beyblading_speed; }
        inline void setTranslationSpeed(int speed) { translation_speed = speed; }
        inline void setRotationSpeed(int speed) { rotation_speed = speed; }
        inline void setBeybladingSpeed(int speed) { beyblading_speed = speed; }
        inline int getMaxSpeed() { return max_speed; }
        //STOP getters and setters

        int getMotorOneSpeedWithCont(bool doBeyblading, double right_stick_vert, double right_stick_horz, double left_stick_vert, double left_stick_horz);
        int getMotorTwoSpeedWithCont(bool doBeyblading, double right_stick_vert, double right_stick_horz, double left_stick_vert, double left_stick_horz);
        int getMotorThreeSpeedWithCont(bool doBeyblading, double right_stick_vert, double right_stick_horz, double left_stick_vert, double left_stick_horz);
        int getMotorFourSpeedWithCont(bool doBeyblading, double right_stick_vert, double right_stick_horz, double left_stick_vert, double left_stick_horz);
        int getMotorSetOneTranslatingSpeed(double xPosition, double yPosition);
        int getMotorSetTwoTranslatingSpeed(double xPosition, double yPosition);
        double getAngle(double xPosition, double yPosition);
        double getMagnitude(double xPosition, double yPosition);
        double getScaledQuadratic(double magnitude);

        //float power_limit;
        float yaw_motor_angle = 0.0f;
        int motor_one_speed = 0; //Driver's front
        int motor_two_speed = 0; //Passenger's front
        int motor_three_speed = 0; //Driver's back
        int motor_four_speed = 0; //Passenger's back
        int translation_speed, rotation_speed, beyblading_speed = 0;
        int max_speed = 9500; //The abs(maximum speed) we want the drivetrain motors to go to
        double beyblading_factor = 0.5; //How much of the max_speed beyblading will eat up while robot is not translating range this from [0, 1]
        static constexpr double PI = 3.14159; //Everyone likes Pi!
        bool use_exponentional_controlling = true;
        pico::Drivers *drivers;
        pico::motor::DjiMotor motor_two = pico::motor::DjiMotor(drivers, pico::motor::MotorId::MOTOR2, pico::can::CAN_BUS0, false, "PURDON'T!", 0, 0);
        pico::motor::DjiMotor motor_three = pico::motor::DjiMotor(drivers, pico::motor::MotorId::MOTOR3, pico::can::CAN_BUS0, true, "Put the possum in his room", 0, 0);
        pico::algorithms::SmoothPid pidController = pico::algorithms::SmoothPid(pid_conf_dt);

    };
}