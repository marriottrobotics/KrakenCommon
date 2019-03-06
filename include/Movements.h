#ifndef EMS_MOVEMENTS
#define EMS_MOVEMENTS

#include "api.h"
#include "Helpers.h"

using namespace pros;

class Movements{
public:
  bool red;
  bool top;

  Motor *leftDriveF;
  Motor *leftDriveR;
  Motor *rightDriveF;
  Motor *rightDriveR;

  Movements(Motor *ldf, Motor *ldr, Motor *rdf, Motor *rdr);
  //void powerDrive(int leftF, int leftR, int rightF, int rightR);
  void powerMotor(int speed);
  void drive(int distance, int speed);
  void driveAsync(int distance, int speed);
  void turnUp(int distance, int speed);
  void slideUp(int distance, int speed);
  void moveAccel(int distance);
};

#endif /* end of include guard: EMS_MOVEMENTS */
