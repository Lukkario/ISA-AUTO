#include <Arduino.h>
#include <ISAMobile.h>


void moveForward(EngineSelector side, int level)
{
    if (side == EngineSelector::Right)
    {
        // do przodu
        digitalWrite(RIGHT_IN1, true);
  			digitalWrite(RIGHT_IN2, false);
  			analogWrite(RIGHT_PWM, level);
    }
    else if (side == EngineSelector::Left)
    {
        // do przodu
        digitalWrite(LEFT_IN1, false);
  			digitalWrite(LEFT_IN2, true);
  			analogWrite(LEFT_PWM, level);
    }
}

void moveForward(int level)
{
    moveForward(EngineSelector::Left, level);
    moveForward(EngineSelector::Right, level);
}

void moveBackwards(EngineSelector side, int level)
{
    if (side == EngineSelector::Right)
    {
        // do przodu
        digitalWrite(RIGHT_IN1, false);
  			digitalWrite(RIGHT_IN2, true);
  			analogWrite(RIGHT_PWM, -level);
    }
    else if (side == EngineSelector::Left)
    {
        // do przodu
        digitalWrite(LEFT_IN1, true);
  			digitalWrite(LEFT_IN2, false);
  			analogWrite(LEFT_PWM, -level);
    }
}

void moveBackwards(int level)
{
    moveBackwards(EngineSelector::Left, level);
    moveBackwards(EngineSelector::Right, level);
}

void turnRight(int level)
{
  moveForward(EngineSelector::Left, level);
  moveBackwards(EngineSelector::Right, level);
}

void stop(EngineSelector side)
{
    if (side == EngineSelector::Right)
    {
        // do przodu
        digitalWrite(RIGHT_IN1, true);
  			digitalWrite(RIGHT_IN2, true);
  			analogWrite(RIGHT_PWM, 0);
    }
    else if (side == EngineSelector::Left)
    {
        // do przodu
        digitalWrite(LEFT_IN1, true);
  			digitalWrite(LEFT_IN2, true);
  			analogWrite(LEFT_PWM, 0);
    }
}

void stop()
{
    stop(EngineSelector::Right);
    stop(EngineSelector::Left);
}
