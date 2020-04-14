#include "main.h"

double kp= 0;

int minSpeed = 0;

PIDController::PIDController(double inKP, int inMinSpeed){
  kp=inKP;
  minSpeed=inMinSpeed;
}

int PIDController::getOutput(int target, int current){

  error=target-current;

  int speed=error*kp;

  if (speed<= minSpeed && speed>=0){
    speed=minSpeed;
  }

  else if (speed<= minSpeed && speed<=0){
    speed=-minSpeed;
  }
  else{
    speed=speed;
  }
  return speed;
}

double PIDController::getError(){
  return error;
}
