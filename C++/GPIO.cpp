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

  std::cout << "Writing: " << pin << " to: " << DIR << "export" << std::endl;
  std::ofstream exportFile;
  exportFile.open((DIR + "export").c_str());
  exportFile.exceptions(std::ios::badbit);
  exportFile << pin << std::endl;
  exportFile.close();
  
  if(mode == INPUT || mode == OUTPUT)
  {
    std::ostringstream pinNumber;
    pinNumber << pin;
    std::cout << "Writing: " << mode << " to: " << DIR + "gpio" + pinNumber.str() + "/direction" << std::endl;
    std::ofstream dirFile;
    dirFile.open((DIR + "gpio" + pinNumber.str() + "/direction").c_str());
    dirFile.exceptions(std::ios::badbit);
    dirFile << mode << std::endl;
    dirFile.close();
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

  std::cout << "Writing: " << value << " to: " << DIR + "gpio" + pinNumber.str() + "/value" << std::endl;
  std::ofstream valueFile;
  valueFile.open((DIR + "gpio" + pinNumber.str() + "/value").c_str());
  valueFile.exceptions(std::ios::badbit);
  valueFile << value << std::endl;
  valueFile.close();

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

  std::ifstream valueFile;
  valueFile.open((DIR + "gpio" + pinNumber.str() + "/value").c_str());
  valueFile.exceptions(std::ios::badbit);
  std::string line = "";
  getline(valueFile, line);
  std::istringstream buffer(line);
  buffer >> rv;
  valueFile.close();

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

  std::cout << "Writing: " << pin << " to: " << DIR << "unexport" << std::endl;
  std::ofstream unexportFile;
  unexportFile.open((DIR + "unexport").c_str());
  unexportFile.exceptions(std::ios::badbit);
  unexportFile << pin << std::endl;
  unexportFile.close();

  return rv;
}
