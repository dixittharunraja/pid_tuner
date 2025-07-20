# PID Tuner – Detailed Build, Wiring & Use Guide

_by RODIX (Dixit Tharun Raja P)_

This guide will help you assemble, wire, program, and operate your PID tuner hardware for the smoothest out-of-the-box experience.

---

## 1. Required Components

| Qty | Item                                  |
|-----|---------------------------------------|
| 1   | Arduino Nano                          |
| 3   | Rotary encoders (with push button)    |
| 1   | 0.96" I2C OLED display                |
| 2   | Mini push buttons                     |
| 1   | HC-12 wireless module                 |
| 1   | 360mAh 2S LiPo battery                |
| 1   | MRB045 2S LiPo USB-C charger module   |
| 1   | BEC 5V 3A voltage regulator           |
| 1   | Rocker switch (10A)                   |
| —   | 3D-printed enclosure (see `enclosure/`) |

---

## 2. Wiring Diagram

**Power System:**

[2S LiPo]──[MRB045 Charger]
|
+──[BEC 5V 3A]──[Rocker Switch]──[Arduino VIN]

- All peripherals (OLED, encoders, HC-12, buttons) wired to Nano (5V & GND).
- NEVER charge and run the device at the same time! Disconnect load before charging.

**Typical Peripheral Connection Table**

| Part           | Arduino Pins      | Notes                   |
|----------------|-------------------|-------------------------|
| Kp encoder     | D10 (CLK), D11 (DT), D12 (SW) |             |
| Ki encoder     | D7  (CLK), D8  (DT), D9  (SW) |             |
| Kd encoder     | D4  (CLK), D5  (DT), D6  (SW) |             |
| OLED           | SDA (A4), SCL (A5)| 5V, GND                 |
| Save button    | A2                | Active LOW, to GND      |
| Reset button   | A3                | Active LOW, to GND      |
| HC-12          | D3 (RX), D2 (TX)  | 5V, GND                 |

**Tip:** Adjust your connections if you need, just update the sketch pin numbers as well.

---

## 3. Enclosure Assembly

- Print parts in `enclosure/`: `case/bottom`, `case/lid`, `case/top`, and `knob.step`.
- Install Nano, OLED, encoders, buttons, HC-12, and battery into the case.
- Secure rocker switch, close lid.
- Recommended: PLA, 0.2mm layer height, 15% infill.

---

## 4. Firmware Upload

- Open `pidtx/pidtx.ino` in Arduino IDE.
- Select Arduino Nano, correct COM port.
- Upload code. Connect HC-12 after flashing to avoid serial conflicts.

---

## 5. Charging & Safety

- To **charge**: Disconnect BEC from battery and plug USB-C into MRB045 charger; connect battery (BAT+/-) to the module.
- Never charge and operate at the same time!
- Always supervise LiPo charging and use a safe charging bag.

---

## 6. Operation

1. Flip rocker switch ON.
2. OLED displays Kp, Ki, Kd.  
3. Rotate encoders to change values (per step!).  
4. Press encoder to send (`Kp Sent!`, etc. appears briefly onscreen).  
5. Press SAVE (A2) to store values in EEPROM: `Save!` displays for 1s.  
6. Press RESET (A3) to zero all values: `Reset!` displays for 1s.  
7. All actions appear and auto-return to value dashboard. Wireless commands sent over HC-12 immediately.

---

## 7. Troubleshooting

- **OLED blank:** Check wiring, I2C address (should be 0x3C), verify voltage.
- **Encoder glitch:** Recheck GND; debounce logic is handled in code.
- **"Sent!"/others not displaying:** Confirm logic and action in code (see `showPID()`).
- **Wireless fails:** Confirm HC-12 baud (9600), antenna connected, wiring correct.

---

## 8. Customization

- Edit encoder pin config in code for your preferences.
- Adjust `sentDisplayDuration` (ms) for feedback time.
- You can modify enclosure in Fusion 360 or remix with .step/.obj.

---

## 9. Receiver Integration

See `pidrx/examples/BasicUsage/BasicUsage.ino` and library documentation for adding to your robot or industrial controller.

---

_Questions, suggestions, or remixes? Open an issue or PR!_

&copy; 2025 RODIX (Dixit Tharun Raja P)