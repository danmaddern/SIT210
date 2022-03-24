
from tkinter import *
import tkinter.font
import RPi.GPIO as GPIO
from gpiozero import LED

import time

#hardware
GPIO.setmode(GPIO.BOARD)

GPIO.setup(11, GPIO.OUT)

GPIO.setup(12, GPIO.OUT)

GPIO.setup(13, GPIO.OUT)

ledblue = LED(12)
ledred = LED(13)
ledgreen = LED(11)

##GUI Def
win = Tk()
win.title("LED BLINK GUI")
myFont = tkinter.font.Font(family = 'Helvetica', size = 12, weight = "bold")


#Event Functions
def redToggle():
	GPIO.output(11, GPIO.HIGH)
	GPIO.output(12, GPIO.HIGH)
	GPIO.output(13, GPIO.LOW)

def blueToggle():
	GPIO.output(11, GPIO.HIGH)
	GPIO.output(12, GPIO.LOW)
	GPIO.output(13, GPIO.HIGH)
	
		
def greenToggle():
	GPIO.output(11, GPIO.LOW)
	GPIO.output(12, GPIO.HIGH)
	GPIO.output(13, GPIO.HIGH)
	
def closed():
	win.quit()
	win.destroy()
	GPIO.cleanup()
	exit()


#widgets
ledButton1 = Button(win, text = "Turn Red LED on", font = myFont, command = redToggle, bg = 'bisque2', height = 1, width = 24)
ledButton1.grid(row=0, column =0)

ledButton2 = Button(win, text = "Turn Blue LED on", font = myFont, command = blueToggle, bg = 'orange', height = 1, width = 24)
ledButton2.grid(row=1, column =0)

ledButton3 = Button(win, text = "Turn Green LED on", font = myFont, command = greenToggle, bg = 'bisque2', height = 1, width = 24)
ledButton3.grid(row=2, column =0)

ledButton4 = Button(win, text = "EXIT", font = myFont, command = closed, bg = 'grey', height = 1, width = 24)
ledButton4.grid(row=3, column =0)

mainloop()