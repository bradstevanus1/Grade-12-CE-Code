// Global Variables

#include <Servo.h>
const int servoPin = 3;
// Back DC motors
const int motorInput1 = 4;
const int motorInput2 = 5;
const int motorPWM1 = 6;
// Secondary power delivery module
const int motorInput3 = 7;
const int motorInput4 = 8;
const int motorPWM2 = 12;
// Sonar Variables
const int trigPin = 10;
const int echoPin = 11;
long duration;
int distance;
// Voltage and Servo values
const int v5 = 142;
const int v6 = 170;
const int left = 50;
const int straight = 90;
const int right = 127;
// Autonomous variables
int grace = 0;
int t = 0;
// Initialize servo
Servo servo;
// Variable used for bluetooth states
char state = '0';

void setup() { // Setup code, runs first
  pinMode(motorInput1, OUTPUT); // All 6 Arduino to L298N pins are outputs
  pinMode(motorInput2, OUTPUT);
  pinMode(motorPWM1, OUTPUT);
  pinMode(motorInput3, OUTPUT);
  pinMode(motorInput4, OUTPUT);
  pinMode(motorPWM2, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Default communication rate of the Bluetooth module
  servo.attach(servoPin); // Attach servo to pin
  analogWrite(motorPWM1, v6); // Set both motor outputs on L298N to 6V
  analogWrite(motorPWM2, v6);
  digitalWrite(motorInput3, HIGH); // Keep servo power open
  digitalWrite(motorInput4, LOW);
}



void loop() {
  if (Serial.available() > 0) { // Checks whether data is comming from the serial port
    state = char(Serial.read()); // Reads the data from the serial port and converts to string literal
    if (state != '-1') { // Disregard null returns
      Serial.println(state); 
    }
  }
// DC motor bluetooth signals
  if (state == 'f') {
    Serial.println("Go forward");
    motorforward();
    state = '0';
  }
  else if (state == 'b') {
    Serial.println("Go backward");
    motorbackward();
    state = '0';
  }
  else if (state == 's') {
    Serial.println("Stop");
    motorstop();
    state = '0';
  }
// Servo steering bluetooth signals
  else if (state == 'l') {
    Serial.println("Turn left");
    servoleft();
    state = '0';
  }
  else if (state == 'r') {
    Serial.println("Turn right");
    servoright();
    state = '0';
  }
  else if (state == 't') {
    Serial.println("Go straight");
    servostraight();
    state = '0';
  }
// Switch to autonomous mode
  else if (state == 'a') {
    autonomous();
    Serial.println("Autonomous mode deactivated");
    state = '0';
  }
}

// Motor control code

void motorforward() {
  delay(1);
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  Serial.println("Motor forward complete");
  delay(1);

}

void motorbackward() {
  delay(1);
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  Serial.println("Motor backward complete");
  delay(1);
}

void motorstop() {
  delay(1);
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  Serial.println("Motor stop complete");
  delay(1);
}

// Servo steering code

void servoleft() {
  servo.write(50);
  delay(1);
  Serial.println("Left turn complete");
}

void servoright() {
  servo.write(130);
  delay(1);
  Serial.println("Right turn complete");
}

void servostraight() {
  servo.write(90);
  delay(1);
  Serial.println("Straight turn complete");
}

// Autonomous mode function

void autonomous() {
  state = '0'; // Reset BT value
  Serial.println("Autonomous mode activated"); // User feedback
  while (true) { // Run continuously
    if (Serial.available() > 0) { // Checks whether data is comming from the serial port
      state = char(Serial.read()); // Reads the data from the serial port
      if (state != '-1') { // Disregard null return
        Serial.println(state);
      }
    }
    // Return to bluetooth control upon button press
    if (state == 'a') { 
      Serial.println("Toggle Bluetooth / Autonomous Mode");
      state = '0';
      return;
    }
    // Autonomous code
    motorforward(); // Default motor state (no walls)
    servostraight();
    distance = getDistance();
    grace = 0;
    
// Obstacle Avoidance
    if (millis() > (grace + 500)) { // millis returns Arduino's clock time
      t = millis(); 
      Serial.println("Millis is: ");
      Serial.print(millis());
      while (distance < 20) { // Backs up and turns right when object is 20m or less in front
        distance = getDistance(); // Get sonar distance
        Serial.println(distance);
        // Continuously runs until object is out of range or until...
        motorbackward();
        servoright();
        grace = millis();
        delay(1);
        // Until one second passes, to avoid getting stuck
        if (millis() > (t + 1000)) {
          break;
        }
      }
    }
  }
}

// This function returns the distance the sonar sees
// to the nearest object, in cm
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  return distance;
}



