//https://docs.particle.io/datasheets/app-notes/an032-calling-api-from-web-page/


int ledRed = D4;    
int ledGreen = D6;
int ledBlue = D5;

//int traffcloud(String command);   

void setup() 
{
    
   
    
    //Setting the mode of the pin
    pinMode(ledRed, OUTPUT);
    pinMode(ledGreen, OUTPUT);
    pinMode(ledBlue, OUTPUT);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledGreen, HIGH);
    //Register the cloud function
    Particle.function("traffcloud", traffcloud);
}
void off(){
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledGreen, HIGH);
}
void blue(){
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledBlue, LOW);
}
void red(){
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, LOW);
}
void green(){
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledGreen, LOW);
}
void loop() 
{

}

int traffcloud(String command) 
{
    if(command.equals("red"))
    {
        red();
        return 1;
    }
    else if(command.equals("green"))
    {
        green();
        return 1;
    }
    else if (command.equals("blue"))
    {
        blue();
        return 1;
    }
    else if(command.equals("sequence"))
    {
        red();
        delay(1000);
        blue();
        delay(1000);
        green();
        delay(1000);
        off();
        return 1;
    }
    else 
        return -1;
    
    
}