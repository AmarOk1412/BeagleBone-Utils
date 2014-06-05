import BBConst

class PWM:
    def __init__(self):
        self.PWMPIN = [ PWMP8_13,
                        PWMP8_19,
                        PWMP9_14,
                        PWMP9_16,
                        PWMP9_28,
                        PWMP9_29,
                        PWMP9_31,
                        PWMP9_42 ]

    def enable(self):
        open("/sys/kernel/debug/omap_mux/gpmc_a2").write('6')
        open("/sys/kernel/debug/omap_mux/gpmc_a3").write('6')
        open("/sys/kernel/debug/omap_mux/mcasp0_aclkx").write('1')
        open("/sys/kernel/debug/omap_mux/mcasp0_fsx").write('1')
        open("/sys/kernel/debug/omap_mux/gpmc_ad9").write('4')
        open("/sys/kernel/debug/omap_mux/gpmc_ad8").write('4')
        open("/sys/kernel/debug/omap_mux/mcasp0_ahclkr").write('4')
        open("/sys/kernel/debug/omap_mux/ecap0_in_pwm0_out").write('0')

    def isPWMPin(self, pin):
        return pin in self.PWMPIN

    def writeDutyPercent(self, pin, percent):
        if 0 <= percent <= 100:
            open("/sys/class/pwm/" + pin + "/duty_percent").write(str(percent))

    def writeFrequency(self, pin, freq):
        open("/sys/class/pwm/" + pin + "/period_freq").write(freq)

    def writeNSDegree(self, pin, deg):
        open("/sys/class/pwm/" + pin + "/duty_ns").write(deg)

    def writePos(self, pin, deg):
        open("/sys/class/pwm/" + pin + "/duty_ns").write(str(int(deg)*DEGREETONS))

    def detach(self, pin):
        open("/sys/class/pwm/" + pin + "/run").write('0')
        open("/sys/class/pwm/" + pin + "/request").write('0')

    def attach(self, pin):
        if open("/sys/class/pwm/" + pin + "/request").read() == '0':
            open("/sys/class/pwm/" + pin + "/run").write('1')
            if open("/sys/class/pwm/" + pin + "/run").read() != '0':
                open("/sys/class/pwm/" + pin + "/run").write('0')
            open("/sys/class/pwm/" + pin + "/period_freq").write(50)
            open("/sys/class/pwm/" + pin + "/duty_ns").write(500000)
            open("/sys/class/pwm/" + pin + "/run").write('1')
            
        
    
        
