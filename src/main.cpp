#include <Arduino.h>
#include <math.h>
#include <ISAMobile.h>
#include <HMC5883L.h>
#include "move.h"
#include <DueTimer.h>

QMC5883 qmc;
HMC5883L compass;

int16_t startX = 0;
int16_t startY = 0;
int16_t startZ = 0;
int startAngle = 0;
bool calib = true;
int avgx = 0;
int avgy = 0;

// void stopCalibrate()
// {
//   calib = false;
// }
//
// void calibrate()
// {
//   moveForward(EngineSelector::Right, 90);
//   moveBackwards(EngineSelector::Left, 150);
//
//   int minx = 0;
//   int maxx = 0;
//   int miny = 0;
//   int maxy = 0;
//   while(calib)
//   {
//     qmc.measure();
//     if(qmc.getX() > maxx)
//       maxx = qmc.getX();
//     if(qmc.getX() < minx)
//       minx = qmc.getX();
//     if(qmc.getY() > maxy)
//       maxy = qmc.getX();
//     if (qmc.getY() < miny)
//       miny = qmc.getY();
//
//   }
//   avgx = (maxx - minx) / 2;
//   avgy = (maxy - miny) / 2;
//   stop();
//   Timer4.stop();
// }

int getAngle()
{
  int x = 0;
  int y = 0;
  for(byte i = 0; i < 5; i++)
  {
    qmc.measure();
    x += qmc.getX();
    y += qmc.getY();
  }
  x /= 5;
  y /= 5;
  // Serial.print("Y = ");
  // Serial.print(qmc.getY());
  // Serial.print(" X = ");
  // Serial.println(qmc.getX());
  int angle = atan2(y - avgy, x - avgx) * (180.0 / M_PI); // convert to degrees
  return angle;
  // return angle < 0 ? (int)(angle + 360) : (int)angle;
}

void turn(int16_t deg)
{
    int now;
    int last = getAngle();
    int rot = 0;
    //Serial.println(start);
    while(rot <= deg)
    {
      now = getAngle();
      if(now > last + 20)
        now = last;
      // if(now >= 280 && startAngle < 300)
      //   now -= 360;
      rot += abs(now - startAngle);
      Serial.print("Start = ");
      Serial.print(startAngle);
      Serial.print(" Now = ");
      Serial.print(now);
      Serial.print(" Rot = ");
      Serial.println(rot);
      startAngle = now;
      // delay(1000);
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
    // Serial.print("Test... ");
Wire.begin();

while (!compass.begin())
  {
    Serial.println("Nie odnaleziono HMC5883L, sprawdz polaczenie!");
    delay(500);
  }
    qmc.init();

    // Timer4.attachInterrupt(stopCalibrate);
    // Timer4.start(8000000);
    // calibrate();
    // Serial.println(avgx);
    // Serial.println(avgy);
    // delay(5000);
}

void loop()
{
    // moveForward(170);
    // delay(2000);
    // stop();
    // delay(100);
    // startAngle = getAngle();
    // turnRight(70);
    // turn(80);
    // stop();
    // delay(100);
}
