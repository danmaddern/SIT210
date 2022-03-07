// We define MY_LED to be the LED that we want to blink. 
//
// In this tutorial, we're using the blue D7 LED (next to D7 on the Photon 
// and Electron, and next to the USB connector on the Argon and Boron).
const pin_t MY_LED = D7;

// The following line is optional, but recommended in most firmware. It 
// allows your code to run before the cloud is connected. In this case, 
// it will begin blinking almost immediately instead of waiting until 
// breathing cyan,
SYSTEM_THREAD(ENABLED);

// The setup() method is called once when the device boots.
void setup() {
  // In order to set a pin, you must tell Device OS that the pin is 
  // an OUTPUT pin. This is often done from setup() since you only need 
  // to do it once.
  pinMode(MY_LED, OUTPUT);
}

void longl(){
    digitalWrite(MY_LED, HIGH);

  delay(3s);

  digitalWrite(MY_LED, LOW);
  delay(1s);
    
}

void shortl(){
    digitalWrite(MY_LED, HIGH);

  delay(1s);
  
  digitalWrite(MY_LED, LOW);
  delay(1s);
    
}

void letterend(){
    delay(3s);
    
}
// The loop() method is called frequently.
void loop() {
    
    //D letter long short short
    longl();
    shortl();
    shortl();
    letterend();
    
    //A Letter short, long 
   
    shortl();
    longl();
    letterend();
    
    //N letter, Long Short
    
    longl();
    shortl();
    letterend();
    
   
}
