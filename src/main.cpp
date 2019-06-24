#include <Arduino.h>
#include <math.h>
#include "ISAMobile.h"
#include "move.h"
#include "distance.h"
#include <DueTimer.h>

#define RESOLUTION_BOTTOM 4
#define RESOLUTION_TOP 4

int angles[] = {265, 175, 100, 21};

QMC5883 qmc;

float getAngle()
{
  qmc.measure();
  float angle = atan2(qmc.getY(), qmc.getX()) * (180.0 / M_PI); // convert to degrees
  return angle < 0 ? (angle + 360) : angle;
}

void test()
{
  int forward = 220;
  int turn = 255;
  int i = 1;
  delay(500);
  moveForward(forward);
  while(getDistance(SensorSide::Front) > 20)
  {
    if(getDistance(SensorSide::Front) < 70)
    {
      if(getDistance(SensorSide::Front) < 70)
      {
        moveForward( forward - ( forward/getDistance(SensorSide::Front) ) *12 );
      }
    }
  }

  turnRight(turn);
  while(!(getAngle() + RESOLUTION_TOP > angles[1] && getAngle() - RESOLUTION_BOTTOM - 10 < angles[1])) {
  }
  // while(getDistance(SensorSide::Left) > 25)
  // {
  // }

  moveForward(forward);
  while(getDistance(SensorSide::Left) < 50)
  {
      i++;
  }
  delay(100);

  turnLeft(turn);
  while(!(getAngle() + RESOLUTION_TOP > angles[0] && getAngle() - RESOLUTION_BOTTOM - 10 < angles[0])) {
  }
  stop();
  delay(500);
  moveForward(forward);
  while (getDistance(SensorSide::Left) > 25) {

  }
  stop();
  delay(500);

  moveForward(forward);
  while (getDistance(SensorSide::Left) < 30) {

  }
  delay(300);

  turnLeft(turn);
  while(!(getAngle() + RESOLUTION_TOP > angles[3] && getAngle() - RESOLUTION_BOTTOM - 10 < angles[3])) {
  }

  moveForward(forward);
  while(getDistance(SensorSide::Left) > 25)
  {

  }
  stop();
  moveForward(forward);
  while (i) {
      i--;
  }
delay(300);
  turnRight(turn);
  while(!(getAngle() + RESOLUTION_TOP > angles[0] && getAngle() - RESOLUTION_BOTTOM - 10 < angles[0])) {
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

void init_angles()
{
  int i = 0;
  while(true)
  {
    if(i > 3)
      break;
    if(Serial1.read() == '\n')
    {
      int angle = 0;
      for(int j = 0; j < 10; j++)
      {
        angle += getAngle();
      }
      angles[i] = angle/10;
      String c = String(angles[i]);
      Serial1.write(c.c_str());
      i++;

    }
  }
  while(true)
  {
    if(Serial1.read() == '\n')
      break;
  }
}

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
    Serial1.begin(9600);
    // Serial.print("Test... ");
Wire.begin();
qmc.init();
init_angles();
// test();
}


void loop()
{

  // delay(1000);
  // Serial.print("SAMPLE: ");
  // Serial.println(getSampledDistance(SensorSide::Front));
  // Serial.print("Front: ");
  // Serial.print(getDistance(SensorSide::Front));
  // Serial.print(" Left: ");
  // Serial.println(getDistance(SensorSide::Left));
  // delay(300);

  // Serial.println(getAngle());
  // delay(500);
//Serial.println(digitalRead(50));

  test();
// while(1){}


}
