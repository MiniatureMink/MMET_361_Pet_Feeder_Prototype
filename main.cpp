#include <Arduino.h>
#include <Servo.h>

Servo foodServo;
int pos = 0; // Create a Servo object
const int servoPin = 9; // Use pin 9 for the servo
const int closed = 0;
const int open = 90;
const unsigned long Max_Open_Time = 5000; // Maximum time to keep the feeder open in milliseconds

// put function declarations here:
void openDoor();
void closeDoor();
void runFeeder();
void openBurst();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  foodServo.attach(servoPin); // Attach the servo to pin 9
  foodServo.write(closed); // Move the servo to the closed position (180 degrees)
  Serial.println("Servo initialized.");
  delay(1000); // Short delay to allow the servo to move
  foodServo.detach(); // Detach the servo to save power
  Serial.println("Servo attached and moved to closed position, now detached to save power.");
  Serial.println("System ready. Press 'o' to open the feeder.");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    char command = Serial.read(); // Read the incoming command
    if (command == 'o') {
      runFeeder();
    } else {
      Serial.println("Invalid command. Use 'o' to open the feeder.");
    }
  }
}

void runFeeder() {
  foodServo.attach(servoPin); // Ensure the servo is attached before operating
  openBurst();
  Serial.println("Feeder will remain open for 60 seconds. Press 'c' to close it manually.");
  unsigned long startTime = millis(); // Record the time when the feeder was opened
  bool closedManually = false;
  while (millis() - startTime < Max_Open_Time) { // Keep the feeder open for the specified time
    if (Serial.available() > 0) {
      char command = Serial.read(); // Read the incoming command
      if (command == 'c') {
        Serial.println("Closing feeder manually...");
        closedManually = true;
        break; // Exit the loop to close the feeder
      }
    }
  }
  if (!closedManually) {
    Serial.println("Maximum open time reached. Closing feeder automatically...");
  }
  closeDoor();
  delay(1000); // Short delay to allow the servo to move
  foodServo.detach(); // Detach the servo to save power

  if(closedManually) {
    Serial.println("Feeder closed manually.");
  } else {
    Serial.println("Feeder closed automatically after 60 seconds.");
  }
  Serial.println("System ready. Press 'o' to open the feeder again.");
}

// put function definitions here:
void openDoor() {
  foodServo.write(open); // Open the feeder by moving to 0 degrees;
  delay(1000); // Short delay to allow the servo to move
}
void closeDoor() {
  foodServo.write(closed); // Close the feeder by moving back to 180 degrees
}
void openBurst(){
for (int i = 0; i < 6; i++) {
 openDoor();
 delay(200);
 closeDoor();
 Serial.println("Burst opened and closed. Waiting for 200 ms before the next burst...");
 delay(200);
  }
  openDoor(); // Keep the feeder open after the burst
}
