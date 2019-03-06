#include "UltrasonicMovements.h"

UltrasonicMovements::UltrasonicMovements(Movements *move, ADIUltrasonic *left, ADIUltrasonic *right){
  ultraLeft = left;
  ultraRight = right;
  robot = move;
}

//Ultra will be parsed to extra file.
void UltrasonicMovements::alignUltrasonic(int rotateVelocity, int threshold, int delayTime){
  //printf("Ultra align started \n");
  //printf("Left %d, Right %d \n", ultraLeft->get_value(), ultraRight->get_value());
  if(ultraLeft->get_value() - ultraRight->get_value() > 0){
    //printf("Left bigger-> \n");
    //Turn Right
    robot->leftDriveF->move_velocity(rotateVelocity);
    robot->leftDriveR->move_velocity(rotateVelocity);
    robot->rightDriveF->move_velocity(-rotateVelocity);
    robot->rightDriveR->move_velocity(-rotateVelocity);

    while(ultraLeft->get_value()-ultraRight->get_value() > threshold){
      delay(delayTime);
    }
    //Stop
    robot->leftDriveF->move(0);
    robot->leftDriveR->move(0);
    robot->rightDriveF->move(0);
    robot->rightDriveR->move(0);
  }else if(ultraRight->get_value() - ultraLeft->get_value() > 0){
    //printf("Right bigger \n");
    //Turn Left
    robot->leftDriveF->move_velocity(-rotateVelocity);
    robot->leftDriveR->move_velocity(-rotateVelocity);
    robot->rightDriveF->move_velocity(rotateVelocity);
    robot->rightDriveR->move_velocity(rotateVelocity);
    //printf("move issued \n");

    while(ultraRight->get_value()-ultraLeft->get_value() > threshold){
      delay(delayTime);
      //printf("Left %d, Right %d \n", ultraLeft->get_value(), ultraRight->get_value());
    }
    //printf("Stopped \n");
    //Stop
    robot->leftDriveF->move(0);
    robot->leftDriveR->move(0);
    robot->rightDriveF->move(0);
    robot->rightDriveR->move(0);
  }

  //printf("Alligned.\n");
}

void UltrasonicMovements::alignAlternate(float rotateVelocity, int threshold, int delayTime){
  while(ABS(ultraLeft->get_value() - ultraRight->get_value()) > threshold){
    int error = ultraLeft->get_value() - ultraRight->get_value();

    printf("Left %d, right %d, error %d \n", ultraLeft->get_value(), ultraRight->get_value(), error);

    robot->leftDriveF->move_velocity(rotateVelocity*error);
    robot->leftDriveR->move_velocity(rotateVelocity*error);
    robot->rightDriveF->move_velocity(-rotateVelocity*error);
    robot->rightDriveR->move_velocity(-rotateVelocity*error);

    delay(delayTime);
  }
  robot->powerMotor(0);
}

void UltrasonicMovements::alignTime(int rotateVelocity, int time, int delayTime){
  for(int i = 0; i < time; i++){
    int error = ultraLeft->get_value() - ultraRight->get_value();

    robot->leftDriveF->move_velocity(rotateVelocity+error);
    robot->leftDriveR->move_velocity(rotateVelocity+error);
    robot->rightDriveF->move_velocity(-rotateVelocity-error);
    robot->rightDriveR->move_velocity(-rotateVelocity-error);

    delay(delayTime);
  }
  robot->powerMotor(0);
}

//End Ultra
