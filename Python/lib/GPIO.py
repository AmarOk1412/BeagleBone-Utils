import BBConst

class GPIO:
    def __init__(self):
        self.DIR = "/sys/class/gpio/"

    def pinMode(self, pin, mode):
        """Init pin"""
        open(self.DIR + "export").write(pin)
        if mode == INPUT or mode == OUTPUT:  
            open(self.DIR + "gpio" + pin + "/direction").write(mode)
  
    def digitalWrite(self, pin, value):
        """Write 0 for 0V or 1 for 5V"""
        open(self.DIR + "gpio" + pin + "/value").write(value)

    def digitalRead(self, pin):
        """Read the value of the pin"""
        return open(self.DIR + "gpio" + pin + "/value").read()

    def freePin(self, pin):
        """Release the pin"""   
        open(self.DIR + "unexport").write(pin)
        
