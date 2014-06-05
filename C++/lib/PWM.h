#ifndef PWM_H
#define PWM_H

#include <string>

#define MIN_DUTY_NS 500000
#define MAX_DUTY_NS 2000000
#define PWM_FREQUENCY 50 //Hz
#define DEGREE_TO_NS 1500000/180

class PWM
{
public:
  PWM();
  ~PWM();
  void enablePin(std::string pin);
  bool attach(std::string pin);
  bool detach(std::string pin);
  bool writePos(std::string pin, int pos);
  bool writeFrequency(std::string pin, int frequency);
  bool writeDutyPercent(std::string pin, int percent);
  bool writeNSDegree(std::string pin, int NSDegree);
  std::string PWMName(int pin);
  bool isPWMPin(std::string pin);

private:
  std::string pwnPin[8];

};

#endif

