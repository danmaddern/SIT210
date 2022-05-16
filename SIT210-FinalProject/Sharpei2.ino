//Hardware
//LED for displaying sensor actions
int ledBlue = D2;    
int ledRed = D3;
int ledYellow = D4;
int ledGreen = D5;

//Booleans to help determine if a device is on or off
bool inTheRoom = true;
bool tvIsOn = false;
bool fanIsOn = false;
bool robotIsOn = false;
int count = 0;

//Setup
void setup() {
    //Here we setup our various LEDs
    pinMode(ledRed, OUTPUT);
    pinMode(ledGreen, OUTPUT);
    pinMode(ledBlue, OUTPUT);
    pinMode(ledYellow, OUTPUT);
    // Fan on red lit, fan off red off
    digitalWrite(ledRed, LOW);
    //TV on yellow lit, TV off yellow off
    digitalWrite(ledYellow, LOW);
    //Robot Vaccum on Blue lit, Off Blue off 
    digitalWrite(ledBlue, LOW);
    //Dog in bed Green, out of bed Green off.
    digitalWrite(ledGreen, LOW);
    Serial.begin(9600);
    //Here we make our suscribe event , this will listen for the event and then run myhandler method when its found.
    Particle.subscribe("sharpei1", myHandler);
    Particle.function("commandCloud", commandCloud);

}

// Methods

// This method runs at start and simply lights up and turns off all LEDS on board as a test to ensure its functioning.
void startupLEDTest()
{
    digitalWrite(ledBlue, HIGH);
    delay(100);
    digitalWrite(ledBlue, LOW);
    delay(100);
    digitalWrite(ledRed, HIGH);
    delay(100);
    digitalWrite(ledRed, LOW);
    delay(100);
    digitalWrite(ledYellow, HIGH);
    delay(100);
    digitalWrite(ledYellow, LOW);
    delay(100);
    digitalWrite(ledGreen, HIGH);
    delay(100);
    digitalWrite(ledGreen, LOW);
    delay(100);
}
// Function to turn Robot on
void robotOn()
{
    digitalWrite(ledBlue, HIGH); 
    Particle.publish("sharpei2", "robotOn",PUBLIC);
    robotIsOn = true;
}
// Function to turn robot off
void robotOff()
{
    digitalWrite(ledBlue, LOW); 
    Particle.publish("sharpei2", "robotOff",PUBLIC);
    robotIsOn = false;
}
// Function to turn fan on.
void fanOn()
{
    digitalWrite(ledRed, HIGH); 
    Particle.publish("sharpei2", "fanOn",PUBLIC); 
    fanIsOn = true;
}
//function to turn fan off
void fanOff()
{
    digitalWrite(ledRed, LOW);  
    Particle.publish("sharpei2", "fanOff",PUBLIC);
    fanIsOn = false;
}
// function to turn TV on
void tvOn()
{
    digitalWrite(ledYellow, HIGH);
    Particle.publish("sharpei2", "TvOn",PUBLIC);
    tvIsOn = true;
}
//function to turn TV off
void tvOff()
{
    digitalWrite(ledYellow, LOW);
    Particle.publish("sharpei2", "TvOff",PUBLIC);
    tvIsOn = false;
}
void inRoom()
{
    digitalWrite(ledGreen, HIGH);
    Particle.publish("sharpei2", "inRoom",PUBLIC); 
}

void leftRoom()
{
    digitalWrite(ledGreen, LOW);
    Particle.publish("sharpei2", "leftRoom",PUBLIC);
}

// Function to take web command and adjust LED and send IFTTT command to peform action.
int commandCloud(String command) 
{
    if(command.equals("FanOn"))
    {
        fanOn();
        return 1;
    }
    else if(command.equals("FanOff"))
    {
        fanOff();
        return 1;
    }
    else if (command.equals("RobotOn"))
    {
        robotOn();
        return 1;
    }
    else if(command.equals("RobotOff"))
    {
        robotOff();
        return 1;
    }
    else if(command.equals("TVOn"))
    {
        tvOn();
        return 1;
    }
    else if(command.equals("TVOff"))
    {
        tvOff();
        return 1;
    }
    else 
        return -1;
    
}
//Main loop

void loop() {
    
    if(count <1)
    {
      startupLEDTest();  
      count++;
    }
}

//handler
void myHandler(const char *event, const char *data)
{
  //i++;
  //Log.info("%d: event=%s data=%s", i, event, (data ? data : "NULL"));
    if (strcmp(data, "LeftRoom") == 0)
	{
		leftRoom();
	}	
	else if (strcmp(data, "InRoom") == 0)
	{
		inRoom();
	}
	if (strcmp(data, "FanOn") == 1)
	{
		fanOn();
		
	}
	else if (strcmp(data, "FanOff") == 0)
	{
		fanOff();
	}
	if (strcmp(data, "RobotOn") == 0)
	{
		robotOn();
	}
	else if (strcmp(data, "RobotOff") == 0)
	{
		robotOff();
	}
	if (strcmp(data, "TVOn") == 0)
	{
		tvOn();
	}
	else if (strcmp(data, "TVOff") == 0)
	{
		tvOff();
	}
	
}

