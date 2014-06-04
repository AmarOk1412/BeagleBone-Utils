#include "lib/GPIO.h"
#include "lib/Pin.h"
#include "lib/PWM.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

int main(int argc, char *argv[])
{
  PWM servo;
  servo.enablePin(PWMP9_14);
  servo.attach(PWMP9_14);
  servo.writePos(PWMP9_14, 0);
  sleep(1);  
  servo.writePos(PWMP9_14, 180);
  sleep(1);
  servo.writePos(PWMP9_14, 0);
  sleep(1);  
  servo.writePos(PWMP9_14, 180);
  sleep(1);
  servo.writePos(PWMP9_14, 0);
  sleep(1);  
  servo.writePos(PWMP9_14, 180);
  sleep(5);
  servo.detach(PWMP9_14);
  return 0;
}

