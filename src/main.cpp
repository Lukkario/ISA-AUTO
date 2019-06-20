#include <Arduino.h>
#include <math.h>
#include "ISAMobile.h"
#include "move.h"
#include "distance.h"
#include <DueTimer.h>
#include <Wire.h>

#define RESOLUTION_BOTTOM 9 //-kąta docelowego
#define RESOLUTION_TOP 9 //+kąta docelowego

//int angles[] = {210, 230, 270, 290, 336, 17, 90, 156};
int angles[] = {0, 246, 167, 96};
int numberOfAngle = 2;

QMC5883 qmc;
// Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(0x0D);

int16_t startX = 0;
int16_t startY = 0;
int16_t startZ = 0;
int startAngle = 0;
bool calib = true;
int avgx = 0;
int avgy = 0;


float getAngle()
{

    qmc.measure();
  // Serial.print("Y = ");
  // Serial.print(qmc.getY());
  // Serial.print(" X = ");
  // Serial.println(qmc.getX());

  float angle = atan2(qmc.getY(), qmc.getX()) * (180.0 / M_PI); // convert to degrees
  return angle < 0 ? (angle + 360) : angle;
}

// void initalize(){
//   turnRight(200);
//   do{
//   }while(!((getAngle() >= angles[0] - RESOLUTION_BOTTOM) && (getAngle() <= angles[0] + RESOLUTION_TOP)));
// }
//
// boolean checkIfFinishAngle() {
//   if(numberOfAngle == 6 && ((getAngle() >= angles[numberOfAngle] - 10) && (getAngle() <= angles[numberOfAngle] + 10))) {
//      numberOfAngle+=2;
//     if(numberOfAngle > 7) {
//       numberOfAngle = 0;
//     }
//     return true;
//   }
//   if(((getAngle() >= angles[numberOfAngle] - RESOLUTION_BOTTOM) && (getAngle() <= angles[numberOfAngle] + RESOLUTION_TOP))) {
//     numberOfAngle+=2;
//     if(numberOfAngle > 7) {
//       numberOfAngle = 0;
//     }
//     return true;
//   }
//     return false;
// }
//
void test()
{
  delay(500);
  while(getDistance(SensorSide::Front) > 20)
  {
    moveForward(150);
  }
  stop();

  while(getDistance(SensorSide::Left)>25)
  {
  turnRight(170);
  }
  while(getDistance(SensorSide::Left) < 50)
  {
    moveForward(150);
  }
  stop();
  delay(500);
  turnLeft(150);
  while (getAngle() > angles[0] + 10 && getAngle() < angles[0] - 10) {
  }
  stop();

}

// void test()
// {
//   moveForward(150);
//   delay(1000);
//   stop();
//   delay(500);
//   turnRight(120);
//   while (!(getAngle() + RESOLUTION_TOP > angles[1] && getAngle() - RESOLUTION_BOTTOM < angles[1])) {
//   }
//   stop();
//   delay(500);
//
//   moveForward(150);
//   delay(1000);
//   stop();
//   delay(500);
//   turnRight(120);
//   while (!(getAngle() + RESOLUTION_TOP > angles[2] && getAngle() - RESOLUTION_BOTTOM < angles[2])) {
//   }
//   stop();
//   delay(500);
//
//   moveForward(150);
//   delay(1000);
//   stop();
//   delay(500);
//   turnRight(120);
//   while (!(getAngle() + RESOLUTION_TOP > angles[3] && getAngle() - RESOLUTION_BOTTOM < angles[3])) {
//   }
//   stop();
//   delay(500);
//
//   moveForward(150);
//   delay(1000);
//   stop();
//   delay(500);
//   turnRight(120);
//   while (!(getAngle() + RESOLUTION_TOP > angles[0] && getAngle() - RESOLUTION_BOTTOM < angles[0])) {
//   }
//   stop();
//   delay(500);
// }

void setup()
{
  for (int i = (int)UltraSoundSensor::__first; i <= (int)UltraSoundSensor::__last; i++)
  	{
  		pinMode(ultrasound_trigger_pin[i], OUTPUT);
  		pinMode(ultrasound_echo_pin[i], INPUT);

  		digitalWrite(ultrasound_trigger_pin[i], 0);
  	}

  	// Silniki
  	pinMode(LEFT_PWM, OUTPUT);
  	pinMode(LEFT_IN1, OUTPUT);
  	pinMode(LEFT_IN2, OUTPUT);

  	pinMode(RIGHT_PWM, OUTPUT);
  	pinMode(RIGHT_IN1, OUTPUT);
  	pinMode(RIGHT_IN2, OUTPUT);


  	moveForward(EngineSelector::Left, 0);
  	moveForward(EngineSelector::Right, 0);


    // Wejścia enkoderowe
    pinMode(ENCODER_LEFT, INPUT);
    pinMode(ENCODER_RIGHT, INPUT);

    Serial.begin(9600);
    // Serial.print("Test... ");
Wire.begin();
qmc.init();
// initalize();
test();
}


void loop()
{
  // delay(1000);
  // Serial.print("SAMPLE: ");
  // Serial.println(getSampledDistance(SensorSide::Front));
  // Serial.print("RAW: ");
 // Serial.println(getDistance(SensorSide::Front));
  // delay(100);

  //    moveForward(170);
  //    delay(2000);
  //    stop();
  //    delay(1000);
  //    turnLeft(200);
  // do{
  //
  // }while(!(checkIfFinishAngle()));

  //    stop();
  //    delay(1000);
// //  stop();
// while(getDistance(SensorSide::Front) > 20)
// {
// moveForward(200);
// }
// stop();
// while(getDistance(SensorSide::Left)>25)
// {
// turnRight(200);
// }
// do{
//
//   }while(!(checkIfFinishAngle()));
//      stop();
//      delay(1000);
// break;
// }
// if(getAngle() + 10 > angles[1] && getAngle() - 10 < angles[1])
//   Serial.println(getAngle());
// delay(500);


}
