
class PIDController {
private:
  double kp;
  int minSpeed;
  double error;

public:
  PIDController(double inKP, int inMinSpeed);

  int getOutput(int target, int current);

  double getError();
};
