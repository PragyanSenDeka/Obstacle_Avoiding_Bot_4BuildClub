// ==========================================================
//  OBSTACLE AVOIDER - PART 1 : STEP 3 (FINAL)
//  Simple obstacle avoiding robot: ESP32 + HC-SR04 + L298N
//
//  The robot drives forward. When an obstacle is closer than
//  STOP_DISTANCE it will:  STOP -> REVERSE 0.5 s -> TURN RIGHT
//  and then carry on forward.
//
//  Wiring summary (ESP32):
//    GPIO 14 -> HC-SR04 TRIG      GPIO 34 <- HC-SR04 ECHO
//    GPIO 32 -> ENA   GPIO 33 -> IN1   GPIO 25 -> IN2
//    GPIO 26 -> IN3   GPIO 27 -> IN4   GPIO 13 -> ENB
//    Left motor -> OUT1/OUT2     Right motor -> OUT3/OUT4
// ==========================================================

// -------- Ultrasonic Sensor Pins --------
const int TRIG_PIN = 14;
const int ECHO_PIN = 34;

// -------- Motor Driver Pins --------
const int IN1 = 33;
const int IN2 = 25;
const int IN3 = 26;
const int IN4 = 27;

const int ENA = 32;
const int ENB = 13;

// -------- Settings you can tune --------
const int STOP_DISTANCE = 10;   // cm - obstacle closer than this = avoid it
const int REVERSE_TIME  = 500;  // ms - how long to drive backward
const int TURN_TIME     = 400;  // ms - how long to turn right
int motorSpeed = 150;           // 0 - 255

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

  stopMotors();        // make sure the bot does not jump at power-on
  delay(2000);         // 2 seconds to place the bot on the floor

  Serial.println("Obstacle Avoider Started");
}

void loop() {

  int distance = readDistanceCM();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm -> ");

  // Obstacle close in front?
  if (distance > 0 && distance <= STOP_DISTANCE) {

    Serial.println("OBSTACLE! STOP, REVERSE, TURN RIGHT");

    stopMotors();
    delay(200);

    moveBackward();
    delay(REVERSE_TIME);

    stopMotors();
    delay(200);

    turnRight();
    delay(TURN_TIME);

    stopMotors();
    delay(200);
  }

  // Path is clear (or nothing in range)
  else {
    Serial.println("FORWARD");
    moveForward();
  }

  delay(50);
}


// -------- Ultrasonic Function --------
// Returns the distance in cm, or -1 if no echo came back.
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
