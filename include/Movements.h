#ifndef EMS_MOVEMENTS
#define EMS_MOVEMENTS

#include "api.h"
#include "Helpers.h"

using namespace pros;

class Movements{
  bool red;
  bool top;

  Motor *leftDriveF;
  Motor *leftDriveR;
  Motor *rightDriveF;
  Motor *rightDriveR;

public:
  Movements(Motor *ldf, Motor *ldr, Motor *rdf, Motor *rdr);
  //void powerDrive(int leftF, int leftR, int rightF, int rightR);
  void powerMotor(int speed);
  void drive(int distance, int speed);
  void driveAsync(int distance, int speed);
  void turnUp(int distance, int speed);
  void slideUp(int distance, int speed);
  //This needs to be fixed.
  void alignUltrasonic(int rotateVelocity = 50, int threshold = 0, int delayTime = 5);
  void alignAlternate(float rotateVelocity = 25, int threshold = 3, int delayTime = 5);
  void alignTime(int rotateVelocity = 25, int time = 0, int delayTime = 5);
  void moveAccel(int distance);
  void distUltrasonic(int target, int threshold = 10, int delayTime = 5, double rotateVelocity = 0.5);
  int currentSensor();
};

#endif /* end of include guard: EMS_MOVEMENTS */