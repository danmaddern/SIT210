// This #include statement was automatically added by the Particle IDE.
#include <BH1750.h>
/*Connections
  - VCC to 3V3 or 5V
  - GND to GND
  - SCL to SCL (A5 on Arduino Uno, Leonardo, etc or 21 on Mega and Due, on
    esp8266 free selectable)
  - SDA to SDA (A4 on Arduino Uno, Leonardo, etc or 20 on Mega and Due, on
    esp8266 free selectable)
  - ADD to (not connected) or GND
ADD pin is used to set sensor I2C address. If it has voltage greater or equal
to 0.7VCC voltage (e.g. you've connected it to VCC) the sensor address will be
0x5C. In other case (if ADD voltage less than 0.7 * VCC) the sensor address
will be 0x23 (by default).

*/
//Sensor address and wire (this is a bus) I2C Library for SDA and SCL
BH1750 LightSensor(0x23, Wire);

String result;
//First we assign a bool bright to ensure that the loops dont keep spamming my email
bool bright = false;

void setup()
{
 LightSensor.begin();
//set the sensor mode for the BH1750 included library
//High Resolution Mode 2 - (generic range: 0.0 up to 27306.25 lux)
// If we are in forced mode, the BH sensor goes back to sleep after each
// measurement and we need to set it to forced mode once at this point, so
// it will take the next measurement and then return to sleep again.
// In normal mode simply does new measurements periodically.
 LightSensor.set_sensor_mode(BH1750::forced_mode_high_res2);
 Serial.begin();
}

void loop()
{
  LightSensor.make_forced_measurement();
  //Here we print the lux measurement to serial console
  Serial.println(String::format("%f lux", LightSensor.get_light_level()));
  
  delay(1000);
  
  //Here we only publish if the light sensor is bright and it has changed from being not bright
  if(LightSensor.get_light_level() >= 100 && bright == false)
  {
         result="Its Bright";
         Particle.publish("result",result , PRIVATE);
         bright = true;
  }
  //Here we only publish if the light sensor is dark and it has changed from being bright
  else if(LightSensor.get_light_level() < 100 && bright==true)
  {
         result="It just got dark";
         Particle.publish("result",result , PRIVATE);
         bright = false;
  }
    

  delay(1000);
}
