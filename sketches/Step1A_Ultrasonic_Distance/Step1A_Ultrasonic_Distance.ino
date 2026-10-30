// ==========================================================
//  OBSTACLE AVOIDER - PART 1 : STEP 1A
//  Measure distance with the HC-SR04 ultrasonic sensor
//  and print it in centimetres.
//
//  Wiring (ESP32):
//    HC-SR04 VCC  -> Breadboard + rail (5V)
//    HC-SR04 GND  -> Breadboard - rail (GND)
//    HC-SR04 TRIG -> GPIO 14
//    HC-SR04 ECHO -> GPIO 34
//  (Using a different ESP32 board? Any free GPIO pins work -
//   just change the two numbers below.)
//
//  Open Serial Monitor at 115200 baud.
// ==========================================================

const int TRIG_PIN = 14;   // sends the sound pulse (output)
const int ECHO_PIN = 34;   // listens for the echo  (input)

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  delay(500);
  Serial.println();
  Serial.println("STEP 1A : Ultrasonic distance test");
  Serial.println("Move your hand or a box in front of the sensor.");
  Serial.println("----------------------------------------------");
}

void loop() {
  // 1. Send a 10 microsecond pulse on TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // 2. Measure how long ECHO stays HIGH (in microseconds)
  //    30000 us timeout = give up after about 5 metres
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // 3. Convert time to distance
  //    sound travels 0.0343 cm per microsecond,
  //    divide by 2 because the sound goes there AND back
  float distanceCM = duration * 0.0343 / 2.0;

  Serial.print("Echo time: ");
  Serial.print(duration);
  Serial.print(" us     Distance: ");

  if (duration == 0) {
    Serial.println("no echo (nothing in range)");
  } else {
    Serial.print(distanceCM, 1);
    Serial.println(" cm");
  }

  delay(200);   // 5 readings per second - easy to read
}
