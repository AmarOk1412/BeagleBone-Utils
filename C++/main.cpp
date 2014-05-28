#include "GPIO.h"
#include "Pin.h"
#include "PWM.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

int main(int argc, char *argv[])
{
   PWM servo;
   servo.attach(PWMP9_14);
   servo.writePos(PWMP9_14, 180);
   int i = 0;
   while(i < 10000000)
   {

    ++i;
   }
   servo.writeNSDegree(PWMP9_14,500000);
   i = 0;
   while(i < 10000000)
   {

    ++i;
   }
   servo.detach(PWMP9_14);
   return 0;
}

