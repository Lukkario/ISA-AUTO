#include <Arduino.h>
#include <math.h>
#include "ISAMobile.h"
#include "move.h"
#include "distance.h"
#include <DueTimer.h>

#define RESOLUTION_BOTTOM 9
#define RESOLUTION_TOP 9

int angles[] = {1, 239, 162, 85};

QMC5883 qmc;

float getAngle()
{
  qmc.measure();
  float angle = atan2(qmc.getY(), qmc.getX()) * (180.0 / M_PI); // convert to degrees
  return angle < 0 ? (angle + 360) : angle;
}

void test()
{
  int i = 1;
  delay(500);
  moveForward(200);
  while(getDistance(SensorSide::Front) > 20)
  {
  }

  turnRight(200);
  while(getDistance(SensorSide::Left) > 25)
  {
  }

  moveForward(200);
  while(getDistance(SensorSide::Left) < 50)
  {
      i++;
  }
  delay(300);

  turnLeft(120);
  while(!(getAngle() + RESOLUTION_TOP > angles[0] && getAngle() - RESOLUTION_BOTTOM - 10 < angles[0])) {
  }
  stop();
  delay(500);
  moveForward(200);
  while (getDistance(SensorSide::Left) > 25) {

  }
  stop();
  delay(500);

  moveForward(200);
  while (getDistance(SensorSide::Left) < 30) {

  }
  delay(300);

  turnLeft(120);
  while(!(getAngle() + RESOLUTION_TOP > angles[3] && getAngle() - RESOLUTION_BOTTOM - 10 < angles[3])) {
  }

  moveForward(200);
  while(getDistance(SensorSide::Left) > 25)
  {

  }
  stop();
  moveForward(200);
  while (i) {
      i--;
  }
delay(300);
  turnRight(120);
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
while(1){}
}
