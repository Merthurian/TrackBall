/* 
Dan Purcell
Track Ball
 */
 
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

//Attach to interrupt pins
Encoder xEncoder(2, 3);
Encoder yEncoder(18, 19);

const int LED_PIN = 52;
const int BUTTON_PIN = 53;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
  delay(3000);
  Serial.begin(115200);
}

unsigned long nextTrackTime;
unsigned long ledTime;

float angle = 0;

boolean buttonState = false;

void loop() {  
  buttonState = !digitalRead(BUTTON_PIN);
  
  if(millis() > nextTrackTime){
    angle = mapFloat(float(analogRead(A0)), 0.0, 1024.0, 0.0, 2*PI); 
    
    nextTrackTime = millis() + 20;
    
    Serial.print("0");    
    
    long x = xEncoder.read();
    long y = yEncoder.read();
    
    long rX = long((x * cos(angle)) + (y * sin(angle)));    
    
    char sign = (rX > -1) ? '+' : '-';    
    Serial.print(sign);
    
    padding(abs(rX), 4);
    
    Serial.print("\r\n");
    
    xEncoder.write(0); //Reset the encoder counts
    yEncoder.write(0);
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

//like the builtin 'map' but for floats.
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

