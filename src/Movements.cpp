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

//Ultra will be parsed to extra file.
void Movements::alignUltrasonic(int rotateVelocity, int threshold, int delayTime){
  //printf("Ultra align started \n");
  //printf("Left %d, Right %d \n", ultraLeft->get_value(), ultraRight->get_value());
  if(ultraLeft->get_value() - ultraRight->get_value() > 0){
    //printf("Left bigger-> \n");
    //Turn Right
    leftDriveF->move_velocity(rotateVelocity);
    leftDriveR->move_velocity(rotateVelocity);
    rightDriveF->move_velocity(-rotateVelocity);
    rightDriveR->move_velocity(-rotateVelocity);

    while(ultraLeft->get_value()-ultraRight->get_value() > threshold){
      delay(delayTime);
    }
    //Stop
    leftDriveF->move(0);
    leftDriveR->move(0);
    rightDriveF->move(0);
    rightDriveR->move(0);
  }else if(ultraRight->get_value() - ultraLeft->get_value() > 0){
    //printf("Right bigger \n");
    //Turn Left
    leftDriveF->move_velocity(-rotateVelocity);
    leftDriveR->move_velocity(-rotateVelocity);
    rightDriveF->move_velocity(rotateVelocity);
    rightDriveR->move_velocity(rotateVelocity);
    //printf("move issued \n");

    while(ultraRight->get_value()-ultraLeft->get_value() > threshold){
      delay(delayTime);
      //printf("Left %d, Right %d \n", ultraLeft->get_value(), ultraRight->get_value());
    }
    //printf("Stopped \n");
    //Stop
    leftDriveF->move(0);
    leftDriveR->move(0);
    rightDriveF->move(0);
    rightDriveR->move(0);
  }

  //printf("Alligned->\n");
}

void Movements::alignAlternate(float rotateVelocity, int threshold, int delayTime){
  while(ABS(ultraLeft->get_value() - ultraRight->get_value()) > threshold){
    int error = ultraLeft->get_value() - ultraRight->get_value();

    printf("Left %d, right %d, error %d \n", ultraLeft->get_value(), ultraRight->get_value(), error);

    leftDriveF->move_velocity(rotateVelocity*error);
    leftDriveR->move_velocity(rotateVelocity*error);
    rightDriveF->move_velocity(-rotateVelocity*error);
    rightDriveR->move_velocity(-rotateVelocity*error);

    delay(delayTime);
  }
  powerMotor(0);
}

void Movements::alignTime(int rotateVelocity, int time, int delayTime){
  for(int i = 0; i < time; i++){
    int error = ultraLeft->get_value() - ultraRight->get_value();

    leftDriveF->move_velocity(rotateVelocity+error);
    leftDriveR->move_velocity(rotateVelocity+error);
    rightDriveF->move_velocity(-rotateVelocity-error);
    rightDriveR->move_velocity(-rotateVelocity-error);

    delay(delayTime);
  }
  powerMotor(0);
}

//End Ultra

void Movements::moveAccel(int distance){
  printf("Starting Accl \n");

  int accelTime = 250;
  //Calculate the time accel and decel should be taking->
  if(distance < 500){
    accelTime = distance / 2;
  }

  int initial = leftDriveF->get_position();
  double diff = 0;
  double coef = 3->0/1250->0;
  double decelCoef = 200->0/62500->0;
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
  //Continue at full speed->
  while(ABS(distance) - (ABS((leftDriveF->get_position()-initial))) > accelTime){
    delay(1);
  }
  printf("Deceleration started Ticks relative %f \n", ABS(leftDriveF->get_position()-initial));
  //Decelerate-> *This is going to have issues with posative and negative move->
  while(ABS(distance) - (ABS((leftDriveF->get_position()-initial))) > 0){
    diff = ABS(distance) - ABS(leftDriveF->get_position()-initial);
    diff = accelTime-diff;
    double speed = (-200->0/250->0) * diff + 200;
    int speedBuf = (int)speed;
    //printf("Relative position = %f, power %d \n", diff, speedBuf);
    powerMotor(speedBuf);
    delay(1);
  }
  printf("Decel ended-> Motor at %f \n", ABS(leftDriveF->get_position()-initial));

  powerMotor(0);
}

void Movements::distUltrasonic(int target, int threshold, int delayTime, double rotateVelocity){
  double error = 0;
  while(ABS(currentSensor() - target) > threshold){

    error = currentSensor() - target;

    //printf("Left %d, target %d, error %f \n", ultraLeft->get_value(), target, error);

    //printf("Power = %f \n", rotateVelocity*error);
    leftDriveF->move_velocity(rotateVelocity*error);
    leftDriveR->move_velocity(rotateVelocity*error);
    rightDriveF->move_velocity(rotateVelocity*error);
    rightDriveR->move_velocity(rotateVelocity*error);

    delay(delayTime);
  }
  powerMotor(0);
}

int Movements::currentSensor(){
  if(red){
    return ultraLeft->get_value();
  }else{
    return ultraRight->get_value();
  }
}

void Movements::slideAlign(int distance){
  printf("Starting setup \n");
  int start = leftDriveF->get_position();
  int fVel = 200;
  int rVel = -200;
  int err = ultraLeft->get_value()-ultraRight->get_value();
  leftDriveF->move_velocity(fVel);
  leftDriveR->move_velocity(rVel);
  rightDriveF->move_velocity(rVel);
  rightDriveR->move_velocity(fVel);
  printf("Starting loop \n");
  while(ABS(leftDriveF->get_position()-start) < distance){
    err = ultraLeft->get_value()-ultraRight->get_value();
    if(err > 0){
      fVel = 200 + err;
      rVel = 200;
    }else if(err < 0){
      rVel = -200 + err; //Err is - so it is 200 - ABS(err)
      fVel = 200;
    }else{
      rVel = -200;
      fVel = 200;
    }
    printf("Looping with err %d, fVel %d, rVel %d \n", err, fVel, rVel);
    leftDriveF->move_velocity(fVel);
    leftDriveR->move_velocity(rVel);
    rightDriveF->move_velocity(rVel);
    rightDriveR->move_velocity(fVel);
    delay(1);
  }
}
