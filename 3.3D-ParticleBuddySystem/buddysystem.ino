
//LED built in on the Particle Argon
int led = D7;


void setup() {
    Serial.begin(9600);
    pinMode(led, OUTPUT);
    //Here we make our suscribe event , this will listen for the event and then run myhandler method when its found.
    Particle.subscribe("buddytest", myHandler);

}

void loop() {

    //10 second delay between publishes
    //Publish the buddy wave event 
	Particle.publish("buddytest", "wave");
	delay(10000);
	//publish buddy Pat event 
	Particle.publish("buddytest", "pat");
	delay(10000);
}

void fastblink(){
    //loop to blink 5 times fast
    for(int i=0; i<5; i++){
		digitalWrite(led, HIGH);
		//delay 2 secs
	    delay(200);
	    //Turn LED off
	    digitalWrite(led, LOW);
	    delay(200);
	    //turn LED ON
    	}
}
void slowblink(){
     //loop for 3 slow blinks
	for(int i=0; i<3; i++){
		digitalWrite(led, HIGH);
		//delay 2 secs
	    delay(1500);
	    //Turn LED off
	    digitalWrite(led, LOW);
	    delay(1500);
	    //turn LED ON
    	}
}
void myHandler(const char *event, const char *data)
{
  //i++;
  //Log.info("%d: event=%s data=%s", i, event, (data ? data : "NULL"));
  if (strcmp(data, "wave") == 0)
	{
	    //when we get a wave we get a slow blink 3 times
		Serial.println("wave");
		slowblink();
		  
	}	
	else if (strcmp(data, "pat") == 0)
	{
		//When we get a pat we send a string of fast blinking LEDS 5 times
		Serial.println("pat");
	    fastblink();
	}
	
}
