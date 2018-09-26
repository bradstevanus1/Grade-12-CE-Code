// Global Variables
const int motorInput1 = 4;
const int motorInput2 = 5;
const int motorPWM1 = 6; 
const int motorInput3 = 7;
const int motorInput4 = 8;
const int motorPWM2 = 9;
const int v5 = 142;


void setup() {
  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorPWM1, OUTPUT);
  pinMode(motorInput3, OUTPUT);
  pinMode(motorInput4, OUTPUT);
  pinMode(motorPWM2, OUTPUT);  
  analogWrite(motorPWM1, v5);
  analogWrite(motorPWM2, v5);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);    
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);  

}

void loop() {


}
