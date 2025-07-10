#include <pidrx.h>

pidrx pidReceiver(8, 9);  // RX, TX pins connected to HC-12

void setup() {
  Serial.begin(9600);
  pidReceiver.begin();
  Serial.println("pidrx example started");
}

void loop() {
  pidReceiver.update();

  int kp = pidReceiver.getKp();
  int ki = pidReceiver.getKi();
  int kd = pidReceiver.getKd();

  Serial.print("Kp: "); Serial.print(kp);
  Serial.print(" | Ki: "); Serial.print(ki);
  Serial.print(" | Kd: "); Serial.println(kd);

  delay(1000);
}
