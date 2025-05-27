// FlySky iBUS receiver reading for STM32 (Arduino IDE)
// Connect iBUS signal to a hardware serial RX pin (e.g., PB7 = Serial1 RX on Black Pill)

#define IBUS_SERIAL     Serial1    // Use Serial1 for iBUS (PB7 on STM32 Black Pill)
#define IBUS_BAUDRATE   115200
#define IBUS_PACKET_SIZE 32
#define IBUS_NUM_CHANNELS 6

uint8_t ibusBuffer[IBUS_PACKET_SIZE];
uint16_t ibusChannels[IBUS_NUM_CHANNELS];

void setup() {
  Serial.begin(115200);       // For debug output to Serial Monitor
  IBUS_SERIAL.begin(IBUS_BAUDRATE);
}

void loop() {
  // Wait for a full iBUS packet
  if (readIBUSPacket(ibusBuffer)) {
    if (ibusBuffer[0] == 0x20 && ibusBuffer[1] == 0x40) { // Check iBUS header
      for (int i = 0; i < IBUS_NUM_CHANNELS; i++) {
        ibusChannels[i] = ibusBuffer[2 + i * 2] | (ibusBuffer[3 + i * 2] << 8);
      }

      // Print channels for verification
      Serial.print("Channels: ");
      for (int i = 0; i < IBUS_NUM_CHANNELS; i++) {
        Serial.print(ibusChannels[i]);
        Serial.print(i < IBUS_NUM_CHANNELS - 1 ? ", " : "\n");
      }
    }
  }
}

// Reads a full iBUS packet from the serial port
bool readIBUSPacket(uint8_t *buffer) {
  static uint8_t idx = 0;
  while (IBUS_SERIAL.available()) {
    uint8_t b = IBUS_SERIAL.read();
    if (idx == 0 && b != 0x20) continue; // Wait for packet start
    buffer[idx++] = b;
    if (idx == IBUS_PACKET_SIZE) {
      idx = 0;
      return true;
    }
  }
  return false;
}
