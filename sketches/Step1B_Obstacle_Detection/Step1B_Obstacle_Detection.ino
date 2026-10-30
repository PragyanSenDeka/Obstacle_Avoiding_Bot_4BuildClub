// ==========================================================
//  OBSTACLE AVOIDER - PART 1 : STEP 1B
//  Decide if there is an obstacle in front of the robot
//  and print a clear message in the Serial Monitor.
//
//  Wiring is the SAME as Step 1A:
//    TRIG -> GPIO 14      ECHO -> GPIO 34
//
//  Open Serial Monitor at 115200 baud.
// ==========================================================

const int TRIG_PIN = 14;
const int ECHO_PIN = 34;

// ----------------------------------------------------------
//  CALIBRATION SETTING
//  If an object is this close (in cm) or closer, it counts
//  as an OBSTACLE. 10 cm is a good start. You will copy this
//  same line into the final sketch.
// ----------------------------------------------------------
const int STOP_DISTANCE = 10;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  delay(500);
  Serial.println();
  Serial.println("STEP 1B : Obstacle detection test");
  Serial.print("STOP_DISTANCE = ");
  Serial.print(STOP_DISTANCE);
  Serial.println(" cm");
  Serial.println("----------------------------------------------");
}

void loop() {
  int distance = readDistanceCM();

  Serial.print("Distance: ");
  if (distance < 0) {
    Serial.print("---");
  } else {
    Serial.print(distance);
    Serial.print(" cm");
  }
  Serial.print("   ->  ");

  if (distance > 0 && distance <= STOP_DISTANCE) {
    Serial.println("OBSTACLE AHEAD - robot would STOP");
  }
  else if (distance < 0) {
    Serial.println("CLEAR - nothing in range");
  }
  else {
    Serial.println("CLEAR - path is free");
  }

  delay(200);
}

// ----------------------------------------------------------
//  Returns the distance in cm, or -1 if no echo came back.
//  (This same function is used in the final sketch.)
// ----------------------------------------------------------
int readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return -1;                       // no echo
  }
  return (int)(duration * 0.0343 / 2.0);
}
