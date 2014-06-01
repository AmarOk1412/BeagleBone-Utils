#include "GPIO.h"
#include "Pin.h"
#include "PWM.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

int main(int argc, char *argv[])
{
   PWM servo;
   //servo.enablePin(PWMP9_14);
   servo.attach(PWMP9_14);
   servo.writePos(PWMP9_14, 180);
   sleep(1);
   servo.writeNSDegree(PWMP9_14,500000);
   sleep(1);
   servo.detach(PWMP9_14);
   /*PWM led;
   led.attach(PWMP9_14);
   led.writeDutyPercent(PWMP9_14,50);
   sleep(1);
   led.detach(PWMP9_14);*/
   return 0;
}

