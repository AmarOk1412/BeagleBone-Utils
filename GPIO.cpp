#include "GPIO.h"

#include <iostream>
#include <fstream>
#include <sstream>

GPIO::GPIO()
{
  DIR = "/sys/class/gpio/";
}

GPIO::~GPIO()
{

}

bool 
GPIO::pinMode(int pin, std::string mode)
{
  int rv = WRITEFILESUCCESS;

  std::ofstream exportFile((DIR + "export").c_str());
  if(exportFile)
    exportFile << pin;
  else
    rv = OPENFILEFAIL;

  
  std::ostringstream pinNumber;
  pinNumber << pin;
  std::ofstream dirFile((DIR + "gpio" + pinNumber.str() + "/direction").c_str());
  if(dirFile)
    dirFile << mode;
  else
    rv = OPENFILEFAIL;

  return rv;
}

bool 
GPIO::digitalWrite(int pin, int value)
{
  int rv = WRITEFILESUCCESS;

  std::ostringstream pinNumber;
  pinNumber << pin;
  std::ofstream valueFile((DIR + "gpio" + pinNumber.str() + "/value").c_str());
  if(valueFile)
    valueFile << value;
  else
    rv = OPENFILEFAIL;

  return rv;
}

int 
GPIO::digitalRead(int pin)
{
  int rv = -1;

  std::ostringstream pinNumber;
  pinNumber << pin;
  std::ifstream valueFile((DIR + "gpio" + pinNumber.str() + "/value").c_str());
  if(valueFile)
  {
    std::string line = "";
    getline(valueFile, line);
    std::istringstream buffer(line);
    buffer >> rv;
  }

  return rv;
}

bool 
GPIO::freePin(int pin)
{
  int rv = WRITEFILESUCCESS;

  std::ofstream exportFile((DIR + "unexport").c_str());
  if(exportFile)
    exportFile << pin;
  else
    rv = OPENFILEFAIL;

  return rv;
}
