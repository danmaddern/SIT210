from tkinter import *
import tkinter.font
import time
import RPi.GPIO as GPIO
from gpiozero import LED
GPIO.setmode(GPIO.BCM)


#hardware
#pin 13 is GPIO 27
LED =27
GPIO.setup(LED, GPIO.OUT)

#Widgets/Windows
win = Tk()
win.title("GUI Morse Code")
Font_style = tkinter.font.Font( family = 'Arial', size = 18, weight = "bold")
#Software

#copied morse code chart into an array for passing into the program
#Program Variables
MorseChart = {
#characters
'a' : '.-' ,
'b' : '-...' ,
'c' : '-.-.' ,
'd' : '-..' ,
'e' : '.' ,
'f' : '..-.' ,
'g' : '--.' ,
'h' : '....' ,
'i' : '..' ,
'j' : '.---' ,
'k' : '-.-' ,
'l' : '.-..' ,
'm' : '--' ,
'n' : '-.' ,
'o' : '---' ,
'p' : '.--.' ,
'q' : '--.-' ,
'r' : '.-.' ,
's' : '...' ,
't' : '-' ,
'u' : '..-' ,
'v' : '...-' ,
'w' : '.--' ,
'x' : '-..-' ,
'y' : '-.--' ,
'z' : '--..' ,
#Numbers
'0' : '-----' , 
'1' : '.----' ,
'2' : '..---' ,
'3' : '...--' ,
'4' : '....-' ,
'5' : '.....' ,
'6' : '-....' ,
'7' : '--...' ,
'8' : '---..' ,
'9' : '----.'
	
}

#Functions
def Dash():
    GPIO.output(LED, GPIO.HIGH)
    time.sleep(0.3)
    GPIO.output(LED, GPIO.LOW)
    time.sleep(0.15)
    
def Dot():
    GPIO.output(LED, GPIO.HIGH)
    time.sleep(0.15)
    GPIO.output(LED, GPIO.LOW)
    time.sleep(0.15)

def RunTask():
	USER_INPUT = USER_INPUT_TEXT.get()
	for alphabet in USER_INPUT:
		for dot_dash in MorseChart[alphabet.lower()]:
			if dot_dash == '-':
				Dash()
			elif dot_dash == '.':
				Dot()
			else:
				time.sleep(0.15)
			time.sleep(1) 

USER_INPUT_TEXT = Entry(win, font = Font_style, width = 25)
USER_INPUT_TEXT.grid(row = 0, column = 0)

Button = Button(win, text = 'Send Message Now', font = Font_style, command = RunTask, height = 3, width = 15)
Button.grid( row =1, column = 0)

win.mainloop()