#ifndef GPIO_H
#define GPIO_H

#include <string>

#define HIGH 1
#define LOW 0
#define INPUT "in"
#define OUTPUT "out"

class GPIO
{
public:
  GPIO();
  ~GPIO();
  bool pinMode(int pin, std::string mode);
  bool digitalWrite(int pin, int value);
  int digitalRead(int pin);
  bool freePin(int pin);

private:
  std::string DIR;

};

#endif

