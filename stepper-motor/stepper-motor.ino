#include <AccelStepper.h>
int STEP = 4; // Pulse pin
int DIR  = 5; // Direction pin
int ENA = 6; // Enable pin
int BUTTON = 2; // Button pin
long RPM = 300; 
long SPR = 400; // Steps per revolution
long SPS; // Steps per second, se entrega en setSpeed()
AccelStepper stepper(1, STEP, DIR); // Construct a stepper in driver mode (1)

void setup()
{ 
  pinMode(BUTTON, INPUT_PULLUP);
  stepper.setEnablePin(ENA);
  stepper.setPinsInverted(0, 0, 1);
  stepper.enableOutputs();

  stepper.setMaxSpeed(10000);	
  stepper.setAcceleration(1000);
  SPS = ((RPM * SPR) / 60);
  stepper.setSpeed(SPS);

  attachInterrupt(digitalPinToInterrupt(BUTTON), backStep, RISING);
}

void loop()
{  
  int buttonVal = digitalRead(BUTTON);
  if (buttonVal == LOW) {
    stepper.runSpeed();
  }
}

void backStep() {
  stepper.stop();
  stepper.setCurrentPosition(0);
  stepper.runToNewPosition(-(SPR/2));
}