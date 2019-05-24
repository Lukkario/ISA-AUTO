#include <Arduino.h>
#include <math.h>
#include <ISAMobile.h>
#include "move.h"

QMC5883 qmc;

int16_t startX = 0;
int16_t startY = 0;
int16_t startZ = 0;

double radToDeg(int16_t x, int16_t y)
{
    // x = x-startX;
    // y = y - startY;
    double bearingDegrees = atan2(y, x) * (180.0 / M_PI); // convert to degrees
    bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees)); // correct discontinuity
    return bearingDegrees;
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

    //pinMode(MODE, OUTPUT); -- podłaczone na krótko ze stanem wysokim
    //digitalWrite(MODE, true);  -- podłaczone na krótko ze stanem wysokim

    moveForward(EngineSelector::Left, 0);
    moveForward(EngineSelector::Right, 0);

    // Wejścia enkoderowe
    pinMode(ENCODER_LEFT, INPUT);
    pinMode(ENCODER_RIGHT, INPUT);

    Serial.begin(9600);
    // Serial.print("Test... ");

    Wire.begin();
    qmc.init();
}

void loop()
{
    moveForward(100);
    delay(2000);
   stop();
   delay(100);
   qmc.measure();
   startX = qmc.getX();
   startY = qmc.getY();
    double deg = radToDeg(startX, startY);

    turnRight(100);

    while((deg > radToDeg(qmc.getX(), qmc.getY()) ? abs(deg - radToDeg(qmc.getX(), qmc.getY())) : abs(radToDeg(qmc.getX(), qmc.getY()) - deg) ) <= 90)
    {
        // Serial.println(radToDeg(qmc.getX(), qmc.getY()));
        qmc.measure();
    }
    stop();
    delay(100);



}
