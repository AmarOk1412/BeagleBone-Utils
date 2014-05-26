#include "GPIO.h"
#include "Pin.h"
#include "PWM.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

int main(int argc, char *argv[])
{
   /*GPIO gpio;
   gpio.pinMode(P9_12, OUTPUT);
   gpio.digitalWrite(P9_12, HIGH);
   gpio.digitalRead(P9_12);
   //gpio.freePin(P9_12);
   gpio.pinMode(P9_14, OUTPUT);
   gpio.digitalWrite(P9_14, HIGH);
   gpio.digitalRead(P9_14);
   //gpio.freePin(P9_14);
   gpio.pinMode(P9_16, OUTPUT);
   gpio.digitalWrite(P9_16, HIGH);
   gpio.digitalRead(P9_16);
   //gpio.freePin(P9_16);*/
   PWM servo;
   servo.attach(PWMP9_14);
   servo.writePos(PWMP9_14, 180);
   usleep(1000);
   servo.writeNSDegree(PWMP9_14,500000);
   usleep(1000);
   servo.detach(PWMP9_14);
   return 0;
}

