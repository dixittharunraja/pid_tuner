#ifndef PIDRX_H
#define PIDRX_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class pidrx {
public:
    pidrx(uint8_t rxPin, uint8_t txPin);
    void begin(long baud = 9600);
    void update(); // Call regularly in loop()
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
