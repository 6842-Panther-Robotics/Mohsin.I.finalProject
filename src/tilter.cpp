#include "main.h"

using namespace pros;
//Sensor
ADIPotentiometer tilterPot('B');

//motor
Motor tilterMotor(6, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);

//PIDController instance
PIDController moveTilter(0.5, 40);

//variables for functions(can add more later if necessary)
int uprightPosition= 3000;
int tilterBackPosition=200;

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

//tilterOP functions
void score(){
  int time = 0;
  while (time <100){

    if (tilterPot.get_value()!=uprightPosition){
      tilter(moveTilter.getOutput(uprightPosition, tilterPot.get_value()));
    }
    if (fabs(moveTilter.getError()<5)){
      time=time +1;
    }
    else{
      brakeTilter();
      tilter(0);
    }
  }
}

void tilterBack(){
  int time = 0;
  while (time <100){

    if (tilterPot.get_value()!=uprightPosition){
      tilter(-moveTilter.getOutput(uprightPosition, tilterPot.get_value()));
    }
    if (fabs(moveTilter.getError()<5)){
      time=time +1;
    }
    else{
      brakeTilter();
      tilter(0);
    }
  }
  }

void tilterOP(){
  if (master.get_digital(DIGITAL_LEFT)){
    score();
  }
  if (master.get_digital(DIGITAL_Y)){
    tilterBack();
  }
  //this is just in case the score and tilter back functions somehow dont work in a match, this is how the user can take over
  if (master.get_digital(DIGITAL_UP)){
    tilter(60);
  }
  if (master.get_digital(DIGITAL_DOWN)){
    tilter(-127);
  }
  else{
    brakeTilter();
    tilter(0);
  }
}
