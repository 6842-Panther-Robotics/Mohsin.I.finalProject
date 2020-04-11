#include "main.h"

using namespace pros;
//Sensor
ADIPotentiometer tilterPot('B');

//motor
Motor tilterMotor(6, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);

//helper functions
void tilter(int speed){
  tilterMotor.move_velocity(speed);
}

void brakeTilter(){
  tilterMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void coastTilter(){
  tilterMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void moveTilterTime(int time, int speed){
  tilter(speed);
  wait(time);
  tilter(0);
}
