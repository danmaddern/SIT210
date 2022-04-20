from smbus import SMBus
import time
import sys

#Hardware
# Address of BH1750 at pin low,
ADDR = 0x23 
# One time high res mode, start measurement at 1lx resolution.        
MODE = 0x20 
# System Management Bus is a interface. RPi and BH1750 communicate through it.
bus = SMBus(1) 

#Functions

def main():
    while True:
        # read 2 bytes in the bus
        data = bus.read_word_data(ADDR, MODE)
        # Flip the bytes
        data = ((data & 0xff) << 8) | (data >> 8)
        # from BH1750 datasheet calcualtion
        light_level = data / 1.2 
        if light_level < 20:
            print("Too Dark")
        elif light_level >= 20 and light_level < 50:
            print("Dark")
        elif light_level >= 50 and light_level < 250:
            print("medium")
        elif light_level >= 250 and light_level <500:
            print("Bright")
        else:
            print("Too Bright")
        # sleep 2 sec
        time.sleep(2) 

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted')
        sys.exit(0)
