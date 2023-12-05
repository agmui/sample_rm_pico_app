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

static pico::algorithms::SmoothPidConfig pid_conf_turret = { 20, 0, 0, 0, 8000, 1, 0, 1, 0, 0, 0 };
static pico::algorithms::SmoothPidConfig pid_yaw_conf = { 130, 0, -25000, 0, 1000000, 1, 0, 1, 0, 0, 0 };    //{ 90, 10, 30, 1, 1000000, 1, 0, 1, 0, 0, 0 };
static pico::algorithms::SmoothPidConfig pid_pitch_conf = { 400, 0.06, 80, 1500, 1000000, 1, 0, 1, 0, 0, 0 };
namespace ThornBots {
    class TurretController {
    public:
        TurretController(pico::Drivers* driver);
        ~TurretController();
        void setMotorValues(bool useWASD, bool doBeyblading, double angleOffset, double right_stick_vert, double right_stick_horz, int motor_one_speed, int motor_four_speed, float target_angle);
        void setMotorSpeeds(bool sendMotorTimeout);
        void stopMotors(bool sendMotorTimeout);
        void startShooting();
        void stopShooting();
        void reZero();
        float getYawEncoderAngle();

    private:
        //START getters and setters
        inline int getMotorYawSpeed() { return motor_yaw_speed; }
        inline int getMotorPitchSpeed() { return motor_pitch_speed; }
        inline int getMotorIndexerSpeed() { return motor_indexer_speed; }
        inline int getFlywheelSpeed() { return flywheel_speed; }
        inline int getMotorPitchMaxSpeed() { return motor_pitch_max_speed; }
        inline int getMotorYawMaxSpeed() { return motor_yaw_max_speed; }
        inline int getFlywheelMaxSpeed() { return flywheel_max_speed; }
        inline int getMotorIndeerMaxSpeed() { return motor_indexer_max_speed; }
        inline void setMotorYawSpeed(int speed) { motor_yaw_speed = speed; }
        inline void setMotorPitchSpeed(int speed) { motor_pitch_speed = speed; }
        inline void setMotorIndexerSpeed(int speed) { motor_indexer_speed = speed; }
        inline void setFlywheelSpeed(int speed) { flywheel_speed = speed; }
        //STOP getters and setters

        static constexpr int motor_yaw_max_speed = 500; //Not sure if this is the absolute maximum. need to test. Motor documentation says 320, but it can def spin faster than taproot's 320 rpm.
        static constexpr int motor_indexer_max_speed = 6000;
        static constexpr int flywheel_max_speed = 6700;
        static constexpr int motor_pitch_max_speed = 900;
        static constexpr int YAW_MOTOR_SCALAR = 500;
        bool isShooting = false;
        int motor_yaw_speed = 0;
        int flywheel_speed = 0;
        int motor_indexer_speed = 0;
        int motor_pitch_speed = 0;
        double current_yaw_angle = 180;

        int tmp = 0;

        static constexpr double PI = 3.14159; //Everyone likes Pi!
        pico::Drivers *drivers;
        int homemadePID(double value);
        int getYawMotorSpeed(double desiredAngle, double actualAngle, int motor_one_speed, int motor_two_speed);
        int getPitchMotorSpeed(bool useWASD, double right_stick_vert, double angleOffSet);
        int getIndexerMotorSpeed();
        int getFlywheelsSpeed();
        pico::motor::DjiMotor motor_yaw = pico::motor::DjiMotor(drivers, pico::motor::MotorId::MOTOR7, pico ::can::CAN_BUS0, false, "Have you seen The Bee Movie?", 0, 0);
        pico::motor::DjiMotor motor_pitch = pico::motor::DjiMotor(drivers, pico::motor::MotorId::MOTOR6, pico::can::CAN_BUS1, false, "Yellow black, yellow black. Ohhh lets spice things up a bit. Black yellow", 0, 0);
        pico::motor::DjiMotor motor_indexer = pico::motor::DjiMotor(drivers, pico::motor::MotorId::MOTOR7, pico::can::CAN_BUS1, false, "He has a pudding-bowl haircut, brown eyes and a sharp nose", 0, 0);
        pico::motor::DjiMotor flywheel_one = pico::motor::DjiMotor(drivers, pico::motor::MotorId::MOTOR8, pico::can::CAN_BUS1, true, "right flywheel", 0, 0);
        pico::motor::DjiMotor flywheel_two = pico::motor::DjiMotor(drivers, pico::motor::MotorId::MOTOR5, pico::can::CAN_BUS1, false, "left flywheel", 0, 0);
        pico::algorithms::SmoothPid pidController = pico::algorithms::SmoothPid(pid_conf_turret);
        pico::algorithms::SmoothPid yawPidController = pico::algorithms::SmoothPid(pid_yaw_conf);
        pico::algorithms::SmoothPid pitchPidController = pico::algorithms::SmoothPid(pid_pitch_conf);
    };
}