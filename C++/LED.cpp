#include "lib/GPIO.h"
#include "lib/Pin.h"
#include "lib/PWM.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

int main(int argc, char *argv[])
{
   PWM ledRouge;
   ledRouge.enablePin(PWMP9_14);
   ledRouge.attach(PWMP9_14);
   ledRouge.writeDutyPercent(PWMP9_14,100);
   PWM ledVerte;
   ledVerte.enablePin(PWMP9_29);
   ledVerte.attach(PWMP9_29);
   ledVerte.writeDutyPercent(PWMP9_29,10);
   PWM ledBleue;
   ledBleue.enablePin(PWMP9_16);
   ledBleue.attach(PWMP9_16);
   ledBleue.writeDutyPercent(PWMP9_16,10);
   sleep(5);
   ledRouge.detach(PWMP9_14);
   ledVerte.detach(PWMP9_29);
   ledBleue.detach(PWMP9_16);
   return 0;
}

