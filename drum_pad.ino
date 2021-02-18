const int pads[] = {A0,A1,A2,A3};
const int sensitivity = 500;  // threshold value to decide when the detected sound is a knock or not
const int numPads = (sizeof(pads)/sizeof(int *));
const int pinLed = 13;

int padReading = 0;
unsigned long lastHitMillis[] = {0,0,0};



void setup() {
  Serial.begin(9600);
  pinMode(pinLed,OUTPUT);
}

void loop() {

  // cacah list padsnya
  for(int i = 0; i < numPads; i++){
    
    unsigned long currentMillis = millis();

    /*
    Create multitasking to reading analog input
    To avoid false triggers test if the debounce delay
    period has passed
    */
    if(currentMillis - lastHitMillis[i] >= 70){
      padReading = analogRead(pads[i]);
      /*
      * if the sensor reading is greater than the sensitivity limit:
      */
      if (padReading >= sensitivity) {
        
        //Set the hit time for pseudo debouncing
        lastHitMillis[i] = millis();

        // Data disini yang dikirim ke serial communication
        Serial.write(i);

        // disini untuk menyalakan LEDnya
        digitalWrite(pinLed,HIGH);
        
      } else {
        // disini untuk mematikan lednya
        digitalWrite(pinLed,LOW);
      }
    }

  }

}
