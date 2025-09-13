# Advanced PIC16F877A Digital Scoreboard & Display

This project is an advanced digital scoreboard and multi-purpose display system built around the PIC16F877A microcontroller. It features a dual-display system: a 4-digit 7-segment display for primary numerical data (like scores or timers) and a 16x2 character LCD for secondary information (like team names, status messages, or menus).

## Hardware & Connections

The circuit for this project was designed and simulated in Proteus. It is crucial to wire all components correctly for the firmware to function as intended.

### Circuit Schematic
*(Suggestion: Place your schematic image in a `hardware/` folder and link to it here. This makes your project look very professional!)*

![Circuit Schematic](hardware/schematic.png)


### Bill of Materials

| Part ID | Component | Quantity | Description |
| :--- | :--- | :--- | :--- |
| U1 | PIC16F877A | 1 | 8-bit Microcontroller |
| LCD1 | LM016L | 1 | 16x2 Character LCD Display |
| DISP1 | 7-SEG-MPX4-CA | 1 | 4-Digit Common Anode 7-Segment Display |
| BTN1-4 | PUSH BUTTON | 4 | User Input Buttons |
| R1 | 10kΩ Resistor | 1 | MCLR Pull-up Resistor |
| - | 10kΩ Potentiometer | 1 | LCD Contrast Control |
| - | Transistors (NPN) | 4 | For driving 7-segment digit pins |
| - | Resistors | various | Current limiting for LEDs, pull-downs for buttons |

### Pinout Details

#### 16x2 LCD Connections
The LCD is controlled in 4-bit mode to save I/O pins.

| LCD Pin | PIC16F877A Pin | Function |
| :--- | :--- | :--- |
| **RS** | `RB0` | Register Select |
| **EN** | `RB1` | Enable |
| **D4** | `RB4` | Data Bit 4 |
| **D5** | `RB5` | Data Bit 5 |
| **D6** | `RB6` | Data Bit 6 |
| **D7** | `RB7` | Data Bit 7 |
| **VEE** | Potentiometer | Contrast Adjustment |

#### 4-Digit 7-Segment Display Connections
The display is multiplexed to show four digits using a single I/O port for the segments.

| 7-Segment Pin | PIC16F877A Pin | Function |
| :--- | :--- | :--- |
| **a-g, dp** | `PORTC (RC0-RC7)` | Segment Lines (Common to all digits) |
| **Digit 1 Select** | `RD0` | Activates Digit 1 |
| **Digit 2 Select** | `RD1` | Activates Digit 2 |
| **Digit 3 Select** | `RD2` | Activates Digit 3 |
| **Digit 4 Select** | `RD3` | Activates Digit 4 |

#### User Input Button Connections

| Button | PIC16F877A Pin | Function |
| :--- | :--- | :--- |
| **Button 1** | `RD4` | User Defined (e.g., Up / Score Team 1) |
| **Button 2** | `RD5` | User Defined (e.g., Down / Score Team 2) |
| **Button 3** | `RD6` | User Defined (e.g., Mode / Next) |
| **Button 4** | `RD7` | User Defined (e.g., Reset / Enter) |
| **Reset Button** | `MCLR` | Master Reset |

### Important Hardware Note
* **Crystal Oscillator:** The C code for this project should be configured for a **20 MHz High-Speed (HS) crystal oscillator**. You must connect a 20 MHz crystal with two ~22pF capacitors to the `OSC1` (Pin 13) and `OSC2` (Pin 14) pins for the firmware to run correctly.

## Software and Tools

* **IDE:** MPLAB X IDE (v6.0 or later)
* **Compiler:** Microchip XC8 C Compiler (v2.40 or later)
* **Programmer:** Microchip PICkit 3, PICkit 4, or similar hardware programmer.
* **Simulation:** Proteus Design Suite (optional).

## How to Compile and Use

1.  **Open the Project:** Open the project folder in the MPLAB X IDE.
2.  **Clean and Build:** Use the "Clean and Build Main Project" button (the hammer and broom icon) to compile the code. This will generate a `.hex` file inside the `dist/` directory of your project folder.
3.  **Program the Device:** Connect your PICkit programmer to your computer and the PIC microcontroller. Use the "Make and Program Device Main Project" button (the green arrow pointing down to a chip) to flash the generated `.hex` file onto your PIC.
4.  **Run:** Power on your circuit. The scoreboard should now be operational.

## Project Structure

A clean and organized folder structure is recommended for this project.