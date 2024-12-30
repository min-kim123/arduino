#include <Servo.h>

Servo leftServo;
Servo rightServo;

#define RIGHT_LDR A0
#define LEFT_LDR A1

#define STOP 1500 //neutral
#define FORWARD_LEFT 1600 
#define BACKWARD_LEFT 1400
#define FORWARD_RIGHT 1400 
#define BACKWARD_RIGHT 1600 

#define THRESHOLD 50

void setup() {
  leftServo.attach(9); 
  rightServo.attach(10);

  leftServo.writeMicroseconds(STOP);
  rightServo.writeMicroseconds(STOP);

  Serial.begin(9600);
}

void loop() {
  int rightLight = analogRead(RIGHT_LDR); 
  int leftLight = analogRead(LEFT_LDR);

  Serial.print("Right LDR: ");
  Serial.print(rightLight);
  Serial.print("  Left LDR: ");
  Serial.println(leftLight);

  // determining movement based on light intensity
  if (abs(leftLight - rightLight) <= THRESHOLD) {
    //approximately equal light intensity: forward
    leftServo.writeMicroseconds(FORWARD_LEFT);
    rightServo.writeMicroseconds(FORWARD_RIGHT);
  } else if (leftLight > rightLight) {
    //more light on left: turn left
    leftServo.writeMicroseconds(BACKWARD_LEFT);
    rightServo.writeMicroseconds(FORWARD_RIGHT);
  } else {
    //more light on right: turn right
    leftServo.writeMicroseconds(FORWARD_LEFT);
    rightServo.writeMicroseconds(BACKWARD_RIGHT);
  }

  delay(50);
}
