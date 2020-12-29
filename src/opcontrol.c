#include "main.h"
int con = 2;
int target;
int target2;
int speed;
bool check;

void homeShoulder(int homePosition) {
printf("homing started, stand by \n");
while(digitalRead(3)==1){
  printf("The bumper switch value %d \n", digitalRead(3)==1);
motorSet(9,-63);
}

motorSet(9,0);
encoderReset(encoder1);
while(encoderGet(encoder1)<homePosition) {
  printf("The shoulder encoder value %d \n", encoderGet(encoder1));
motorSet(9,63);
}
motorSet(9,0);
printf("homing complete \n");
}

void homeElbow(int homePosition){
  printf("homing started, stand by \n");
  while(digitalRead(6)==HIGH){
  printf("The limit switch value %d \n", digitalRead(6));
  motorSet(8,-63);
  }
  motorSet(8,0);
  encoderReset(encoder2);
  while(encoderGet(encoder2)>homePosition) {
    printf("The elbow encoder value %d \n", encoderGet(encoder2));
  motorSet(8,63);
  }
  motorSet(8,0);
  printf("homing complete \n");
  }


void chassisSet(int left, int right) {
  motorSet(2, right);
  motorSet(3, left);
}


void shoulderSet(int speed) {
	motorSet(9, -speed);
}

void wristSet(int speed) {
	motorSet(4, -speed);
}

void clawSet(int speed) {
	motorSet(7, -speed);
}

void follow1d(){
  while(!(joystickGetDigital(1, 8, JOY_RIGHT))){
    printf("The Ultrasonic sensor value is %d \n", ultrasonicGet(sensor));
    if(ultrasonicGet(sensor)<100){
      motorSet(2, -30);
      motorSet(3, -30);
    }else if(ultrasonicGet(sensor)>100){
      motorSet(2, 30);
      motorSet(3, 30);
    }else{
      motorSet(2, 0);
      motorSet(3, 0);
    }
  }
}

void follow2d(){
  while(!(joystickGetDigital(1, 8, JOY_RIGHT))){
    printf("The Ultrasonic sensor value is %d \n", ultrasonicGet(sensor));

    if(ultrasonicGet(sensor)==-1 || ultrasonicGet(sensor)>250){
      if(check){
        motorSet(2, -60);
        motorSet(3, 60);
      }else{
        check=true;
      }
    }else if(ultrasonicGet(sensor)<85){
      check=false;
      speed = (115-ultrasonicGet(sensor));
      motorSet(2, -speed);
      motorSet(3, -speed);
      printf("**** %d \n", ultrasonicGet(sensor));
    }else if(ultrasonicGet(sensor)>115){
      check=false;
      speed = (ultrasonicGet(sensor)-85);
      motorSet(2, speed);
      motorSet(3, speed);
      print("check less greater than 100");
    }else{
      check=false;
      motorSet(2, 0);
      motorSet(3, 0);
      print("check else");
    }
  }
}

void lineFollow(){
  while(!(joystickGetDigital(1, 5, JOY_DOWN))){
if(analogReadCalibrated(2)>analogReadCalibrated(1) &&analogReadCalibrated(2)>analogReadCalibrated(3)){
  motorSet(2, 25);
  motorSet(3, 25);
}else if(analogReadCalibrated(3)>analogReadCalibrated(1) && analogReadCalibrated(3)>=analogReadCalibrated(2)){
  motorSet(2,-70);
  motorSet(3, 40);
}else if(analogReadCalibrated(1)>analogReadCalibrated(3) && analogReadCalibrated(1)>=analogReadCalibrated(2)){
  motorSet(2, 40);
  motorSet(3,-70);//left
}else{
  motorSet(2, 30);
  motorSet(3, 30);
}
}
}

void operatorControl() {
  int power;
  int turn;

    while (1) {
printf("The Ultrasonic sensor value is %d \n", ultrasonicGet(sensor));

      if(joystickGetDigital(1, 8, JOY_UP)){
        homeShoulder(180);
      }

      if(joystickGetDigital(1, 8, JOY_DOWN)){
        homeElbow(-70);
      }

      if(joystickGetDigital(1, 7, JOY_UP)){
        clawSet(63);
      }else if(joystickGetDigital(1, 7, JOY_DOWN)){
        clawSet(-63);
      }else{
        clawSet(0);
      }

      if(joystickGetDigital(1, 7, JOY_LEFT)){
        wristSet(63);
      }else if(joystickGetDigital(1, 7, JOY_RIGHT)){
        wristSet(-63);
      }else{
        wristSet(0);
      }

      if(joystickGetDigital(1, 8, JOY_LEFT)){
        follow2d();
      }

      if(joystickGetDigital(1, 5, JOY_UP)){
        lineFollow();
      }

        power = joystickGetAnalog(1, 2); // vertical axis on left joystick
        turn  = joystickGetAnalog(1, 1); // horizontal axis on left joystick
				chassisSet((power+turn),(power-turn));

        printf("The shoulder encoder value %d \n", encoderGet(encoder1));
        if(joystickGetAnalog(1, 3) != 0){
          shoulderSet(-1*joystickGetAnalog(1, 3));
          target=encoderGet(encoder1);
        }else{
          int diff = encoderGet(encoder1)-target;
          shoulderSet(diff*con);
        }

        printf("The elbow encoder value %d \n", encoderGet(encoder2));
				if(joystickGetDigital(1, 6, JOY_UP)) {
      motorSet(8,127); // pressing up, so lift should go up
      target2=encoderGet(encoder2);
    }else if(joystickGetDigital(1, 6, JOY_DOWN)) {
      motorSet(8,-127); // pressing down, so lift should go down
      target2=encoderGet(encoder2);
    }
    else {
      motorSet(8,encoderGet(encoder2)-target2); // no buttons are pressed, stop the lift
    }

        delay(20);
    }

}
