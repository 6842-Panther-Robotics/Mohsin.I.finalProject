#include "main.h"

using namespace pros;

//sensors
Imu inertial(9);

//motors
Motor rightFront(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor leftFront(3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor rightBack(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor leftBack(4, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

//PIDController instance
PIDController movePID(0.5, 30);
PIDController turnPID(0.2, 30);

//constants
int TICS_PER_REVOLUTION=360;
int WHEEL_DIAMETER=4;
double PI=3.14159;
int CORRECTION_THRESHHOLD=3;
int TIME_INCREMENT_THRESHHOLD=5;
double CORRECTION_FACTOR=0.8;

int rightFrontPosition=rightFront.get_position();
int leftFrontPosition=leftFront.get_position();

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

void brakeDrive(){
  rightFront.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  leftFront.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  rightBack.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  leftBack.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void coastDrive(){
  rightFront.set_brake_mode(E_MOTOR_BRAKE_COAST);
  leftFront.set_brake_mode(E_MOTOR_BRAKE_COAST);
  rightBack.set_brake_mode(E_MOTOR_BRAKE_COAST);
  leftBack.set_brake_mode(E_MOTOR_BRAKE_COAST);
}

//auton functions
void moveForward(double targetInches){
  int time=0;
  double target = TICS_PER_REVOLUTION*(targetInches / (WHEEL_DIAMETER * PI));
  int drivePIDSpeed=movePID.getOutput(targetInches, rightFront.get_position());

  rightFront.tare_position();
  leftFront.tare_position();

  while (time<100){
    left(drivePIDSpeed);
    right(drivePIDSpeed);

    if (abs(rightFrontPosition-leftFrontPosition)<CORRECTION_THRESHHOLD){
      right(drivePIDSpeed);
      left(drivePIDSpeed*CORRECTION_FACTOR);
    }

    if (abs(leftFrontPosition-rightFrontPosition)<CORRECTION_THRESHHOLD){
      right(drivePIDSpeed*CORRECTION_FACTOR);
      left(drivePIDSpeed);
    }

    if (fabs(movePID.getError()<TIME_INCREMENT_THRESHHOLD)){
      time++;
    }

  }
  brakeDrive();
  left(0);
  right(0);
}

void moveBackward(double targetInches){
  int time=0;
  double target = TICS_PER_REVOLUTION*(targetInches / (WHEEL_DIAMETER * PI));
  int drivePIDSpeed=movePID.getOutput(targetInches, rightFront.get_position());

  rightFront.tare_position();
  leftFront.tare_position();

  while (time<100){
    left(-drivePIDSpeed);
    right(-drivePIDSpeed);

    if (abs(rightFrontPosition-leftFrontPosition)<CORRECTION_THRESHHOLD){
      right(-drivePIDSpeed);
      left(-drivePIDSpeed*CORRECTION_FACTOR);
    }

    if (abs(leftFrontPosition-rightFrontPosition)<CORRECTION_THRESHHOLD){
      right(-drivePIDSpeed*CORRECTION_FACTOR);
      left(-drivePIDSpeed);
    }

    if (fabs(movePID.getError()<TIME_INCREMENT_THRESHHOLD)){
      time++;
    }

  }
  brakeDrive();
  left(0);
  right(0);
}

void turn(int degrees){
  int turnPIDSpeed=turnPID.getOutput(degrees, inertial.get_rotation());
  int time=0;

  while (time<100){
    left(turnPIDSpeed);
    right(-turnPIDSpeed);

    if (abs(rightFrontPosition-leftFrontPosition)<CORRECTION_THRESHHOLD){
      right(-turnPIDSpeed);
      left(turnPIDSpeed*CORRECTION_FACTOR);
    }

    if (abs(leftFrontPosition-rightFrontPosition)<CORRECTION_THRESHHOLD){
      right(-turnPIDSpeed*CORRECTION_FACTOR);
      left(turnPIDSpeed);
    }
    if (fabs(turnPID.getError()<TIME_INCREMENT_THRESHHOLD)){
      time++;
    }
  }
  brakeDrive();
  left(0);
  right(0);
}

//driveOP
void driveOP(){
  rightFront.move(master.get_analog(ANALOG_RIGHT_Y));
  leftFront.move(master.get_analog(ANALOG_LEFT_Y));
  rightBack.move(master.get_analog(ANALOG_RIGHT_Y));
  leftBack.move(master.get_analog(ANALOG_LEFT_Y));
}
