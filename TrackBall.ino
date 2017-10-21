/* 
Dan Purcell
Track Ball
 */
 
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

//Attach to interrupt pins
Encoder xEncoder(2, 3);
//Encoder yEncoder(18, 19);

const int LED_PIN = 52;
const int BUTTON_PIN = 53;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200);
}

long xPosition  = -999;
//long yPosition = -999;

unsigned long nextTrackTime;
unsigned long ledTime;

boolean buttonState = false;

void loop() {  
  buttonState = !digitalRead(BUTTON_PIN);
  
  if(millis() > nextTrackTime){
    nextTrackTime = millis() + 20;
    
    Serial.print("0");    
    long x = xEncoder.read()/2; //TODO: Make this better.
    char sign = (x > -1) ? '+' : '-';    
    Serial.print(sign);
    
    padding(abs(x), 4);
    
    Serial.print("\r\n");
    
    xEncoder.write(0); //Reset the encoder count
  }
  
  if (Serial.available() > 0) {
    if (Serial.read() == '1') {
      digitalWrite(LED_PIN, HIGH);
      ledTime = millis() + 500;
    }      
  }
  
  if (millis() > ledTime)
    digitalWrite(LED_PIN, LOW);
  else {
    if (buttonState) {
      delay(20);
      Serial.println("100000");
      delay(10000);
    }
  }
}

//zero pad and limit digits
void padding( int number, byte width ) {
 int currentMax = 10;
 for (byte i=1; i<width; i++){
   if (number < currentMax) {
     Serial.print("0");
   }
   currentMax *= 10;
 }
 Serial.print(number);
}

