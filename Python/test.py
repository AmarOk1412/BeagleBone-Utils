import time
import pwm #Used to enable PWM
from servo import Servo

#You can use your own method to enable PWM, but this just works
pwm.enable();


servoBase = Servo()
servoBase.attach("P9_14")
servoMiddle = Servo()
servoMiddle.attach("P9_16")
servoHead1 = Servo()
servoHead1.attach("P9_29")
servoHead2 = Servo()
servoHead2.attach("P9_31")
continueB = True 
while continueB:
  ligne = raw_input('exit|-b pos|-m pos|-h1 pos|-h2 pos\n')
  if ligne == 'exit':
    continueB = False
  if ligne[:2] == '-b':
    servoBase.write(int(ligne[3:]))
  if ligne[:2] == '-m':
    servoMiddle.write(int(ligne[3:]))
  if ligne[:3] == '-h1':
    servoHead1.write(int(ligne[4:]))
  if ligne[:3] == '-h2':
    servoHead2.write(int(ligne[4:]))
  

servoBase.detach()
servoMiddle.detach()
servoHead1.detach()
servoHead2.detach()
