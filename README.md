# AVR Bare-Metal Synthesizer

A low-level synthesizer developed for the **ATmega328P** (Arduino Uno R3) using the pure AVR toolchain. This project bypasses the standard Arduino abstraction layers, utilizing direct register manipulation and a custom build system to achieve high performance and a minimal binary footprint.

## 🚀 Overview
The synthesizer operates by mapping physical buttons to specific musical notes. By configuring the microcontroller's internal **16-bit Timer 1** in CTC (Clear Timer on Compare Match) mode, it generates precise square wave frequencies for a buzzer or speaker.

* **Binary Size:** < 300 bytes.
* **Architecture:** Bare-metal C (no Arduino libraries).
* **Hardware Interface:** 7-button keyboard (Active-low polling, no potentiometers).

## 🛠️ System Architecture

The project is structured to separate hardware configuration, musical data, and execution logic:

* **`src/main.c`**: Contains the hardware initialization, GPIO polling logic, and the state machine for audio output.
* **`include/pitches.h`**: A header file defining the OCR1A register values for musical notes, calculated for a 16MHz clock with a prescaler of 8.
* **`Makefile`**: A custom automation script for compiling via `avr-gcc` and flashing via `avrdude`.

## 🎹 Note Mapping & Hardware Pins

| Note | Frequency | AVR Pin | Arduino Equivalent | Input Type |
| :--- | :--- | :--- | :--- | :--- |
| **C4** | 261.63 Hz | PC0 | **A0** | Internal Pull-up |
| **D4** | 293.66 Hz | PC1 | **A1** | Internal Pull-up |
| **E4** | 329.63 Hz | PC2 | **A2** | Internal Pull-up |
| **F4** | 349.23 Hz | PC3 | **A3** | Internal Pull-up |
| **G4** | 392.00 Hz | PC4 | **A4** | Internal Pull-up |
| **A4** | 440.00 Hz | PC5 | **A5** | Internal Pull-up |
| **B4** | 493.88 Hz | PD2 | **D2** | Internal Pull-up |
| **AUDIO**| PWM (OC1A)| PB1 | **D9** | **Output** |

## ⚙️ Technical Implementation

### Frequency Generation
The frequency of the notes is determined by the formula:
$$OCR1A = \frac{F\_CPU}{2 \cdot N \cdot \text{Frequency}} - 1$$
Where **$N$** (Prescaler) is set to 8. This allows for high-resolution pitch control across the mid-range octaves.

### Polling & Execution
The software uses a non-blocking polling mechanism to check the state of **Port C** and **Port D**. When a button is pressed (logic 0), Timer 1 is enabled, and the `COMPARE_REGISTER` is updated with the corresponding pitch value. The system ensures immediate note transitions by resetting the timer counter (`TCNT1`) upon frequency changes.

## 🔧 Installation and Usage

```bash
# 1. Clone the repository
git clone [https://github.com/steve-caiula/AVR-Bare-Metal-Synthesizer.git](https://github.com/steve-caiula/AVR-Bare-Metal-Synthesizer.git)
cd AVR-Bare-Metal-Synthesizer

# 2. Compile the project
make

# 3. Flash to Arduino Uno (Ensure PORT is correct in Makefile)
make flash

# 4. Clean build artifacts
make clean
```

## 👤 Author
Stefano Caiula (steve-caiula)