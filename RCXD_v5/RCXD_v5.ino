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
// Sonar Variables
const int trigPin = 10;
const int echoPin = 11;
long duration;
int distance;

const int v5 = 142;
const int v6 = 170;
const int left = 50;
const int straight = 90;
const int right = 130;

// Autonomous variables
int grace = 0;
int t = 0;
int anna = 0;
int cait = 0;

Servo servo;
char state = '0';

void setup() {
  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorPWM1, OUTPUT);
  pinMode(motorInput3, OUTPUT);
  pinMode(motorInput4, OUTPUT);
  pinMode(motorPWM2, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
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
  delay(1);
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  Serial.print("Motor forward complete");
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
    motorforward();
    distance = getDistance();
//    if (millis() > (grace + 500)) {
//      t = millis();
//      while (distance < 20) {
//        distance = getDistance();
//        motorbackward();
//        servoright();
//        grace = millis();
//        if (millis() > (t + 1000)) {
//          break;
//        }
//      }
//    }
    if (distance>20){
      motorbackward();
      servoright();
      delay(1000);
    }

    
    
    
    
    
  }
}
 
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}









