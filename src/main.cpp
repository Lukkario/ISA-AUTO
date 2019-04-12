#include <Arduino.h>
#include <ISAMobile.h>
#include "move.h"

QMC5883 qmc;

int16_t startX = 0;
int16_t startY = 0;
int16_t startZ = 0;

void setup()
{
    for (int i = (int)UltraSoundSensor::__first; i <= (int)UltraSoundSensor::__last; i++)
    {
        pinMode(ultrasound_trigger_pin[i], OUTPUT);
        pinMode(ultrasound_echo_pin[i], INPUT);

        digitalWrite(ultrasound_trigger_pin[i], 0);
    }

    // Silniki
    pinMode(A_PHASE, OUTPUT);
    pinMode(A_ENABLE, OUTPUT);
    pinMode(B_PHASE, OUTPUT);
    pinMode(B_ENABLE, OUTPUT);

    //pinMode(MODE, OUTPUT); -- podłaczone na krótko ze stanem wysokim
    //digitalWrite(MODE, true);  -- podłaczone na krótko ze stanem wysokim

    moveForward(PowerSideEnum::Left, 0);
    moveForward(PowerSideEnum::Right, 0);

    // Wejścia enkoderowe
    pinMode(ENCODER_LEFT, INPUT);
    pinMode(ENCODER_RIGHT, INPUT);

    Serial.begin(9600);
    Serial.print("Test... ");

    Wire.begin();
    qmc.init();
    Serial1.begin(9600); // HC06
    qmc.measure();
    startX = qmc.getX();
    startY = qmc.getY();
    startZ = qmc.getZ();
}

void loop()
{
    qmc.measure();
    // int16_t x = qmc.getX();
    // int16_t y = qmc.getY();
    // int16_t z = qmc.getZ();
    // char buf[64];
    // sprintf(buf, "\n x=%5d, y=%5d, z=%5d", x ,y ,z);
    // Serial.print(buf);
    moveForward(100);
    delay(1000);
    stop();
    delay(1000);
    moveForward(PowerSideEnum::Right, 100);
    moveBackwards(PowerSideEnum::Left, 100);
    
    while(startX + qmc.getX() < 720 && startY - qmc.getY() < 100)
    {
        qmc.measure();
        delay(10);
    }
    
    delay(1000);
    stop();
    delay(1000);



}