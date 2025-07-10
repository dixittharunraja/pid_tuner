#ifndef PID_REMOTE_RECEIVER_H
#define PID_REMOTE_RECEIVER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class PIDRemoteReceiver {
public:
    PIDRemoteReceiver(uint8_t rxPin, uint8_t txPin);
    void begin(long baud = 9600);
    void update(); // Call this regularly in loop()
    int getKp();
    int getKi();
    int getKd();
    void saveToEEPROM();
    void loadFromEEPROM();
private:
    SoftwareSerial hc12;
    int kp, ki, kd;
    void processCommand(const String &cmd);
    static const int EEPROM_ADDR[3];
};

#endif
