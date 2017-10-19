/* 
Dan Purcell
Track Ball
 */
 
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

//Attach X & Y to interrupt pins
Encoder xEncoder(2, 3);
Encoder yEncoder(18, 19);

void setup() {
  Serial.begin(115200);
  Serial.println("Track Ball");
}

long xPosition  = -999;
long yPosition = -999;

unsigned long time;

void loop() {  
  if(millis() > time){
    time = millis() + 20;
    
    Serial.print("0");
    
    long x = xEncoder.read();
    
    char sign = (x > -1) ? '+' : '-';
    
    Serial.print(sign);
    
    padding(abs(x), 4);
    
    Serial.print("\r\n");
    
    xEncoder.write(0);
  }
}

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

