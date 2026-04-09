#include <Arduino.h>
#include <Servo.h>

Servo foodServo;
int pos = 0; // Create a Servo object
const int servoPin = 9; // Use pin 9 for the servo

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  foodServo.attach(servoPin); // Attach the servo to pin 9
  foodServo.write(180); //Move servo to reference angle
  Serial.println("Servo attached and moved to 180 degrees");
  Serial.println("System ready. Press 'o' to open the feeder and 'c' to close it.");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    char command = Serial.read(); // Read the incoming command
    if (command == 'o') {
      foodServo.write(0); // Open the feeder by moving to 0 degrees
      Serial.println("Feeder opened.");
    } else if (command == 'c') {
      foodServo.write(180); // Close the feeder by moving back to 180 degrees
      Serial.println("Feeder closed.");
    }
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}