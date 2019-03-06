#ifndef EMS_ULTRA
#define EMS_ULTRA
#include "Movements.h"

class UltrasonicMovements{

ADIUltrasonic *ultraLeft;
ADIUltrasonic *ultraRight;
Movements *robot;

public:
  UltrasonicMovements(Movements *move, ADIUltrasonic *left, ADIUltrasonic *right);

  void alignUltrasonic(int rotateVelocity = 50, int threshold = 0, int delayTime = 5);
  void alignAlternate(float rotateVelocity = 25, int threshold = 3, int delayTime = 5);
  void alignTime(int rotateVelocity = 25, int time = 0, int delayTime = 5);
  void distUltrasonic(int target, int threshold = 10, int delayTime = 5, double rotateVelocity = 0.5);
  int currentSensor();
};


#endif /* end of include guard: EMS_ULTRA */
