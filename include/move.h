#include <Arduino.h>
#include <ISAMobile.h>
// void SetPowerLevel(PowerSideEnum side, int level)
// {
//     level = constrain(level, -255, 255);

//     if (side == PowerSideEnum::Right)
//     {
//         if (level > 0)
//         {
//             // do przodu
//             digitalWrite(A_PHASE, 1);
//             analogWrite(A_ENABLE, level);
//         }
//         else if (level < 0)
//         {
//             // do tyłu
//             digitalWrite(A_PHASE, 0);
//             analogWrite(A_ENABLE, -level);
//         }
//         else
//         {
//             // stop
//             digitalWrite(A_PHASE, 0);
//             analogWrite(A_ENABLE, 0);
//         }
//     }

//     if (side == PowerSideEnum::Left)
//     {
//         if (level > 0)
//         {
//             // do przodu
//             digitalWrite(B_PHASE, 1);
//             analogWrite(B_ENABLE, level);
//         }
//         else if (level < 0)
//         {
//             // do tyłu
//             digitalWrite(B_PHASE, 0);
//             analogWrite(B_ENABLE, -level);
//         }
//         else
//         {
//             // stop
//             digitalWrite(B_PHASE, 0);
//             analogWrite(B_ENABLE, 0);
//         }
//     }
// }
void moveForward(PowerSideEnum side, int speed) {
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

void stopAll() {
    digitalWrite(A_PHASE, 0);
    analogWrite(A_ENABLE, 0);
    digitalWrite(B_PHASE, 0);
    analogWrite(B_ENABLE, 0);
}

void moveBackwards(PowerSideEnum side, int speed) {
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

void stopSide(PowerSideEnum side) {
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