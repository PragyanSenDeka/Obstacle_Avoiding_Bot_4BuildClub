// ==========================================================
//  OBSTACLE AVOIDER - PART 1 : STEP 2B
//  Speed test using PWM on ENA / ENB.
//  Both motors run FORWARD and the speed rises step by step.
//  Note the LOWEST speed at which BOTH wheels start turning.
//
//  !! LIFT THE BOT so the wheels are in the air !!
//  Wiring is the SAME as Step 2A.
// ==========================================================

const int ENA = 32;
const int IN1 = 33;
const int IN2 = 25;
const int IN3 = 26;
const int IN4 = 27;
const int ENB = 13;

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
  Serial.println("STEP 2B : Motor speed test (bot must be lifted!)");
  delay(3000);
}

void loop() {
  // Both motors forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // Speed goes 0, 25, 50 ... 250
  for (int speed = 0; speed <= 250; speed += 25) {
    Serial.print("Speed = ");
    Serial.println(speed);
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(1500);
  }

  stopAll();
  Serial.println("---- STOP. Pause 4 s, then repeat ----");
  delay(4000);
}

void stopAll() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
