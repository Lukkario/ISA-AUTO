#include <Arduino.h>
#include <math.h>
#include "ISAMobile.h"
#include "move.h"
#include "distance.h"
#include "PID.h"
#include <DueTimer.h>
#include <Fuzzy.h>

#define RESOLUTION_BOTTOM 6
#define RESOLUTION_TOP 6

int angles[] = {265, 175, 100, 21};

QMC5883 qmc;

Fuzzy *fuzzy = new Fuzzy();

float getAngle()
{
  qmc.measure();
  float angle = atan2(qmc.getY(), qmc.getX()) * (180.0 / M_PI); // convert to degrees
  return angle < 0 ? (angle + 360) : angle;
}

void init_angles()
{
  int i = 0;
  while(true)
  {
    if(i > 0)
      break;
    if(Serial1.read() == '\n')
    {
      int angle = 0;
      for(int j = 0; j < 10; j++)
      {
        angle += getAngle();
      }
      angles[i] = angle/10;
      String c = String(angles[i]);
      Serial1.write(c.c_str());
      i++;

    }
  }
  while(true)
  {
    if(Serial1.read() == '\n')
      break;
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
    Serial1.begin(9600);
    // Serial.print("Test... ");
Wire.begin();
qmc.init();
FuzzyInput *distance = new FuzzyInput(1);
FuzzySet *close = new FuzzySet(0,0, 45, 100);
distance->addFuzzySet(close);
FuzzySet *far = new FuzzySet(80,150,200,200);
distance->addFuzzySet(far);
fuzzy->addFuzzyInput(distance);

FuzzyInput *distanceSide = new FuzzyInput(2);
FuzzySet *farSide = new FuzzySet(40,80,200,200);
distanceSide->addFuzzySet(farSide);
FuzzySet *closeSide = new FuzzySet(0,0, 20, 50);
distanceSide->addFuzzySet(closeSide);
fuzzy->addFuzzyInput(distanceSide);

FuzzyOutput *speed = new FuzzyOutput(1);
FuzzySet *slow = new FuzzySet(0, 0, 60, 170);
speed->addFuzzySet(slow);
FuzzySet *fast = new FuzzySet(160, 200, 225, 225);
speed->addFuzzySet(fast);
fuzzy->addFuzzyOutput(speed);

FuzzyOutput *angle = new FuzzyOutput(2);
FuzzySet *tinyAngle = new FuzzySet(0,0,3,10);
angle->addFuzzySet(tinyAngle);
FuzzySet *hugeAngle = new FuzzySet(0,90, 90,90);
angle->addFuzzySet(hugeAngle);
fuzzy->addFuzzyOutput(angle);

FuzzyOutput *angleSide = new FuzzyOutput(3);
FuzzySet *tinyAngleSide = new FuzzySet(0,0,3,10);
angleSide->addFuzzySet(tinyAngleSide);
FuzzySet *HugeAngleSide = new FuzzySet(0,90, 90,90);
angleSide->addFuzzySet(HugeAngleSide);
fuzzy->addFuzzyOutput(angleSide);

FuzzyRuleAntecedent *ifDistanceSmall = new FuzzyRuleAntecedent();
ifDistanceSmall->joinSingle(close);
FuzzyRuleConsequent *thenSpeedSlow = new FuzzyRuleConsequent();
thenSpeedSlow->addOutput(slow);
FuzzyRule *fuzzyRule01 = new FuzzyRule(1, ifDistanceSmall, thenSpeedSlow);
fuzzy->addFuzzyRule(fuzzyRule01);

FuzzyRuleAntecedent *ifDistanceFar = new FuzzyRuleAntecedent();
ifDistanceFar->joinSingle(far);
FuzzyRuleConsequent *thenSpeedFast = new FuzzyRuleConsequent();
thenSpeedFast->addOutput(fast);
FuzzyRule *fuzzyRule02 = new FuzzyRule(2, ifDistanceFar, thenSpeedFast);
fuzzy->addFuzzyRule(fuzzyRule02);

FuzzyRuleConsequent *thenAngleTiny = new FuzzyRuleConsequent();
thenAngleTiny->addOutput(tinyAngle);
FuzzyRuleConsequent *thenAngleHuge = new FuzzyRuleConsequent();
thenAngleHuge->addOutput(hugeAngle);
FuzzyRule *fuzzyRule03 = new FuzzyRule(3, ifDistanceFar, thenAngleTiny);
FuzzyRule *fuzzyRule04 = new FuzzyRule(4, ifDistanceSmall, thenAngleHuge);
fuzzy->addFuzzyRule(fuzzyRule03);
fuzzy->addFuzzyRule(fuzzyRule04);


FuzzyRuleAntecedent *ifDistanceFarSide = new FuzzyRuleAntecedent();
ifDistanceFarSide->joinSingle(farSide);
FuzzyRuleConsequent *thenTineAngleSide = new FuzzyRuleConsequent();
thenTineAngleSide->addOutput(tinyAngleSide);
FuzzyRule *fuzzyRule05 = new FuzzyRule(5, ifDistanceFarSide, thenTineAngleSide);

FuzzyRuleAntecedent *ifDistanceCloseSide = new FuzzyRuleAntecedent();
ifDistanceCloseSide->joinSingle(closeSide);
FuzzyRuleConsequent *thenHugeAngleSide = new FuzzyRuleConsequent();
thenHugeAngleSide->addOutput(HugeAngleSide);
FuzzyRule *fuzzyRule06 = new FuzzyRule(6, ifDistanceCloseSide, thenHugeAngleSide);
fuzzy->addFuzzyRule(fuzzyRule05);
fuzzy->addFuzzyRule(fuzzyRule06);

delay(500);
// init_angles();
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

int input = getDistance(SensorSide::Front);
int input2 = getDistance(SensorSide::Right);
fuzzy->setInput(1, input);
fuzzy->setInput(2, input2);
fuzzy->fuzzify();
float output = fuzzy->defuzzify(1);
float output2 = fuzzy->defuzzify(2);
float output3 = fuzzy->defuzzify(3);
String s = String(output3);
Serial1.write(s.c_str());
Serial1.write('\n');
String s2 = String(output);
Serial1.write(s2.c_str());
Serial1.write('\n');
if(output3 >= 50)
{
  // stop();
  // delay(10000);
  moveForward(EngineSelector::Right, (int) (output-output3 - 10));
  moveForward(EngineSelector::Left, (int) (output+output3 + 10));
}
else
{
  moveForward(EngineSelector::Right, (int) (output + output2));
  moveForward(EngineSelector::Left, (int) (output - output2));
  if(input < 50)
  {
    moveForward(EngineSelector::Right, (int) (output + output2));
    moveBackwards(EngineSelector::Left, (int) (output + output2));
  }
}


// Serial.print(input);
// Serial.print(" ");
// Serial.print(input2);
// Serial.print(" ");
// Serial.print(output);
// Serial.print(" ");
// Serial.print(output2);
// Serial.print(" ");
// Serial.println(output3);
// delay(500);

}
