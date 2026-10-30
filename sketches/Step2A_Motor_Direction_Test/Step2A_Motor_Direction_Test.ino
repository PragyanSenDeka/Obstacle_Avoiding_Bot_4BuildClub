// ==========================================================
//  OBSTACLE AVOIDER - PART 1 : STEP 2A
//  Test each motor ONE AT A TIME, forward and backward.
//
//  !! LIFT THE BOT so the wheels are in the air !!
//
//  Wiring (ESP32 -> L298N):
//    GPIO 32 -> ENA   (Left motor speed)
//    GPIO 33 -> IN1   (Left motor direction)
//    GPIO 25 -> IN2   (Left motor direction)
//    GPIO 26 -> IN3   (Right motor direction)
//    GPIO 27 -> IN4   (Right motor direction)
//    GPIO 13 -> ENB   (Right motor speed)
//    Left motor  -> OUT1 / OUT2
//    Right motor -> OUT3 / OUT4
//  Remove the ENA and ENB jumper caps on the L298N.
// ==========================================================

// -------- Motor Driver Pins --------
const int ENA = 32;
const int IN1 = 33;
const int IN2 = 25;
const int IN3 = 26;
const int IN4 = 27;
const int ENB = 13;

int testSpeed = 150;   // 0 - 255

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopAll();
  delay(500);
  Serial.println();
  Serial.println("STEP 2A : Motor direction test (bot must be lifted!)");
  delay(3000);   // 3 seconds to place the bot on its stand
}

void loop() {
  // ---- LEFT motor ----
  Serial.println("LEFT motor  -> FORWARD");
  analogWrite(ENA, testSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(2000);
  stopAll();
  delay(1000);

  Serial.println("LEFT motor  -> BACKWARD");
  analogWrite(ENA, testSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(2000);
  stopAll();
  delay(1000);

  // ---- RIGHT motor ----
  Serial.println("RIGHT motor -> FORWARD");
  analogWrite(ENB, testSpeed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(2000);
  stopAll();
  delay(1000);

  Serial.println("RIGHT motor -> BACKWARD");
  analogWrite(ENB, testSpeed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(2000);
  stopAll();

  Serial.println("---- pause 3 s, then repeat ----");
  delay(3000);
}

void stopAll() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
