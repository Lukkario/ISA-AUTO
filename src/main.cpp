#include <Arduino.h>
#include <ISAMobile.h>
#include "move.h"

QMC5883 qmc;

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
}

void loop()
{
}