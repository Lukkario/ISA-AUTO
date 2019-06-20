#define FRONT_T US_FRONT_TRIGGER_PIN
#define BACK_T  US_BACK_TRIGGER_PIN
#define LEFT_T  US_LEFT_TRIGGER_PIN
#define RIGHT_T US_RIGHT_TRIGGER_PIN

#define FRONT_E US_FRONT_ECHO_PIN
#define BACK_E  US_BACK_ECHO_PIN
#define LEFT_E  US_LEFT_ECHO_PIN
#define RIGHT_E US_RIGHT_ECHO_PIN

#define SAMPLES 5

enum SensorSide
{
  Front,
  Back,
  Left,
  Right
};

int measureSoundSpeed(int trigger_pin, int echo_pin)
{
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  int duration = pulseIn(echo_pin, HIGH);
  return (int)((float)duration * 0.03438f * 0.5f);
}

int getDistance(SensorSide side)
{
  switch (side) {
    case Front:
      return measureSoundSpeed(FRONT_T, FRONT_E);
      break;
    case Back:
      return measureSoundSpeed(BACK_T, BACK_E);
      break;
    case Left:
      return measureSoundSpeed(LEFT_T, LEFT_E);
      break;
    case Right:
      return measureSoundSpeed(RIGHT_T, RIGHT_E);
      break;
  }
}

int getSampledDistance(SensorSide side)
{
  int sum = 0;
  for(int i = 0; i < SAMPLES; i++)
  {
    sum += getDistance(side);
  }
  return (int)(sum/SAMPLES);
}
