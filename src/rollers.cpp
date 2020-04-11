#include "main.h"

using namespace pros;

Motor leftRoller(8, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor rightRoller(8, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

//helper functions
void rollers(int speed){
  leftRoller.move_velocity(speed);
  rightRoller.move_velocity(speed);
}

void brakeRollers(){
  leftRoller.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  rightRoller.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void coastRollers(){
  leftRoller.set_brake_mode(E_MOTOR_BRAKE_COAST);
  rightRoller.set_brake_mode(E_MOTOR_BRAKE_COAST);
}

void moveRollersTime(int time, int speed){
  rollers(speed);
  wait(time);
  rollers(0);
}

//rollerOP
void rollersOP(){
  if (master.get_digital(DIGITAL_R1)){
    rollers(127);
  }
  if (master.get_digital(DIGITAL_R2)){
    rollers(-127);
  }
  else{
    brakeRollers();
    rollers(0);
  }
}
