#include <Servo.h>

#define SERVO1_PIN PA10  // Update if you use a different pin
#define SERVO2_PIN PA11  // Update if you use a different pin

Servo servo1;
Servo servo2;

void setup() {
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
}

void loop() {
  // Sweep from 0 to 180
  for (int pos = 0; pos <= 180; pos++) {
    servo1.write(pos);
    servo2.write(pos);
    delay(15); // Adjust delay for sweep speed
  }
  // Sweep from 180 back to 0
  for (int pos = 180; pos >= 0; pos--) {
    servo1.write(pos);
    servo2.write(pos);
    delay(15);
  }
}
