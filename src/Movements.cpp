#include "Movements.h"
#include <iostream>
#include <math.h>

Movements::Movements(Motor *ldf, Motor *ldr, Motor *rdf, Motor *rdr){
  leftDriveF = ldf;
  leftDriveR = ldr;
  rightDriveF = rdf;
  rightDriveR = rdr;
}

void Movements::powerMotor(int speed){
  leftDriveF->move_velocity(speed);
  leftDriveR->move_velocity(speed);
  rightDriveF->move_velocity(speed);
  rightDriveR->move_velocity(speed);
}

void Movements::drive(int distance, int speed){
  leftDriveF->move_relative(distance, speed);
  leftDriveR->move_relative(distance, speed);
  rightDriveF->move_relative(distance, speed);
  rightDriveR->move_relative(distance, speed);
  while(ABS(rightDriveR->get_position()-rightDriveR->get_target_position()) >= 10 || ABS(rightDriveF->get_position()-rightDriveF->get_target_position()) >= 10
    || ABS(leftDriveF->get_position()-leftDriveF->get_target_position()) >= 10 || ABS(leftDriveR->get_position()-leftDriveR->get_target_position()) >= 10){
    //Do nothing
    delay(1);
  }
}

void Movements::driveAsync(int distance, int speed){
  leftDriveF->move_relative(distance, speed);
  leftDriveR->move_relative(distance, speed);
  rightDriveF->move_relative(distance, speed);
  rightDriveR->move_relative(distance, speed);
}

void Movements::turnUp(int distance, int speed){
    if(!red){
      leftDriveF->move_relative(distance, speed);
      leftDriveR->move_relative(distance, speed);
      rightDriveF->move_relative(-distance, speed);
      rightDriveR->move_relative(-distance, speed);
    }else{
      leftDriveF->move_relative(-distance, speed);
      leftDriveR->move_relative(-distance, speed);
      rightDriveF->move_relative(distance, speed);
      rightDriveR->move_relative(distance, speed);
    }
    while(ABS(rightDriveR->get_position()-rightDriveR->get_target_position()) >= 10){
      //Do nothing
    }
}

void Movements::slideUp(int distance, int speed){
    if(!red){
      leftDriveF->move_relative(distance, speed);
      leftDriveR->move_relative(-distance, speed);
      rightDriveF->move_relative(-distance, speed);
      rightDriveR->move_relative(distance, speed);
    }else{
      leftDriveF->move_relative(-distance, speed);
      leftDriveR->move_relative(distance, speed);
      rightDriveF->move_relative(distance, speed);
      rightDriveR->move_relative(-distance, speed);
    }
    while(ABS(rightDriveR->get_position()-rightDriveR->get_target_position()) >= 10){
      //Do nothing
    }
}

void Movements::moveAccel(int distance){
  printf("Starting Accl \n");

  int accelTime = 250;
  //Calculate the time accel and decel should be taking.
  if(distance < 500){
    accelTime = distance / 2;
  }

  int initial = leftDriveF->get_position();
  double diff = 0;
  double coef = 3.0/1250.0;
  double decelCoef = 200.0/62500.0;
  //printf("Coef = %f \n", coef);
  //Accelerate
  while(ABS(leftDriveF->get_position() - initial) < accelTime){
    diff = ABS(leftDriveF->get_position() - initial);
    //printf("Diff %f \n", diff);
    double speed = (coef*pow(diff, 2)) + 50;
    int speedBuf = (int)speed;
    powerMotor(speedBuf);
    delay(1);
  }
  printf("Acceleration complete \n");

  powerMotor(200);
  //Continue at full speed.
  while(ABS(distance) - (ABS((leftDriveF->get_position()-initial))) > accelTime){
    delay(1);
  }
  printf("Deceleration started Ticks relative %f \n", ABS(leftDriveF->get_position()-initial));
  //Decelerate. *This is going to have issues with posative and negative move.
  while(ABS(distance) - (ABS((leftDriveF->get_position()-initial))) > 0){
    diff = ABS(distance) - ABS(leftDriveF->get_position()-initial);
    diff = accelTime-diff;
    double speed = (-200.0/250.0) * diff + 200;
    int speedBuf = (int)speed;
    //printf("Relative position = %f, power %d \n", diff, speedBuf);
    powerMotor(speedBuf);
    delay(1);
  }
  printf("Decel ended. Motor at %f \n", ABS(leftDriveF->get_position()-initial));

  powerMotor(0);
}
