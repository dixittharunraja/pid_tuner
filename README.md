# pid_tuner

**pid_tuner** is an open-source Arduino library and protocol for seamless, wireless, and persistent tuning of PID controller parameters. It is designed for embedded systems engineers, robotics enthusiasts, and anyone who needs to adjust PID gains in real time—without recompiling code or physically accessing the device.

---

## 🚀 Concept

Traditionally, tuning PID (Proportional, Integral, Derivative) parameters on microcontrollers is tedious. Most workflows require:
- Hardcoding new values in firmware
- Re-uploading code for every adjustment
- Manual serial input or clunky UI
- No persistent storage (values lost after reset)

**pid_tuner** solves these problems by enabling:
- **Wireless, real-time updates** of Kp, Ki, Kd via a simple serial protocol (e.g., HC-12, Bluetooth, XBee, etc.)
- **Persistent storage** of parameters in EEPROM with a single command
- **Separation of tuning interface and control logic**—so you can focus on your application, not the plumbing

---

## ⚡️ Why not just use Serial/USB?

Conventional methods, such as using the Arduino Serial Monitor or hardcoding values, have multiple drawbacks:
- **Physical access required:** You must connect a cable to the device, which is often impractical for mobile robots or deployed systems.
- **No real-time feedback:** Changing values requires stopping the process, editing code, and re-uploading.
- **No persistence:** Serial input is lost after a power cycle unless you add extra code for storage.
- **Error-prone:** Manual entry and code changes increase the risk of mistakes and bugs.

---

## 🛠️ Problem Solved by pid_tuner

- **Wireless tuning:** Update parameters from a remote controller or GUI, even while the system is running.
- **Immediate effect:** Changes take place in real time—no need to stop or reset your device.
- **Persistent storage:** A single "save" command stores the current values in EEPROM, surviving power cycles.
- **Minimal integration:** Just include the library, call `update()` in your loop, and use `getKp()`, `getKi()`, `getKd()` in your control logic.
- **Protocol simplicity:** The library uses a human-readable, robust serial protocol (`KP,10\n`, `KI,5\n`, `KD,2\n`, `SAVE\n`, `RESET\n`).

---

## 📦 Features

- Wireless PID parameter updates (Kp, Ki, Kd) via serial protocol
- EEPROM-backed persistent storage
- Lightweight and easy to integrate
- Compatible with HC-12, Bluetooth, or any serial radio
- Example sketches included

---

## 📚 Getting Started

### Hardware

- Arduino-compatible board (Nano, Uno, Leonardo, etc.)
- HC-12 or compatible serial wireless module

### Installation

1. Clone or download this repository into your Arduino `libraries` folder.
2. Restart the Arduino IDE.
3. Open `File > Examples > pid_tuner > BasicUsage`.

---

## 🧩 Integration Example

- Use a wireless transmitter (another Arduino, GUI, etc.) to send parameter updates.
- The receiver runs `pid_tuner`, updating and saving PID parameters as instructed.

---

## ⚠️ Limitations & Future Work

- Currently supports integer PID values; floating-point support is planned.
- Assumes exclusive use of the selected serial port for PID tuning.
- Security/authentication is not implemented (for trusted/lab environments).

---

## 🤝 Contributing

Contributions, bug reports, and feature requests are welcome!  
Please open an issue or submit a pull request.

---

## 💡 Inspiration

pid_tuner was created to make embedded PID tuning as seamless as possible, freeing you from the constraints of cables, code changes, and manual entry.  
If you find it useful, please star the repo and share your projects!

