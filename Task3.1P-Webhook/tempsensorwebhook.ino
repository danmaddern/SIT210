// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>

//Pin for data sensor
#define DHTPIN D5     

//Type of device 
#define DHTTYPE DHT11		// DHT 11 

//Left - Signal
//Middle - VCC
//Right - GND

DHT dht(DHTPIN, DHTTYPE);

void setup() {
	Serial.begin(9600); 
	Serial.println("Intializing device");
	Particle.publish("state", "DHT11 device starting");

	dht.begin();
	delay(2000);
}

void loop() {

//Get Temp in C
	float t = dht.getTempCelcius();

  
// Checking for errors
	if (isnan(t)) {
		Serial.println("Failed to connect and read from sensor");
		return;
	}

	
	Serial.print("Temp: "); 
	Serial.print(t);
	Serial.print("*C ");
	Serial.println(Time.timeStr());
	//Publish data to web console 
	Particle.publish("readings", String::format("{\"Temp(°C)\": %4.2f}", t));
	//Publish to thingsspeak
	Particle.publish("Temp", String(t), PRIVATE);                                   
	delay(25000);
	
}