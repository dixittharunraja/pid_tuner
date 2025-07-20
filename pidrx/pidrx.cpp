#include "pidrx.h"
#include <EEPROM.h>

const int pidrx::EEPROM_ADDR[3] = {0, 4, 8};

pidrx::pidrx(uint8_t rxPin, uint8_t txPin)
    : hc12(rxPin, txPin), kp(0), ki(0), kd(0) {}

void pidrx::begin(long baud) {
    hc12.begin(baud);
    loadFromEEPROM();
}

void pidrx::update() {
    static String inputString = "";
    while (hc12.available()) {
        char inChar = (char)hc12.read();
        if (inChar == '\n') {
            inputString.trim();
            processCommand(inputString);
            inputString = "";
        } else {
            inputString += inChar;
        }
    }
}

int pidrx::getKp() { return kp; }
int pidrx::getKi() { return ki; }
int pidrx::getKd() { return kd; }

void pidrx::saveToEEPROM() {
    EEPROM.put(EEPROM_ADDR[0], kp);
    EEPROM.put(EEPROM_ADDR[1], ki);
    EEPROM.put(EEPROM_ADDR[2], kd);
}

void pidrx::loadFromEEPROM() {
    EEPROM.get(EEPROM_ADDR[0], kp);
    EEPROM.get(EEPROM_ADDR[1], ki);
    EEPROM.get(EEPROM_ADDR[2], kd);
}

void pidrx::processCommand(const String &cmd) {
    if (cmd.startsWith("KP,")) {
        kp = cmd.substring(3).toInt();
    } else if (cmd.startsWith("KI,")) {
        ki = cmd.substring(3).toInt();
    } else if (cmd.startsWith("KD,")) {
        kd = cmd.substring(3).toInt();
    } else if (cmd.equals("SAVE")) {
        saveToEEPROM();
    } else if (cmd.equals("RESET")) {
        kp = 0; ki = 0; kd = 0;
    }
}
