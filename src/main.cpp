#include <Arduino.h>
#include <math.h>
#include "ISAMobile.h"
#include "move.h"
#include "distance.h"
#include "PID.h"
#include <DueTimer.h>

void setup()
{

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
    // moveForward(120);
    startTimer(interruptInterval);
    startInterrupts();
}


void loop()
{

}
