#include "main.h"

using namespace pros;

//sensors
ADIPotentiometer liftPot('A');

//motors
Motor liftMotor(5, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);

//helper functions
void lift(int speed){
  liftMotor.move_velocity(speed);
}

void moveLiftTime(int time, int speed){
  lift(speed);
  wait(time);
  lift(0);
}

void brakeLift(){
  liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void coastLift(){
  liftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
}

//liftOP
void liftOP(){
  if (master.get_digital(DIGITAL_L1)){
    liftMotor.move_velocity(127);
  }
  if (master.get_digital(DIGITAL_L2)){
    liftMotor.move_velocity(-127);
  }
  else{
    liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    liftMotor.move_velocity(0);
  }
}
