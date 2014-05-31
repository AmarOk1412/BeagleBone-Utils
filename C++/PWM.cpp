#include "PWM.h"
#include "Pin.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#define OPENFILEFAIL false
#define WRITEFILESUCCESS true

PWM::PWM()
{
  //enable PWM on EHRPWM1A=P9.14
  std::cout << "Writing: 6 to: /sys/kernel/debug/omap_mux/gpmc_a2" << std::endl;
  std::ofstream gpmc_a2File;
  gpmc_a2File.open("/sys/kernel/debug/omap_mux/gpmc_a2");
  gpmc_a2File.exceptions(std::ios::badbit);
  gpmc_a2File << "6" << std::endl;
  gpmc_a2File.close();

  //enable PWM on EHRPWM1B=P9.16
  std::cout << "Writing: 6 to: /sys/kernel/debug/omap_mux/gpmc_a3" << std::endl;
  std::ofstream gpmc_a3File;
  gpmc_a3File.open("/sys/kernel/debug/omap_mux/gpmc_a3");
  gpmc_a3File.exceptions(std::ios::badbit);
  gpmc_a3File << "6" << std::endl;
  gpmc_a3File.close();

  //enable PWM on EHRPWM0B=P9.31
  std::cout << "Writing: 1 to: /sys/kernel/debug/omap_mux/mcasp0_aclkx" << std::endl;
  std::ofstream mcasp0_aclkxFile;
  mcasp0_aclkxFile.open("/sys/kernel/debug/omap_mux/mcasp0_aclkx");
  mcasp0_aclkxFile.exceptions(std::ios::badbit);
  mcasp0_aclkxFile << "1" << std::endl;
  mcasp0_aclkxFile.close();

  //enable PWM on EHRPWM0A=P9.29
  std::cout << "Writing: 1 to: /sys/kernel/debug/omap_mux/mcasp0_fsx" << std::endl;
  std::ofstream mcasp0_fsxFile;
  mcasp0_fsxFile.open("/sys/kernel/debug/omap_mux/mcasp0_fsx");
  mcasp0_fsxFile.exceptions(std::ios::badbit);
  mcasp0_fsxFile << "1" << std::endl;
  mcasp0_fsxFile.close();

  //enable PWM on EHRPWM2B=P8.19
  std::cout << "Writing: 4 to: /sys/kernel/debug/omap_mux/gpmc_ad9" << std::endl;
  std::ofstream gpmc_ad9File;
  gpmc_ad9File.open("/sys/kernel/debug/omap_mux/gpmc_ad9");
  gpmc_ad9File.exceptions(std::ios::badbit);
  gpmc_ad9File << "4" << std::endl;
  gpmc_ad9File.close();

  //enable PWM on EHRPWM2A=P8.13
  std::cout << "Writing: 4 to: /sys/kernel/debug/omap_mux/gpmc_ad8" << std::endl;
  std::ofstream gpmc_ad8File;
  gpmc_ad8File.open("/sys/kernel/debug/omap_mux/gpmc_ad8");
  gpmc_ad8File.exceptions(std::ios::badbit);
  gpmc_ad8File << "4" << std::endl;
  gpmc_ad8File.close();

  std::cout << "Writing: 0 to: /sys/kernel/debug/omap_mux/ecap0_in_pwm0_out" << std::endl;
  std::ofstream ecap0_in_pwm0_outFile;
  ecap0_in_pwm0_outFile.open("/sys/kernel/debug/omap_mux/ecap0_in_pwm0_out");
  ecap0_in_pwm0_outFile.exceptions(std::ios::badbit);
  ecap0_in_pwm0_outFile << "0" << std::endl;
  ecap0_in_pwm0_outFile.close();

  std::cout << "Writing: 4 to: /sys/kernel/debug/omap_mux/mcasp0_ahclkr" << std::endl;
  std::ofstream mcasp0_ahclkrFile;
  mcasp0_ahclkrFile.open("/sys/kernel/debug/omap_mux/mcasp0_ahclkr");
  mcasp0_ahclkrFile.exceptions(std::ios::badbit);
  mcasp0_ahclkrFile << "4" << std::endl;
  mcasp0_ahclkrFile.close();

  //Init PWM Available pin tab
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

/**
* PWM::attach
* pin
* return true if the pin is correctly initialized
*/
bool 
PWM::attach(std::string pin)
{
  bool rv = WRITEFILESUCCESS;

/*  if(!pwnPin.contains(pin))
    return false;*/ 

  int isAvailable;
  std::ifstream irequestFile;
  irequest.open(("/sys/class/pwm/" + pin + "/request").c_str());
  irequest.exceptions(std::ios::badbit);
  std::string line = "";
  getline(irequest, line);
  std::istringstream buffer(line);
  buffer >> isAvailable;
  irequest.close();

  if(isAvailable != 0)
    rv = OPENFILEFAIL;

  if(!rv)
    return rv;

  std::cout << "Writing: 1 to: " << "/sys/class/pwm/" + pin + "/request" << std::endl;
  std::ofstream requestFile;
  requestFile.open(("/sys/class/pwm/" + pin + "/request").c_str());
  requestFile.exceptions(std::ios::badbit);
  requestFile << "1" << std::endl;
  requestFile.close();

  int running;
  std::ifstream irunFile;
  irunFile.open(("/sys/class/pwm/" + pin + "/run").c_str());
  irunFile.exceptions(std::ios::badbit);
  std::string line = "";
  getline(irunFile, line);
  std::istringstream buffer(line);
  buffer >> running;
  irunFile.close();

  std::ofstream runFile;
  runFile.open(("/sys/class/pwm/" + pin + "/run").c_str());

  if(running != 0)
  {  
    std::cout << "Writing: 0 to: " << "/sys/class/pwm/" + pin + "/run" << std::endl;
    runFile.exceptions(std::ios::badbit);
    runFile << "0" << std::endl;
  }
  runFile.close();

  if(!rv)
    return rv;

  std::cout << "Writing: 0 to: " << "/sys/class/pwm/" + pin + "/period_freq" << std::endl;
  std::ofstream freqFile;
  freqFile.open(("/sys/class/pwm/" + pin + "/period_freq").c_str());
  freqFile.exceptions(std::ios::badbit);
  freqFile << "50" << std::endl;
  freqFile.close();

  if(!rv)
    return rv;

  std::cout << "Writing: " << MIN_DUTY_NS << " to: " << "/sys/class/pwm/" + pin + "/duty_ns" << std::endl;
  std::ofstream dutyFile;
  dutyFile.open(("/sys/class/pwm/" + pin + "/duty_ns").c_str());
  dutyFile.exceptions(std::ios::badbit);
  dutyFile << MIN_DUTY_NS << std::endl;
  dutyFile.close();

  if(!rv)
    return rv;
  
  std::cout << "Writing: 1 to: " << "/sys/class/pwm/" + pin + "/run" << std::endl;
  runFile.open(("/sys/class/pwm/" + pin + "/run").c_str());
  runFile.exceptions(std::ios::badbit);
  runFile << "1" << std::endl;
  runFile.close();
  
  return rv;
}

/**
* PWM::detach
* pin
* return true if the pin is correctly detached
*/
bool 
PWM::detach(std::string pin)
{
/*  if(!pwnPin.contains(pin))
    return false;*/

  bool rv = WRITEFILESUCCESS;

  std::cout << "Writing: 0 to: " << "/sys/class/pwm/" + pin + "/run" << std::endl;
  std::ofstream runFile;
  runFile.open(("/sys/class/pwm/" + pin + "/run").c_str());
  runFile.exceptions(std::ios::badbit);
  runFile << "0" << std::endl;
  runFile.close();

  if(!rv)
    return rv;

  std::cout << "Writing: 0 to: " << "/sys/class/pwm/" + pin + "/request" << std::endl;
  std::ofstream requestFile;
  requestFile.open(("/sys/class/pwm/" + pin + "/request").c_str());
  requestFile.exceptions(std::ios::badbit);
  requestFile << "0" << std::endl;
  requestFile.close();
  
  return rv;
}

/**
* PWM::writePos write a Pos in degree for a servomotor
* pin
* pos
* return true if the action is correct
*/
bool 
PWM::writePos(std::string pin, int pos)
{
/*  if(!pwnPin.contains(pin))
    return false;*/

  bool rv = WRITEFILESUCCESS;

  std::cout << "Writing: " << MIN_DUTY_NS+pos*DEGREE_TO_NS << " to: " << "/sys/class/pwm/" + pin + "/duty_ns" << std::endl;
  std::ofstream dutyFile;
  dutyFile.open(("/sys/class/pwm/" + pin + "/duty_ns").c_str());
  dutyFile.exceptions(std::ios::badbit);
  dutyFile << MIN_DUTY_NS+pos*DEGREE_TO_NS << std::endl;
  dutyFile.close();
  
  return rv;
}

/**
* PWM::writeNSDegree write a Pos in NSDegree for a servomotor
* pin
* NSDegree
* return true if the action is correct
*/
bool 
PWM::writeNSDegree(std::string pin, int NSDegree)
{
/*  if(!pwnPin.contains(pin))
    return false;*/

  bool rv = WRITEFILESUCCESS;

  std::cout << "Writing: " << NSDegree << " to: " << "/sys/class/pwm/" + pin + "/duty_ns" << std::endl;
  std::ofstream dutyFile;
  dutyFile.open(("/sys/class/pwm/" + pin + "/duty_ns").c_str());
  dutyFile.exceptions(std::ios::badbit);
  dutyFile << NSDegree << std::endl;
  dutyFile.close();
  
  return rv;
}

/**
* PWM::writeFrequency write a frequency in Hertz
* pin
* frequency
* return true if the action is correct
*/
bool
PWM::writeFrequency(std::string pin, int frequency)
{
/*  if(!pwnPin.contains(pin))
    return false;*/

  bool rv = WRITEFILESUCCESS;

  std::cout << "Writing: " << frequency << " to: " << "/sys/class/pwm/" + pin + "/period_freq" << std::endl;
  std::ofstream freqFile;
  freqFile.open(("/sys/class/pwm/" + pin + "/period_freq").c_str());
  freqFile.exceptions(std::ios::badbit);
  freqFile << frequency << std::endl;
  freqFile.close();
  
  return rv;
}

/**
* PWM::writePos write a percent band large
* pin
* percent
* return true if the action is correct
*/
bool
PWM::writeDutyPercent(std::string pin, int percent)
{
/*  if(!pwnPin.contains(pin))
    return false;*/

  bool rv = WRITEFILESUCCESS;

  if(percent >= 0 && percent <= 100)
  {
    std::cout << "Writing: " << percent << " to: " << "/sys/class/pwm/" + pin + "/duty_percent" << std::endl;
    std::ofstream dutyFile;
    dutyFile.open(("/sys/class/pwm/" + pin + "/duty_percent").c_str());
    dutyFile.exceptions(std::ios::badbit);
    dutyFile << percent << std::endl;
    dutyFile.close();
  }
  else
    rv = OPENFILEFAIL;
  
  return rv;
}

/**
* PWM::writePos
* pin
* return the name of the pin
*/
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
