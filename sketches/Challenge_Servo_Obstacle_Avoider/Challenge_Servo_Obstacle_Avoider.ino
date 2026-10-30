// ==========================================================
//  OBSTACLE AVOIDER - CHALLENGE (reference solution)
//  The HC-SR04 sits on an SG90 servo. When an obstacle is
//  ahead the robot stops, looks LEFT and RIGHT, and turns
//  towards the side with more space.
//
//  Needs the "ESP32Servo" library (Library Manager).
//
//  Wiring (ESP32):
//    GPIO 14 -> HC-SR04 TRIG      GPIO 34 <- HC-SR04 ECHO
//    GPIO 23 -> Servo signal (orange)
//    GPIO 32 -> ENA   GPIO 33 -> IN1   GPIO 25 -> IN2
//    GPIO 26 -> IN3   GPIO 27 -> IN4   GPIO 13 -> ENB
//    Servo red -> + rail (5V)     Servo brown -> - rail (GND)
// ==========================================================

#include <ESP32Servo.h>

// -------- Pins --------
const int TRIG_PIN  = 14;
const int ECHO_PIN  = 34;
const int SERVO_PIN = 23;

const int IN1 = 33;
const int IN2 = 25;
const int IN3 = 26;
const int IN4 = 27;
const int ENA = 32;
const int ENB = 13;

// -------- Settings you can tune --------
const int STOP_DISTANCE = 10;   // cm
const int REVERSE_TIME  = 300;  // ms
const int TURN_TIME     = 400;  // ms (about a 90 degree turn)
int motorSpeed = 150;           // 0 - 255

const int ANGLE_AHEAD = 90;
const int ANGLE_LEFT  = 160;    // swap LEFT and RIGHT if your servo is mirrored
const int ANGLE_RIGHT = 20;
const int SERVO_WAIT  = 400;    // ms for the servo to arrive and settle
const int NO_ECHO_CM  = 400;    // "no echo" is treated as lots of space

Servo myServo;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stopMotors();

  myServo.setPeriodHertz(50);          // standard servo signal
  myServo.attach(SERVO_PIN, 500, 2400);
  myServo.write(ANGLE_AHEAD);

  delay(2000);
  Serial.println("Servo Obstacle Avoider Started");
}

void loop() {
  int front = readDistanceCM();

  if (front > 0 && front <= STOP_DISTANCE) {
    Serial.print("Obstacle at ");
    Serial.print(front);
    Serial.println(" cm -> stop and look around");

    stopMotors();
    delay(200);

    moveBackward();
    delay(REVERSE_TIME);
    stopMotors();

    int leftDistance  = lookAt(ANGLE_LEFT);
    int rightDistance = lookAt(ANGLE_RIGHT);
    lookAt(ANGLE_AHEAD);

    Serial.print("Left: ");
    Serial.print(leftDistance);
    Serial.print(" cm   Right: ");
    Serial.print(rightDistance);
    Serial.println(" cm");

    if (leftDistance <= STOP_DISTANCE && rightDistance <= STOP_DISTANCE) {
      Serial.println("Both sides blocked -> turn around");
      moveBackward();
      delay(REVERSE_TIME);
      turnRight();
      delay(TURN_TIME * 2);
    }
    else if (leftDistance > rightDistance) {
      Serial.println("More space on the LEFT -> turn left");
      turnLeft();
      delay(TURN_TIME);
    }
    else {
      Serial.println("More space on the RIGHT -> turn right");
      turnRight();
      delay(TURN_TIME);
    }

    stopMotors();
    delay(200);
  }
  else {
    moveForward();
  }

  delay(50);
}

// Move the servo, wait, then measure. Returns cm (no echo = NO_ECHO_CM).
int lookAt(int angle) {
  myServo.write(angle);
  delay(SERVO_WAIT);
  int d = readDistanceCM();
  if (d < 0) {
    d = NO_ECHO_CM;
  }
  return d;
}

// -------- Ultrasonic Function --------
int readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) {
    return -1;
  }
  return (int)(duration * 0.0343 / 2.0);
}

// -------- Motor Functions --------
void moveForward() {
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
