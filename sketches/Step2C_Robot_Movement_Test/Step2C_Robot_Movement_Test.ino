// ==========================================================
//  OBSTACLE AVOIDER - PART 1 : STEP 2C
//  Test the 4 moves the obstacle avoider will use:
//  FORWARD, BACKWARD, TURN RIGHT, STOP
//  (These are the SAME functions used in the final sketch.)
//
//  !! LIFT THE BOT so the wheels are in the air !!
//  Wiring is the SAME as Step 2A.
// ==========================================================

// -------- Motor Driver Pins --------
const int ENA = 32;
const int IN1 = 33;
const int IN2 = 25;
const int IN3 = 26;
const int IN4 = 27;
const int ENB = 13;

int motorSpeed = 150;   // motor speed (0 - 255)

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopMotors();
  delay(500);
  Serial.println();
  Serial.println("STEP 2C : Movement test (bot must be lifted!)");
  delay(3000);
}

void loop() {
  Serial.println("FORWARD     (both wheels forward)");
  moveForward();
  delay(2000);

  Serial.println("STOP");
  stopMotors();
  delay(1000);

  Serial.println("BACKWARD    (both wheels backward)");
  moveBackward();
  delay(2000);

  Serial.println("STOP");
  stopMotors();
  delay(1000);

  Serial.println("TURN RIGHT  (left wheel forward, right wheel backward)");
  turnRight();
  delay(2000);

  Serial.println("STOP - pause 3 s, then repeat");
  stopMotors();
  delay(3000);
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

// Spin on the spot to the right:
// left wheel forward, right wheel backward
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
