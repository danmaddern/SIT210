#Libraries
import RPi.GPIO as GPIO        
import time

#hardware Setup

#the GPIO 27 for LED
led = 27  
#the GPIO 22 for trigger                
trigger = 22  
#the GPIO 23 for echo           
echo = 23                      

#GPIO Mode (BOARD / BCM)
GPIO.setmode(GPIO.BCM)         

#GPIO Pins (OUT / IN)
GPIO.setup(led, GPIO.OUT)      
GPIO.setup(trigger, GPIO.OUT) 
GPIO.setup(echo, GPIO.IN)      

#GPIO PWM
# Create a PWM object
pwm = GPIO.PWM(led, 100)  
# Start PWM at 0% duty cycle     
pwm.start(0)                  


#Functions

def getDistance():
    #trigger settings
    
	# set Trigger to HIGH
    GPIO.output(trigger, True) 

    # set Trigger after 0.01ms to LOW
    time.sleep(0.00001)
    GPIO.output(trigger, False)
    
    # Time settings
    Start = time.time()
    Stop = time.time()

    # record the  StartTime
    while GPIO.input(echo) == 0:
        Start = time.time()

    # save time of arrival
    while GPIO.input(echo) == 1:
        Stop = time.time()
    
    #calculate time
    TimeElapsed = Stop - Start
    
    # multiply with the sonic speed and divide by 2
    distance = (TimeElapsed * 34300) / 2

    return distance

try:
	# Loop will until interrupted
    while 1:                     
        #create a variable for distance, call distance function and print this to console
        distancefound = getDistance()
        print ("Distance to target = %.1f cm" % distancefound) 
        #here we say if the distance is over 250 cm the light is off
        if (distancefound > 150):         
            x = 0   
        #if the distance is not over 150 cm we turn the LED on.
        else:
            # as we want the light to get brighter we divide the brightness by distnace.
            if (distancefound <5):
                x = 100 
            elif(distancefound <50):
                x = 50
            elif(distancefound < 100):
                x = 25
            elif(distancefound < 149):
                x = 5
        # Change duty cycle
        pwm.ChangeDutyCycle(x)  
        #add a delay of 0.05 seconds 
        time.sleep(0.05)         

# Add an exception in prep for main project using error handling
# In this case we break if the keyboard is pressed.
except KeyboardInterrupt:
    pass  
    #stop the PWM
    pwm.stop()

    #reset all devices to off and 0 as part of clean up      
    GPIO.cleanup()  