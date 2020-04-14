//helper functions
void wait(int time);
void right(int speed);
void left(int speed);
void timedDrive(int time, int speed);
void brake();
void coast();

//auton functions
void moveForward(double targetInches);
void moveBackward(double targetInches);
void turn(int degrees);

//drive control
void driveOP();
