#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 102 // REV
#define SERVOMAX 592 // REV
#define PHARENDIRECT 100
#define PHAREDIRECT 600

#define LOWER_SERVO 14
#define UPPER_SERVO 15

#define LOWER_UNDEPLOYED 185
#define LOWER_DEPLOYED 40

#define UPPER_UNDEPLOYED 313
#define UPPER_DEPLOYED 2

void setAngle(int slot, int angle) {
  pwm.setPWM(slot, 0, getPWM(angle));
}

int getPWM(int angle) {
  return map(angle, 0, 300, SERVOMIN, SERVOMAX);
}

bool lock = false;

bool engaged = false;
bool switchStatus = false;

int currentPharePwm = 600;

int currentLowerPWM = 0;
int currentUpperPWM = 0;

bool isLowerDeployed = false;
int lowerProcessing = -1;

bool isUpperDeployed = false;
int upperProcessing = -1;

void setup()
{
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
  currentLowerPWM = getPWM(LOWER_UNDEPLOYED);
  currentUpperPWM = getPWM(UPPER_UNDEPLOYED);
}

void loop()
{
  if (!engaged) {
    switchStatus = !digitalRead(2);
    if (switchStatus) {
      Serial.println("Engaged! Toggle lower deployment");
      if (!isLowerDeployed) {
        lowerProcessing = LOWER_UNDEPLOYED;
      }
      if (isUpperDeployed && isLowerDeployed) {
        upperProcessing = UPPER_DEPLOYED;
      }
      engaged = true;
    }
  }
  while (Serial.available() > 0)
  {
    int inputInt = Serial.parseInt();
    // if (l == 0)
    // {
    // }
    // if (l == 2)
    // {
    //   setAngle(LOWER_SERVO, 90)
    // }
    // if (l == 2)
    // {
    //   setAngle(LOWER_SERVO, 90)
    // }
    // if (l == 3)
    // {
    //   setAngle(LOWER_SERVO, 180)
    // }
    //   setAngle(15, 300);
    //   delay(1000);
    //   setAngle(14, 0);
    // }
    // if (l == 1)
    // {
    //   pwm.setPWM(14, 0, map(90, 0, 300, SERVOMIN, SERVOMAX));
    //   delay(1000);
    //   pwm.setPWM(15, 0, map(192, 0, 300, SERVOMIN, SERVOMAX));
    // }
    // if (l == 2)
    // {
    //   isRotating = true;
    // }
    // if (l == 3)
    // {
    //   isRotating = false;
    // }
    if (inputInt > 0) {
      // currentLowerPWM = getPWM(inputInt);
      // Serial.println(inputInt);
      if (inputInt == 1) {
        lowerProcessing = isLowerDeployed ? LOWER_DEPLOYED : LOWER_UNDEPLOYED;

        Serial.println("Toggle Lower deployment!");
      }
      if (inputInt == 2) {
        upperProcessing = isUpperDeployed ? UPPER_DEPLOYED : UPPER_UNDEPLOYED;

        Serial.println("Toggle Upper deployment!");
      }
    }
  }
  // if (isRotating) {
  //   pwm.setPWM(13, 0, currentPharePwm);
  //   if (currentPharePwm == PHAREDIRECT) {
  //     currentPharePwm = PHARENDIRECT;
  //   } else {
  //     currentPharePwm = PHAREDIRECT;
  //   }
  // }
  if (lowerProcessing != -1) {
    if (!isLowerDeployed) {
      if (lowerProcessing == LOWER_DEPLOYED) {
        Serial.println("Deployed!");
        lowerProcessing = -1;
        isLowerDeployed = true;

        if (engaged) {
          Serial.println("Because engaged var is true, we automaticly carry the next deployment");
          upperProcessing = isUpperDeployed ? UPPER_DEPLOYED : UPPER_UNDEPLOYED;
        }
      } else {
        lowerProcessing--;
        Serial.println(lowerProcessing);
        currentLowerPWM = getPWM(lowerProcessing);
      }
    } else {
      if (lowerProcessing == LOWER_UNDEPLOYED) {
        Serial.println("UNDeployed!");
        lowerProcessing = -1;
        isLowerDeployed = false;

        if (engaged) {
          Serial.println("Because engaged var is true, we declare the end of the engagement");
          engaged = false;
        }
      } else {
        lowerProcessing++;
        Serial.println(lowerProcessing);
        currentLowerPWM = getPWM(lowerProcessing);
      }
    }
  }
  if (upperProcessing != -1) {
    if (!isUpperDeployed) {
      if (upperProcessing == UPPER_DEPLOYED) {
        Serial.println("Deployed!");
        upperProcessing = -1;
        isUpperDeployed = true;

        if (engaged) {
          Serial.println("Because engaged var is true, we declare the end of the engagement");
          engaged = false;
        }
      } else {
        upperProcessing--;
        Serial.println(upperProcessing);
        currentUpperPWM = getPWM(upperProcessing);
      }
    } else {
      if (upperProcessing == UPPER_UNDEPLOYED) {
        Serial.println("UNDeployed!");
        upperProcessing = -1;
        isUpperDeployed = false;

        if (engaged) {
          Serial.println("Because engaged var is true, we automaticly carry the next undeployment");
          lowerProcessing = isLowerDeployed ? LOWER_DEPLOYED : LOWER_UNDEPLOYED;
        }
      } else {
        upperProcessing++;
        Serial.println(upperProcessing);
        currentUpperPWM = getPWM(upperProcessing);
      }
    }
  }

  pwm.setPWM(LOWER_SERVO, 0, currentLowerPWM);
  pwm.setPWM(UPPER_SERVO, 0, currentUpperPWM);
  
  delay(20);
}