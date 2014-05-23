#include "GPIO.h"

#include <iostream>
#include <fstream>
#include <sstream>

#define OPENFILEFAIL false
#define WRITEFILESUCCESS true

GPIO::GPIO()
{
  DIR = "/sys/class/gpio/";
}

GPIO::~GPIO()
{

}

/**
 * GPIO::digitalWrite
 * pin
 * mode
 * return true if the pin is open with the correct direction
 */
bool 
GPIO::pinMode(int pin, std::string mode)
{
  bool rv = WRITEFILESUCCESS;

  std::ofstream exportFile((DIR + "export").c_str());
  if(exportFile)
    exportFile << pin;
  else
    rv = OPENFILEFAIL;

  
  if(mode == INPUT || mode == OUTPUT)
  {
    std::ostringstream pinNumber;
    pinNumber << pin;
    cout << DIR + "gpio" + pinNumber.str() + "/direction";
    std::ofstream dirFile((DIR + "gpio" + pinNumber.str() + "/direction").c_str());
    if(dirFile)
      dirFile << mode;
    else
      rv = OPENFILEFAIL;
  }
  else
    rv = OPENFILEFAIL;

  return rv;
}

/**
 * GPIO::digitalWrite
 * pin
 * value
 * return true if the value is assigned to pin
 */
bool 
GPIO::digitalWrite(int pin, int value)
{
  bool rv = WRITEFILESUCCESS;

  std::ostringstream pinNumber;
  pinNumber << pin;
  std::ofstream valueFile((DIR + "gpio" + pinNumber.str() + "/value").c_str());
  if(valueFile)
    valueFile << value;
  else
    rv = OPENFILEFAIL;

  return rv;
}

/**
 * GPIO::digitalRead
 * pin
 * return the value of the pin(-1 if it fails)
 */
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

/**
 * GPIO::freePin
 * pin the pin to free
 * return if the pin is free
 */
bool 
GPIO::freePin(int pin)
{
  bool rv = WRITEFILESUCCESS;

  std::ofstream exportFile((DIR + "unexport").c_str());
  if(exportFile)
    exportFile << pin;
  else
    rv = OPENFILEFAIL;

  return rv;
}
