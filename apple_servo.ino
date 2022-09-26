#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo1;
// twelve servo objects can be created on most boards


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo1.attach(10);
}

void loop() 
{
    myservo.write(180-60);              // tell servo to go to position in variable 'pos'
    myservo1.write(60);
    delay(1000);                       // waits 15ms for the servo to reach the position
    myservo.write(180-0);              // tell servo to go to position in variable 'pos'
    myservo1.write(0);
    delay(1000); 
    
    
}
