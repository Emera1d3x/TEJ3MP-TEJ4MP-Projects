// Sehan Munir, Andy Zhang, Yogi Shah
// TEJ4MP - Mr. Wong
// 2025-06-08
// Line Following Car
// This i-Car (intelligent car) will follow a complex maze. Environment is white with black tape representing paths.

// Constant Values
//  LDR Pins
#define LDR_LEFT  A0
#define LDR_MID   A1
#define LDR_RIGHT A2
//  Motor Pins (Regular and Enablers)
#define rightMotorPin1 9
#define rightMotorPin2 10
#define leftMotorPin1 11
#define leftMotorPin2 8
#define enableRight 5
#define enableLeft 6
//  Sensor Light Value Cutoffs (W/B)
#define CUTOFF_RIGHT 220
#define CUTOFF_LEFT 220
#define CUTOFF_MIDDLE 220

// Setup - Basic setup to make pin modes correct
void setup() {
  // Declaring Motor Pins as OUTPUT
  pinMode(rightMotorPin1, OUTPUT); pinMode(rightMotorPin2, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT); pinMode(leftMotorPin2, OUTPUT);
  pinMode(enableRight, OUTPUT); pinMode(enableLeft, OUTPUT);
  // Begin Serialization
  Serial.begin(9600);
}
// Event Loop
void loop() {
  // Reading Sensors
  int ldrLeft = analogRead(LDR_LEFT);
  int ldrMid = analogRead(LDR_MID);
  int ldrRight = analogRead(LDR_RIGHT);
  // Considering whether Sensors are on W/B. 1 = white, 0 = black
  bool whiteL = (ldrLeft > CUTOFF_LEFT);
  bool whiteM = (ldrMid > CUTOFF_MIDDLE);
  bool whiteR = (ldrRight > CUTOFF_RIGHT);
  // Main Logic (A reactive type logic, motors spin based on exact moment (fully reactive))
  if (whiteL && whiteM && whiteR){
    rotateMotors(-110, 110);
  } else if (whiteL && whiteR){ 
    rotateMotors(100, 100);
  } else if (!whiteR && !whiteM &&!whiteL) {
    rotateMotors(120, -110);
  } else if (!whiteR){
    rotateMotors(100, 0); 
  } else if (!whiteL){
    rotateMotors(0, 100);
  } else {
    rotateMotors(-90, -90);
  }
  // Adjustments (These are adjustments for problems such as friction, acceleration, momentum)
  delay(130);
  rotateMotors(0, 0);
  delay(50);
}
// Motor Direction Setter (Sets direction of motors)
void setDirection(bool leftForward, bool rightForward){
  if (leftForward){
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  } else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  }
  if (rightForward){
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  }
}
// Move Motors (Gives power to motors)
void rotateMotors(int leftSpeed, int rightSpeed) {
  rightSpeed = -rightSpeed; // (Adjusting Right Motor)
  setDirection(leftSpeed>0, rightSpeed>0); // Set direction
  // Give motors power
  analogWrite(enableLeft, constrain(absoluteVal(leftSpeed), 0, 255));
  analogWrite(enableRight, constrain(absoluteVal(rightSpeed), 0, 255));
}
// Absolute Value (Helper method to get SPEED)
int absoluteVal(int input){
  return (input>0)?input:-input; 
}
