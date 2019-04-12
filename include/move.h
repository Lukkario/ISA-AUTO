#include <Arduino.h>
#include <ISAMobile.h>

void moveForward(PowerSideEnum side, int speed)
{
    if (side == PowerSideEnum::Right)
    {
        // do przodu
        digitalWrite(A_PHASE, 1);
        analogWrite(A_ENABLE, speed);
    }
    else if (side == PowerSideEnum::Left)
    {
        // do przodu
        digitalWrite(B_PHASE, 1);
        analogWrite(B_ENABLE, speed);
    }
}

void stop()
{
    digitalWrite(A_PHASE, 0);
    analogWrite(A_ENABLE, 0);
    digitalWrite(B_PHASE, 0);
    analogWrite(B_ENABLE, 0);
}

void moveBackwards(PowerSideEnum side, int speed)
{
    if (side == PowerSideEnum::Right)
    {
        // do przodu
        digitalWrite(A_PHASE, 1);
        analogWrite(A_ENABLE, -speed);
    }
    else if (side == PowerSideEnum::Left)
    {
        // do przodu
        digitalWrite(B_PHASE, 1);
        analogWrite(B_ENABLE, -speed);
    }
}

void stop(PowerSideEnum side)
{
    if (side == PowerSideEnum::Right)
    {
        // do przodu
        digitalWrite(A_PHASE, 0);
        analogWrite(A_ENABLE, 0);
    }
    else if (side == PowerSideEnum::Left)
    {
        // do przodu
        digitalWrite(B_PHASE, 0);
        analogWrite(B_ENABLE, 0);
    }
}

void moveForward(int level)
{
    moveForward(PowerSideEnum::Left, level);
    moveForward(PowerSideEnum::Right, level);
}

void moveBackwards(int level)
{
    moveBackwards(PowerSideEnum::Left, level);
    moveBackwards(PowerSideEnum::Right, level);
}