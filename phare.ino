#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 102 // REV
#define SERVOMAX 592 // REV
#define PHARENDIRECT 100
#define PHAREDIRECT 600

bool isRotating = false;
bool isDirect = false;
int currentPharePwm = 600;

void setup()
{
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
}

void loop()
{
  while (Serial.available() > 0)
  {
    int l = Serial.parseInt();
    if (l == 0)
    {
      pwm.setPWM(15, 0, map(0, 0, 300, SERVOMIN, SERVOMAX));
      delay(1000);
      pwm.setPWM(14, 0, map(0, 0, 300, SERVOMIN, SERVOMAX));
    }
    if (l == 1)
    {
      pwm.setPWM(14, 0, map(90, 0, 300, SERVOMIN, SERVOMAX));
      delay(1000);
      pwm.setPWM(15, 0, map(192, 0, 300, SERVOMIN, SERVOMAX));
    }
    if (l == 2)
    {
      isRotating = true;
    }
    if (l == 3)
    {
      isRotating = false;
    }
  }
  if (isRotating) {
    pwm.setPWM(13, 0, currentPharePwm);
    if (currentPharePwm == PHAREDIRECT) {
      currentPharePwm = PHARENDIRECT;
    } else {
      currentPharePwm = PHAREDIRECT;
    }
  }
  delay(1000);
}
