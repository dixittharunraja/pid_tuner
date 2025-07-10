#include <PIDRemoteReceiver.h>

PIDRemoteReceiver pidRemote(8, 9); // RX, TX pins for HC-12

void setup() {
    Serial.begin(9600);
    pidRemote.begin();
}

void loop() {
    pidRemote.update(); // Call regularly to process new data

    // Example: Use the latest PID values
    int kp = pidRemote.getKp();
    int ki = pidRemote.getKi();
    int kd = pidRemote.getKd();

    // Use kp, ki, kd in your control loop...
}
