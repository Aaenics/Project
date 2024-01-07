#include "AFMotor.h"

const int MOTOR_1 = 1;
const int MOTOR_2 = 2;
const int MOTOR_3 = 3;
const int MOTOR_4 = 4;
const int MOTION_SENSOR_PIN = 5; // Motion sensor input pin

AF_DCMotor motor1(MOTOR_1, MOTOR12_64KHZ);
AF_DCMotor motor2(MOTOR_2, MOTOR12_64KHZ);
AF_DCMotor motor3(MOTOR_3, MOTOR12_64KHZ);
AF_DCMotor motor4(MOTOR_4, MOTOR12_64KHZ);

int Speed = 130;
int state = 0;

void setup() {
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor3.setSpeed(Speed);
  motor4.setSpeed(Speed);
  Serial.begin(9600);
  pinMode(MOTION_SENSOR_PIN, INPUT); // Motion sensor pin as input
  delay(500);
}

void loop() {
  if (Serial.available() > 0) {
    state = Serial.read();
    if (state > 10) {
      Speed = state;
    }
  }

  int motionState = digitalRead(MOTION_SENSOR_PIN); // Read motion sensor state

  if (motionState == HIGH) {
    // If motion is detected, move forward
    forword();
    delay(120000); // Move for 0.5 seconds (adjust this delay as needed)
  } else {
    // If no motion, stop the motors
    Stop();
  }

  // Key Control Command
  if (state == 1) {
    forword();
  } else if (state == 2) {
    backword();
  } else if (state == 3) {
    turnLeft();
  } else if (state == 4) {
    turnRight();
  } else if (state == 5) {
    Stop();
  }

  // Voice Control Command
  else if (state == 6) {
    turnLeft();
    delay(400);
    state = 5;
  } else if (state == 7) {
    turnRight();
    delay(400);
    state = 5;
  }

  delay(80);
}

void forword() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void backword() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
