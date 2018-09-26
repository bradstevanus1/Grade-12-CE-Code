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
const int motorPWM2 = 9;
const int trigPin

const int v6 = 170;
const int left = 50;
const int straight = 90;
const int right = 130;
Servo servo;
char state = '0';

void setup() {
  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorPWM1, OUTPUT);
  pinMode(motorInput3, OUTPUT);
  pinMode(motorInput4, OUTPUT);
  pinMode(motorPWM2, OUTPUT);
  Serial.begin(9600); // Default communication rate of the Bluetooth module
  servo.attach(servoPin); // Attach servo to pin
  analogWrite(motorPWM1, v6); // Set both motor outputs to 5V
  analogWrite(motorPWM2, v6);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW); 
}



void loop() {
  if (Serial.available() > 0) { // Checks whether data is comming from the serial port
    state = char(Serial.read()); // Reads the data from the serial port
    if (state != '-1') {
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

void motorforward() {
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  Serial.print("Motor forward complete");

}

void motorbackward() {
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  Serial.print("Motor backward complete");
}

void motorstop() {
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  Serial.print("Motor stop complete");
}

void servoleft() {
  servo.write(50);
  delay(1);
  Serial.print("Left turn complete");
}

void servoright() {
  servo.write(130);
  delay(1);
  Serial.print("Right turn complete");
}

void servostraight() {
  servo.write(90);
  delay(1);
  Serial.print("Straight turn complete");
}

void testServo() {
  servo.write(50);
  delay(2000);
  servo.write(90);
  delay(2000);
  servo.write(130);
  delay(2000);
}

void autonomous() {
  state = '0';
  Serial.println("Autonomous mode activated");
  while (true) {
    if (Serial.available() > 0) { // Checks whether data is comming from the serial port
      state = char(Serial.read()); // Reads the data from the serial port
      if (state != '-1') {
        Serial.println(state);
      }
    }
    if (state == 'a') {
      Serial.println("Toggle Bluetooth / Autonomous Mode");
      state = '0';
      return;
    }








  
  }
}










