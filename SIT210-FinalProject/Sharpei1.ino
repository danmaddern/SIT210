// Libraries included
#include <HC_SR04.h>
#include <Adafruit_DHT.h>

#define DHTTYPE DHT11
#define DHTPIN D8
#define LEDPIN D7
// System consts
const int trigPin = D5;
const int echoPin = D4;
// System Variables
double Distance = 0.0;
double inches = 0.0;
bool beam_status = false;
bool inBed = true;
bool fanOn = false;
bool tvOn = false;
bool robotOn = false;
int vaccumRunCount = 0;
int ErrorCount = 0;
// Set range finder for HC SR04 ultrasonic sensor
HC_SR04 rangefinder = HC_SR04(trigPin, echoPin);

DHT dht(DHTPIN, DHTTYPE);
// Hardware Setup and intitilization.
void setup()
{

    Serial.begin(9600);
    Spark.variable("Distance", &Distance, DOUBLE);
    Spark.variable("inches", &inches, DOUBLE);
    // Print to Console to inform of state of system.
    Serial.println("Intializing device");
    Particle.publish("state", "DHT11 device starting");
    Particle.publish("state", "HCSR04 device starting");
    // Call the DHT11 begin function

    dht.begin();
    delay(2000);
}

// Program Functions

//This function reads the distance and returns the distance.
double readDistance()
{
    Distance = rangefinder.getDistanceCM();
    inches = rangefinder.getDistanceInch();
    delay(100);
    Particle.publish("Distance", (String)Distance);
    return Distance;
}
// Determine if there is a change in distance
bool distanceChange(double distance)
{
    // distance = rangefinder.getDistanceCM();
    if (distance < 25)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// This function takes a temp reading and returns the value t for tmep.
float readTemp()
{
    float t = dht.getTempCelcius();
    return t;
}

//This function returns a bool value and determines if the temp is too hot
bool tooHotCheck(float t)
{
    if (t > 10)
        return true;
    else
        return false;
}
// This function takes the Temp and outputs it to the console.
void printTemp(float t)
{
    // info around temp settings
    Serial.print("Temp: ");
    Serial.print(t);
    Serial.print("*C ");
    Serial.println(Time.timeStr());
    Particle.publish("readings", String::format("{\"Temp(°C)\": %4.2f}", t));
    Particle.publish("Temp", String(t), PRIVATE);
}

bool validDistance(double Distance)
{
    if (Distance <= 0)
    {
        Serial.println("No valid reading was detected : ");
        return false;
    }
    else
    {
        return true;
    }
}
void loop()
{
    // First we ensure that we are getting correct readings by validating the Distance reading, if we get 5 failed readings in a row we reboot the device
    if(ErrorCount > 5)
    {
       System.reset();
    }
    if (validDistance(readDistance()) == true)
    {
        // Check if the dog is in Bed, if it is check the devices that need to be turned on or off
        if (inBed == true)
        {
            Particle.publish("sharpei1", "InRoom", PUBLIC);
            Serial.println("The dog is currently in Bed");

            float t = readTemp();
            // Error checking temp reading
            if (isnan(t))
            {
                Serial.println("Failed to connect and read from sensor");
                return;
            }
            else
            {
                printTemp(t);
                if (tooHotCheck(readTemp()) == true)
                {
                    // Here we publish Fan on which sharpei2 will receive as the temp is too warm.
                    Particle.publish("sharpei1", "FanOn", PUBLIC);
                    Serial.println("Its too hot turning Fan on");
                }
                else if (fanOn == true)
                {
                    // Here we publish Fan off which sharpei 2 will receive
                    Particle.publish("sharpei1", "FanOff", PUBLIC);
                    Serial.println("The Temp is Fine so Fan is not on");
                }
            }

            if (vaccumRunCount < 2)
            {
                // Here we publish Robot Vaccum on which Sharpei 2 will receive 
                Particle.publish("sharpei1", "RobotOn", PUBLIC);
                Serial.println("Robot Vaccum Enabled");
                vaccumRunCount++;
            }
            else
            {
                //Here we publish Vaccum has max runs for the day which Sharpei2 will receive
                Particle.publish("sharpei1", "VaccumMaxRuns", PUBLIC);
                Serial.println("Vaccum Has already run twice today ");
            }
            if (tvOn == true)
            {
                //Here we publish TVoff which Sharpei2 will receive
                Particle.publish("sharpei1", "TVOff", PUBLIC);
                Serial.println("Turning the TV off");
                tvOn = false;
            }

            delay(100);
        }
        // Loop to hold the program untill the status changes from in bed to outofbed.
        while (inBed == true)
        {
            beam_status = distanceChange(readDistance());
            if (beam_status == false)
            {
                inBed = false;
            }
        }

        // Here we check if the dog is not in bed and publish the devices that need to be changed when the dog is not in bed.
        if (inBed == false)
        {
            //Here we publish that the dog left the bedroom  which Sharpei2 will receive
            Particle.publish("sharpei1", "LeftRoom", PUBLIC);
            Serial.println("The dog is out of bed.");

            if (fanOn == true)
            {
                //Here we publish FanOff which Sharpei2 will receive
                Particle.publish("sharpei1", "FanOff", PUBLIC);
                Serial.println("Turning the fan off");
                fanOn = false;
            }
            if (tvOn == false)
            {
                //Here we publish TVon which Sharpei2 will receive
                Particle.publish("sharpei1", "TVOn", PUBLIC);
                Serial.println("Turning the TV on");
                tvOn = true;
            }
            if (robotOn == true)
            {
                //Here we publish RobotStop which Sharpei2 will receive
                Particle.publish("sharpei1", "RobotStop", PUBLIC);
                Serial.println("Turning the Robot Vaccum off");
                robotOn = false;
            }
        }
        // While loop to hold program untill the status changes from out of bed to inbed.
        while (inBed == false)
        {
            beam_status = distanceChange(readDistance());
            if (beam_status == false)
            {
                inBed = true;
            }
        }
    }
    else
    {
        ErrorCount++;
    }
}