#include <AccelStepper.h>
int STEP = 4; // Pulse pin
int DIR  = 5; // Direction pin
int ENA = 6; // Enable pin
int BUTTON = 1 // Button pin
long RPM = 200; 
long SPR = 400; // Steps per revolution
long SPS; // Steps per second
AccelStepper stepper(1, STEP, DIR);

void setup()
{ 
  pinMode(BUTTON, INPUT_PULLUP);

  SPS = (RPM * SPR) / 60;

  stepper.setEnablePin(ENA);
  stepper.setPinsInverted(0, 0, 1);
  stepper.enableOutputs();
   
  stepper.setMaxSpeed(1000);	
  stepper.setAcceleration(1000);
  stepper.setSpeed(SPS); 

  attachInterrupt(digitalPinToInterrupt(BUTTON), backStep, RISING);
}

void loop()
{ 
  int buttonValue = digitalRead(BUTTON);
  if (buttonValue == LOW) {
    stepper.run();
}

void backStep()
{
  stepper.stop();
  stepper.runToNewPosition(-SPR/2);
}