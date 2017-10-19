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

String message;

void loop() {  
  if(millis() > time){
    time = millis() + 20;
    
    message = "0";
    
    long x = xEncoder.read();
    
    char sign = (x > -1) ? '+' : '-';
    
    message.concat(sign);
    
    String val = String(x, DEC);
    val = val.substring(val.length() - 4);
    
    message.concat(val);
    
    Serial.println(message);
    xEncoder.write(0);
  }
}

