#include "PWM.h"
#include "Pin.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define OPENFILEFAIL false
#define WRITEFILESUCCESS true

PWM::PWM()
{
  /*int MMAP_OFFSET = 0x44c00000;
  int MMAP_SIZE   = 0x48ffffff-MMAP_OFFSET;
  int CM_PER_BASE = 0x44e00000 - MMAP_OFFSET;
  int CM_PER_EPWMSS1_CLKCTRL = CM_PER_BASE + 0xcc;
  int CM_PER_EPWMSS0_CLKCTRL = CM_PER_BASE + 0xd4;
  int CM_PER_EPWMSS2_CLKCTRL = CM_PER_BASE + 0xd8;
  TODO
  std::ofstream gpmc_a2File("/sys/kernel/debug/omap_mux/gpmc_a2");
  if(gpmc_a2File)
    gpmc_a2File << "6";
  std::ofstream gpmc_a3File("/sys/kernel/debug/omap_mux/gpmc_a3");
  if(gpmc_a3File)
    gpmc_a3File << "6";
  std::ofstream mcasp0_aclkxFile("/sys/kernel/debug/omap_mux/mcasp0_aclkx");
  if(mcasp0_aclkxFile)
    mcasp0_aclkxFile << "1";
  std::ofstream mcasp0_fsxFile("/sys/kernel/debug/omap_mux/mcasp0_fsx");
  if(mcasp0_fsxFile)
    mcasp0_fsxFile << "1";
  std::ofstream gpmc_ad9File("/sys/kernel/debug/omap_mux/gpmc_ad9");
  if(gpmc_ad9File)
    gpmc_ad9File << "4";
  std::ofstream gpmc_ad8File("/sys/kernel/debug/omap_mux/gpmc_ad8");
  if(gpmc_ad8File)
    gpmc_ad8File << "4";
  std::ofstream ecap0_in_pwm0_outFile("/sys/kernel/debug/omap_mux/ecap0_in_pwm0_out");
  if(ecap0_in_pwm0_outFile)
    ecap0_in_pwm0_outFile << "0";
  std::ofstream mcasp0_ahclkrFile("/sys/kernel/debug/omap_mux/mcasp0_ahclkr");
  if(mcasp0_ahclkrFile)
    mcasp0_ahclkrFile << "4";*/
  system("python ../Python/pwmenable.py");
  pwnPin[0] = PWMP8_13;
  pwnPin[1] = PWMP8_19;
  pwnPin[2] = PWMP9_14;
  pwnPin[3] = PWMP9_16;
  pwnPin[4] = PWMP9_28;
  pwnPin[5] = PWMP9_29;
  pwnPin[6] = PWMP9_31;
  pwnPin[7] = PWMP9_42;
}

PWM::~PWM()
{

}

bool 
PWM::attach(std::string pin)
{
  bool rv = WRITEFILESUCCESS;

/*  if(!pwnPin.contains(pin))
    return false;*/

  std::ofstream requestFile(("/sys/class/pwm/" + pin + "/request").c_str());
  if(requestFile)
    requestFile << "1";
  else
    rv = OPENFILEFAIL;

  if(!rv)
    return rv;

  std::ofstream runFile(("/sys/class/pwm/" + pin + "/run").c_str());
  if(runFile)
    runFile << "0";
  else
    rv = OPENFILEFAIL;

  if(!rv)
    return rv;

  std::ofstream freqFile(("/sys/class/pwm/" + pin + "/period_freq").c_str());
  if(freqFile)
    freqFile << "50";
  else
    rv = OPENFILEFAIL;

  if(!rv)
    return rv;

  std::ofstream dutyFile(("/sys/class/pwm/" + pin + "/duty_ns").c_str());
  if(dutyFile)
    dutyFile << MIN_DUTY_NS;
  else
    rv = OPENFILEFAIL;

  if(!rv)
    return rv;

  if(runFile)
    runFile << "1";
  else
    rv = OPENFILEFAIL;
  
  return rv;
}

bool 
PWM::detach(std::string pin)
{
/*  if(!pwnPin.contains(pin))
    return false;*/

  bool rv = WRITEFILESUCCESS;

  std::ofstream runFile(("/sys/class/pwm/" + pin + "/run").c_str());
  if(runFile)
    runFile << "0";
  else
    rv = OPENFILEFAIL;

  if(!rv)
    return rv;

  std::ofstream requestFile(("/sys/class/pwm/" + pin + "/request").c_str());
  if(requestFile)
    requestFile << "0";
  else
    rv = OPENFILEFAIL;
  
  return rv;
}

bool 
PWM::writePos(std::string pin, int pos)
{
/*  if(!pwnPin.contains(pin))
    return false;*/

  bool rv = WRITEFILESUCCESS;

  std::ofstream runFile(("/sys/class/pwm/" + pin + "/run").c_str());
  if(runFile)
    runFile << "0";
  else
    rv = OPENFILEFAIL;

  std::ofstream dutyFile(("/sys/class/pwm/" + pin + "/duty_ns").c_str());
  if(dutyFile)
    dutyFile << MIN_DUTY_NS+pos*DEGREE_TO_NS;
  else
    rv = OPENFILEFAIL;

  if(runFile)
    runFile << "1";
  else
    rv = OPENFILEFAIL;
  
  return rv;
}

bool 
PWM::writeNSDegree(std::string pin, int NSDegree)
{
/*  if(!pwnPin.contains(pin))
    return false;*/

  bool rv = WRITEFILESUCCESS;

  std::ofstream dutyFile(("/sys/class/pwm/" + pin + "/duty_ns").c_str());
  if(dutyFile)
    dutyFile << NSDegree;
  else
    rv = OPENFILEFAIL;
  
  return rv;
}

bool
PWM::writeFrequency(std::string pin, int frequency)
{
/*  if(!pwnPin.contains(pin))
    return false;*/

  bool rv = WRITEFILESUCCESS;

  std::ofstream freqFile(("/sys/class/pwm/" + pin + "/period_freq").c_str());
  if(freqFile)
    freqFile << frequency;
  else
    rv = OPENFILEFAIL;
  
  return rv;
}

std::string 
PWM::PWMName(int pin)
{
  if(pin == P8_13)
    return "ehrpwm.2:1";
  else if(pin == P8_19)
    return "ehrpwm.2:0";
  else if(pin == P9_14)
    return "ehrpwm.1:0";
  else if(pin == P9_16)
    return "ehrpwm.1:1";
  else if(pin == P9_42)
    return "ecap.0";
  else 
    return "";
}

bool 
PWM::isPWMPin()
{
  //TODO...
  return true;
}
