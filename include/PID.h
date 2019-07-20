#include <Arduino.h>
#include <DueTimer.h>
#include <ISAMobile.h>
#include "move.h"

int L_R = 0;
int R_R = 0;
int RPS = 1;
int RPS_R = 2;
int interruptInterval = 1;
int speedL = 100;
int speedR = 100;
float kp = 2;
float ki = 0.006;
float kd = 0;

float integralL = 0;
float integralR = 0;

float errorL = 0;
float errorR = 0;

void stopInterrupts();
void startInterrupts();

void calculate_rps()
{
  stopInterrupts();
  // Serial.print("R: ");
  // Serial.print(R_R);
  // Serial.print(" L: ");
  // Serial.println(L_R);

  errorL = RPS - L_R/interruptInterval;
  errorR = RPS_R - R_R/interruptInterval;

  integralL += errorL;
  integralR += errorR;

  speedL += speedL > 255 ? 0 : kp*errorL + ki*integralL;
  speedR += speedR > 255 ? 0 : kp*errorR + ki*integralR;



  Serial.print("speedR: ");
  Serial.print(speedR);
  Serial.print(" speedL: ");
  Serial.println(speedL);

  moveForward(EngineSelector::Right, speedR);
  moveForward(EngineSelector::Left, speedL);

  L_R = 0;
  R_R = 0;
  startInterrupts();
}

void left_revolution()
{
  L_R++;
}

void right_revolution()
{
  R_R++;
}


void startInterrupts()
{
  attachInterrupt(ENCODER_LEFT, left_revolution, CHANGE);
  attachInterrupt(ENCODER_RIGHT, right_revolution, CHANGE);
}

void stopInterrupts()
{
  detachInterrupt(ENCODER_LEFT);
  detachInterrupt(ENCODER_RIGHT);
}

void startTimer(int sec)
{
  Timer4.attachInterrupt(calculate_rps).start(sec * 1000 * 100);
}
