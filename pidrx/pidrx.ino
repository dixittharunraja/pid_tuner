#include <pidrx.h>

pidrx pidReceiver(8, 9);  // RX, TX pins connected to HC-12

void setup() {
  Serial.begin(9600);
  pidReceiver.begin();
}

void loop() {
  pidReceiver.update();

  int kp = pidReceiver.getKp();
  int ki = pidReceiver.getKi();
  int kd = pidReceiver.getKd();

  // Use kp, ki, kd in your control logic
}
