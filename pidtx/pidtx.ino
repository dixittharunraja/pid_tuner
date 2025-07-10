#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <digitalWriteFast.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned long sentDisplayDuration = 2000;

struct Encoder {
  const int clkPin, dtPin, swPin;
  volatile int value;
  int lastCLK;
  bool sendFlag;
  bool sent;
  unsigned long sentTime;
  const char* label;
  int y;
};

const int saveButtonPin = 2;
const int resetButtonPin = 3;

bool lastSaveButtonState = HIGH;
bool lastResetButtonState = HIGH;
unsigned long lastDebounceTimeSave = 0;
unsigned long lastDebounceTimeReset = 0;
const unsigned long debounceDelay = 50; // ms

Encoder encoders[] = {
  {4, 5, 6, 0, 0, HIGH, false, 0, "Kp", 0},
  {7, 8, 9, 0, 0, HIGH, false, 0, "Ki", 22},
  {10, 11, 12, 0, 0, HIGH, false, 0, "Kd", 44}
};
const int NUM_ENCODERS = sizeof(encoders)/sizeof(encoders[0]);

const int EEPROM_ADDR[NUM_ENCODERS] = {0, 4, 8};

void printToOLED(const char* text, int x, int y, int textSize = 2, uint16_t color = SSD1306_WHITE) {
  display.setTextSize(textSize);
  display.setTextColor(color);
  display.setCursor(x, y);
  display.print(text);
}

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    for (;;);
  }
  display.clearDisplay();

  for (int i = 0; i < NUM_ENCODERS; ++i) {
    pinMode(encoders[i].clkPin, INPUT);
    pinMode(encoders[i].dtPin, INPUT);
    pinMode(encoders[i].swPin, INPUT_PULLUP);
    encoders[i].lastCLK = digitalReadFast(encoders[i].clkPin);
  }

  pinMode(saveButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);

  loadPIDValuesFromEEPROM();

  showPID();
}

void loop() {
  bool needUpdate = false;
  for (int i = 0; i < NUM_ENCODERS; ++i) {
    needUpdate |= readEncoder(encoders[i], i);
  }

  unsigned long now = millis();
  for (int i = 0; i < NUM_ENCODERS; ++i) {
    if (encoders[i].sent && now - encoders[i].sentTime > sentDisplayDuration) {
      encoders[i].sent = false;
      needUpdate = true;
    }
  }
  
  checkButtons();

  if (needUpdate) showPID();
}

bool readEncoder(Encoder &enc, int idx) {
  bool updated = false;
  int currCLK = digitalReadFast(enc.clkPin);

  if (currCLK != enc.lastCLK && currCLK == HIGH) {
    enc.value += (digitalReadFast(enc.dtPin) == LOW) ? 1 : -1;
    updated = true;
  }
  enc.lastCLK = currCLK;

  bool btn = digitalReadFast(enc.swPin);
  if (!btn && enc.sendFlag) {
    enc.sent = true;
    enc.sentTime = millis();
    updated = true;
    sendSinglePID(idx);
    delay(200); // debounce
  }
  enc.sendFlag = btn;

  return updated;
}

void showPID() {
  display.clearDisplay();
  char buf[16];
  for (int i = 0; i < NUM_ENCODERS; ++i) {
    snprintf(buf, sizeof(buf), "%s: %d", encoders[i].label, encoders[i].value);
    printToOLED(buf, 0, encoders[i].y, 2);
    if (encoders[i].sent) printToOLED("Sent!", 88, encoders[i].y, 1);
  }
  display.display();
}

void checkButtons() {
  int readingSave = digitalRead(saveButtonPin);
  if (readingSave != lastSaveButtonState) {
    lastDebounceTimeSave = millis();
  }
  if ((millis() - lastDebounceTimeSave) > debounceDelay) {
    if (lastSaveButtonState == HIGH && readingSave == LOW) { // Button pressed
      savePIDValues();
      Serial.print("SAVE\n");
    }
  }
  lastSaveButtonState = readingSave;

  int readingReset = digitalRead(resetButtonPin);
  if (readingReset != lastResetButtonState) {
    lastDebounceTimeReset = millis();
  }
  if ((millis() - lastDebounceTimeReset) > debounceDelay) {
    if (lastResetButtonState == HIGH && readingReset == LOW) { // Button pressed
      resetPIDValues();
      Serial.print("RESET\n");
    }
  }
  lastResetButtonState = readingReset;
}

void loadPIDValuesFromEEPROM() {
  for (int i = 0; i < NUM_ENCODERS; ++i) {
    int val = 0;
    EEPROM.get(EEPROM_ADDR[i], val);
    encoders[i].value = val;
  }
}

void savePIDValues() {
  unsigned long now = millis();
  for (int i = 0; i < NUM_ENCODERS; ++i) {
    EEPROM.put(EEPROM_ADDR[i], encoders[i].value);
    encoders[i].sent = true;
    encoders[i].sentTime = now;
  }
  showPID();
}

void resetPIDValues() {
  for (int i = 0; i < NUM_ENCODERS; ++i) {
    encoders[i].value = 0;
    encoders[i].sent = false;
  }
  showPID();
}

void sendSinglePID(int idx) {
  String msg;
  switch (idx) {
    case 0: // Kp
      msg = "KP," + String(encoders[0].value) + "\n";
      break;
    case 1: // Ki
      msg = "KI," + String(encoders[1].value) + "\n";
      break;
    case 2: // Kd
      msg = "KD," + String(encoders[2].value) + "\n";
      break;
    default:
      return;
  }
  Serial.print(msg);
}
