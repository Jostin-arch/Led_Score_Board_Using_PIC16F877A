# PIC16F877A Scoreboard & Timer Project

This repository contains the firmware for a versatile digital display system built with a PIC16F877A microcontroller. Designed for hobbyists, students, and electronics enthusiasts, this project can be used for local sports events, classroom experiments, or as a lab utility.

The system features a 4-digit 7-segment display and can be compiled to operate in one of two distinct modes: a two-team **Scoreboard** or a configurable **Countdown/Count-up Timer**.


## Features

This project can be compiled to perform one of the following functions:

### Scoreboard Mode (`score_count.c`)
* **Dual Score Tracking:** Keeps score for two separate teams from 0 to 99.
* **Simple Controls:** Uses two dedicated push buttons to increment the score for each team.
* **Real-time Display:** Scores are instantly updated on the 4-digit display.

### Timer Mode (`Time_counter.c`)
* **Dual Functionality:** Operates as both a countdown and a count-up timer.
* **UART Configuration:** The initial time is set by sending 6 digits (e.g., "053000" for 5m 30s) via a serial connection (9600 baud rate).
* **On-the-fly Controls:** Features hardware buttons for pausing/resuming the timer and switching modes.

---

## Functional Overview

* **Display Driving:** Both modes use **display multiplexing** (Persistence of Vision) to drive the 4-digit 7-segment display.
    * The `Time_counter.c` firmware uses a **Timer0 interrupt** for a precise, non-blocking refresh cycle.
    * The `score_count.c` firmware uses software `__delay_ms()` calls in a loop.
* **Input Handling:** Inputs are read by polling the state of the connected push buttons. Basic software debouncing is implemented with small delays to prevent false triggers.
* **Serial Communication (Timer Mode):** The timer leverages the PIC's built-in UART module to receive configuration data. It waits for 6 specific ASCII characters to set the initial minutes and seconds before starting.

---

## Hardware Requirements

| Component | Quantity | Description |
| :--- | :--- | :--- |
| **Microcontroller** | 1 | PIC16F877A |
| **Display** | 1 | 4-Digit 7-Segment Display (Common Anode) |
| **Oscillator** | 1 | 20 MHz Crystal Oscillator (with two ~22pF capacitors) |
| **Input** | 2-4 | Push Buttons |
| **Display Drivers** | 4 | NPN Transistors (e.g., BC547) for digit selection |
| **Serial Interface**| 1 | USB-to-TTL Serial Converter (e.g., FT232RL) - **Required for Timer Mode only** |
| **Misc.** | various | Resistors, 5V Power Supply, Wires |

---

## Pin Connections

The two firmware modes use different pin configurations. Wire your circuit according to the mode you intend to flash.

### Pinout for Scoreboard Mode (`score_count.c`)

| PIC16F877A Pin | Connection | Function |
| :--- | :--- | :--- |
| **PORTB & PORTD** | 7-Segment Pins (a-g) | Segment Drivers |
| **RC0 - RC3** | Digit Select Transistors | Activates each of the four digits |
| **RC4 / RC5** | Push Buttons | Increment Score (Team 1 / Team 2) |

### Pinout for Timer Mode (`Time_counter.c`)

| PIC16F877A Pin | Connection | Function |
| :--- | :--- | :--- |
| **PORTB** | 7-Segment Pins (a-g) | Segment Driver (All Digits) |
| **RC0 - RC3** | Digit Select Transistors | Activates each of the four digits |
| **RD4 / RD5** | Push Buttons | Pause/Resume & Mode Select |
| **RC6 (TX) / RC7 (RX)**| Serial Module Pins | UART Communication |

---

## Project Structure
SCORE_BOARD/
│
├── src/                # Contains all .c and .h source files
│   ├── score_count.c
│   └── Time_counter.c
│
├── hardware/           # Contains schematics and hardware-related files
│   └── schematic.png
│
├── .gitignore          # Tells Git which files to ignore (e.g., build files)
│
└── README.md           # This documentation file


## Software and Tools

* **IDE:** MPLAB X IDE (v6.0 or later)
* **Compiler:** Microchip XC8 C Compiler (v2.40 or later)
* **Programmer:** Microchip PICkit 3, PICkit 4, or similar hardware programmer.

---

## How to Compile and Use

This project contains two different main programs. You must choose which one to compile.

1.  **Open Project:** Open the project folder in MPLAB X IDE.
2.  **Select Firmware:** In the "Projects" pane on the left, you will see your source files (`score_count.c` and `Time_counter.c`).
    * Decide which mode you want to use.
    * Right-click on the C file you **do not** want to use and select **"Exclude from Build"**.
3.  **Clean and Build:** Clean and build the project by clicking the "hammer and broom" icon. This will compile only the included C file and generate a `.hex` file.
4.  **Program Device:** Connect your PICkit programmer and flash the generated `.hex` file to your PIC16F877A using the "Make and Program Device" button.
5.  **Run:** Power on your circuit and it will operate in the mode you selected.

---

## Future Improvements & Contributing

This project is a great foundation for further development. Contributions and suggestions are welcome!

* **Unified Firmware:** Combine both modes into a single firmware, using a button on startup to select the desired mode.
* **EEPROM Storage:** Use the internal EEPROM to save the last scores or timer settings so they are not lost on power down.
* **Sound Notifications:** Add a buzzer to signal the end of a countdown or other events.

---

## License

This project is licensed under the MIT License. This is a permissive license that allows you to use, copy, modify, and distribute the code freely.