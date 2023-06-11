#include <Wire.h>
#include <ZumoShield.h>

ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

const int MAX_SPEED = 150;

int motorright = 9;
int motorrightdir  = 7;
int motorleft = 10;
int motorleftdir  = 8;

void setup()
{
  reflectanceSensors.init();
  button.waitForButton();

  delay(1000);
  int i = 0;

  while (i < 80)
  {
    if (i > 10 && i <= 30)
    {
      motors.setSpeeds(-200, 200);
    }
    else if (i > 50 && i <= 70)
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }

    reflectanceSensors.calibrate();

    delay(50);
    i++;
  }

  analogWrite(motorright, 0);
  analogWrite(motorleft, 0);

  button.waitForButton();
}

void loop()
{
  unsigned int sensors[6];

  int value = reflectanceSensors.readLine(sensors);
  movement(value);
}

void movement(int value)
{
  if (value < 2000)
  {
    digitalWrite(motorrightdir, LOW);
    digitalWrite(motorleftdir, LOW);
    analogWrite(motorright, 0);
    analogWrite(motorleft, 150);

  }
  else if (value < 2750 and value > 2000)
  {
    digitalWrite(motorrightdir, LOW);
    digitalWrite(motorleftdir, LOW);
    analogWrite(motorright, 150);
    analogWrite(motorleft, 150);
  }
  else
  {
    digitalWrite(motorrightdir, LOW);
    digitalWrite(motorleftdir, LOW);
    analogWrite(motorright, 150);
    analogWrite(motorleft, 0);
  }
}
