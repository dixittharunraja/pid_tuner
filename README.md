# pid_tuner

**pid_tuner** by **RODIX (Dixit Tharun Raja P)**

[![License: CC BY-NC 4.0](https://img.shields.io/badge/License-CC--BY--NC%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc/4.0/)

**pid_tuner** is an open-source hardware plus firmware system for convenient, wireless, real-time tuning of PID (Proportional–Integral–Derivative) controller parameters. This project combines a custom-built transmitter (portable, battery powered, encoder-driven) with a simple Arduino-based PID receiver library for direct integration into your robotics, automation, or control system projects.

## 🚀 Features

- **Wireless PID Value Tuning** – Send Kp, Ki, Kd updates via HC-12 radio module—no USB or cable required
- **User-Friendly Physical UI** – 3 rotary encoders with push, crystal-clear OLED display, and two tactile buttons for Save and Reset
- **Live Visual Feedback** – OLED shows each parameter, explicit feedback for ‘Sent’, ‘Save!’, and ‘Reset!’ actions
- **EEPROM Persistence** – Save or reset parameters with a button, persistence across power cycles
- **3D-Printable Enclosure** – Rugged, portable, open hardware design (Fusion 360, .step, .obj included)
- **Simple Integration** – Arduino library for receiver, easy drop-in to your existing project

## 📦 Hardware

| Component             | Purpose                        |
|-----------------------|--------------------------------|
| Arduino Nano          | Main controller                |
| 3x Rotary Encoders    | For Kp/Ki/Kd adjustment        |
| 0.96" I2C OLED        | Screen feedback                |
| 2x Push Buttons       | Save & Reset                   |
| HC-12 Module          | Wireless link                  |
| 360mAh 2S LiPo        | Power source                   |
| MRB045 Charger        | Safe, USB-C battery charging   |
| 5V 3A BEC             | Converts battery to clean 5V   |
| 10A Rocker switch     | On/off control                 |
| 3D-printed enclosure  | All files in `enclosure/`      |

## 📂 Repository Structure

| Folder           | Content                                                      |
|------------------|--------------------------------------------------------------|
| `pidtx/`         | Transmitter code (`pidtx.ino`), images                       |
| `pidrx/`         | Receiver Arduino library, usage example                      |
| `enclosure/`     | Fusion 360 models, .step/.obj files for 3D printing          |
| `README.md`      | This overview                                                |
| `INSTRUCTIONS.md`| Full assembly, wiring, and use guide                         |
| `LICENSE`        | License and use terms                                        |

## 🔧 How It Works

* Rotate an encoder → instantly updates value for Kp, Ki, or Kd.
* Press encoder → current value is wirelessly sent (OLED: ‘Kp Sent!’ etc.).
* Press **Save** → All values are saved to EEPROM, OLED: ‘Save!’
* Press **Reset** → All values reset to 0, OLED: ‘Reset!’
* All actions get clear, single-screen, time-limited feedback before returning to the value dashboard.

## 🛠 Quick Start

1. **Assemble** transmitter using instructions and enclosure models.
2. **Program** the transmitter Arduino Nano using `pidtx/pidtx.ino`.
3. **Connect and program** your receiver system using the `pidrx` library (see example).
4. **Tune wirelessly**—no computer needed in the field!

## 🖧 Example Protocol

| Action        | HC-12 Serial Command Sent       |
|---------------|---------------------------------|
| Set Kp        | `KP,12\n`                       |
| Set Ki        | `KI,7\n`                        |
| Set Kd        | `KD,3\n`                        |
| Save to EEPROM| `SAVE\n`                        |
| Reset         | `RESET\n`                       |

## ⬇️ [Build & Use Instructions](INSTRUCTIONS.md)

See ***INSTRUCTIONS.md*** for full wiring diagrams, enclosure assembly, and troubleshooting.


## 📝 License

**This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0).**

_You may use, adapt, remix, and share for non-commercial purposes with proper credit.  
Commercial use is not permitted without the express written permission of ROÐIX (Dixit Tharun Raja P).  
See the `LICENSE` file and https://creativecommons.org/licenses/by-nc/4.0/ for details._

---

_Built with Arduino IDE & Fusion 360.  
&copy; 2025 RODIX (Dixit Tharun Raja P)_