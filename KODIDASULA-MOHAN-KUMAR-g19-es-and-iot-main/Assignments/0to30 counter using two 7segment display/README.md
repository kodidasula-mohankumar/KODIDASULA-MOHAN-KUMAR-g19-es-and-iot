#  0–30 Counter Using Two 7-Segment Displays

## Project Overview

This project uses an **Arduino Uno** and two 7-segment displays to count from **0 to 30**. The Arduino generates the tens and units digits, then sends each digit to the corresponding display through four digital output pins.

The circuit uses **CD4511 BCD-to-7-segment decoder/driver ICs** to drive the displays. The project was designed and simulated in **Tinkercad Circuits**.

## Components Required

- Arduino Uno R3
- 2 × 7-segment displays (common-cathode type, compatible with CD4511)
- 2 × CD4511 BCD-to-7-segment decoder/driver ICs
- Current-limiting resistors for the display segments, as required by the circuit
- Breadboard and jumper wires
- Tinkercad Circuits (for online simulation)

## Pin Connections

The Arduino uses digital pins **2–9** as two groups of four BCD outputs.

| Arduino pin | Purpose | Digit bit |
|---|---|---|
| 2 | Units display BCD input | Bit 0 (LSB) |
| 3 | Units display BCD input | Bit 1 |
| 4 | Units display BCD input | Bit 2 |
| 5 | Units display BCD input | Bit 3 (MSB) |
| 6 | Tens display BCD input | Bit 0 (LSB) |
| 7 | Tens display BCD input | Bit 1 |
| 8 | Tens display BCD input | Bit 2 |
| 9 | Tens display BCD input | Bit 3 (MSB) |

**Note:** In the code, pins 2–5 are written with the `tens` value and pins 6–9 with the `units` value, despite the comments labeling these groups the other way around. Verify the physical wiring and decoder connections so the tens and units digits appear in the intended positions.

## How It Works

1. `setup()` configures Arduino pins 2 through 9 as outputs.
2. The `loop()` counts from 0 through 30.
3. `num / 10` calculates the tens digit.
4. `num % 10` calculates the units digit.
5. Bitwise operations (`&` and `>>`) extract the four bits of each digit.
6. The Arduino sends those bits to the decoder inputs.
7. `delay(1000)` pauses for one second before displaying the next count.

## Arduino Code

```cpp
int input[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(input[i], OUTPUT);
  }
}

void loop() {
  for (int num = 0; num <= 30; num++) {
    int tens = num / 10;
    int units = num % 10;

    // Pins 2, 3, 4, 5 receive the tens digit
    digitalWrite(input[0], tens & 1);
    digitalWrite(input[1], (tens >> 1) & 1);
    digitalWrite(input[2], (tens >> 2) & 1);
    digitalWrite(input[3], (tens >> 3) & 1);

    // Pins 6, 7, 8, 9 receive the units digit
    digitalWrite(input[4], units & 1);
    digitalWrite(input[5], (units >> 1) & 1);
    digitalWrite(input[6], (units >> 2) & 1);
    digitalWrite(input[7], (units >> 3) & 1);

    delay(1000);
  }
}
```

## Important Technical Note

The code above calculates the **tens digit** for pins 2–5 and the **units digit** for pins 6–9. Make sure the physical display connected to pins 2–5 is the tens display and the display connected to pins 6–9 is the units display, or swap the two code sections to match your wiring.

The CD4511 accepts BCD inputs, so each digit should be in the range 0–9. The code splits the count into two decimal digits before sending them to the decoders.

## Expected Output

The displays count upward once per second:

`00 → 01 → 02 → ... → 09 → 10 → 11 → ... → 29 → 30`

After displaying 30, the inner `for` loop ends. Because `loop()` repeats in Arduino, the count starts again at 00.

## How to Run

1. Open the circuit in Tinkercad Circuits, or assemble the circuit using the listed components.
2. Check that each CD4511 is connected to the correct display type and BCD input pins.
3. Confirm that the displays have appropriate current-limiting resistors and that power and ground connections are correct.
4. Upload the code to the Arduino Uno.
5. Start the simulation or power the circuit and observe the count.

## Concepts Practiced

- Arduino digital outputs
- Arrays and `for` loops in C/C++
- Integer division (`/`) and modulo (`%`)
- Bitwise AND (`&`) and right shift (`>>`)
- BCD digit extraction
- Interfacing 7-segment displays using decoder ICs

## Future Improvements

- Use `millis()` instead of `delay()` for non-blocking timing.
- Add buttons to start, stop, or reset the counter.
- Extend the counter range or change the counting direction.

## Author

Created as an Arduino circuit-design assignment and simulated using Tinkercad Circuits.
