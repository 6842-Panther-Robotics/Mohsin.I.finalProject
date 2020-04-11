#include "main.h"

using namespace pros;

//sensors
Imu inertial(9);

//motors
Motor rightFront(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor leftFront(3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor rightBack(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor leftBack(4, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

//helper functions
void wait(int time){
  delay(time);
}

void right(int speed){
  rightFront.move(speed);
  rightBack.move(speed);
}

void left(int speed){
  leftFront.move(speed);
  leftBack.move(speed);
}

void timedDrive(int time, int speed){
  right(speed);
  left(speed);
  wait(time);
  right(0);
  left(0);

}

void brake(){
  rightFront.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  leftFront.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  rightBack.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  leftBack.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void coast(){
  rightFront.set_brake_mode(E_MOTOR_BRAKE_COAST);
  leftFront.set_brake_mode(E_MOTOR_BRAKE_COAST);
  rightBack.set_brake_mode(E_MOTOR_BRAKE_COAST);
  leftBack.set_brake_mode(E_MOTOR_BRAKE_COAST);
}

//driveOP
void driveOP(){
  rightFront.move(master.get_analog(ANALOG_RIGHT_Y));
  leftFront.move(master.get_analog(ANALOG_LEFT_Y));
  rightBack.move(master.get_analog(ANALOG_RIGHT_Y));
  leftBack.move(master.get_analog(ANALOG_LEFT_Y));
}
