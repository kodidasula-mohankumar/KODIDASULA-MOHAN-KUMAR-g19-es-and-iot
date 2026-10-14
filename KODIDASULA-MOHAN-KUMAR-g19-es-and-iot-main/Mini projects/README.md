 Smart 16x2 LCD Character Movement with LDR-Based Mode Selection

A simple Arduino-based mini project that controls a custom character on a 16×2 I2C LCD using push buttons and an LDR (Light Dependent Resistor).

The project has two operating modes:

Manual Mode: Move the character left or right using push buttons.

Automatic Mode: When sufficient light is detected by the LDR, the character automatically moves across the LCD while an LED and buzzer provide a signal.

Features

16×2 I2C LCD display

Custom happy-face character

Left and right push-button control

Automatic movement using an LDR

LED and buzzer indication when automatic mode starts

Button debouncing for reliable input

Automatic character movement from left to right and back

Simple and beginner-friendly Arduino project

Components Required
Component	Quantity
Arduino board	1
16×2 I2C LCD	1
LDR	1
Push Button	2
LED	1
Buzzer	1
Resistors	As required
Jumper wires	As required
Breadboard	1
Pin Connections
Component	Arduino Pin
Left Button	D2
Buzzer	D3
LED	D4
Right Button	D5
LDR	A0
LCD SDA	A4*
LCD SCL	A5*

Note: For Arduino boards other than the Uno/Nano, the I2C SDA and SCL pins may be different.

How It Works
Manual Mode

When the LDR detects light below the configured threshold, the project operates in MANUAL mode.

Press the left button to move the character one position to the left.

Press the right button to move the character one position to the right.

The character cannot move outside the 16-column LCD.

Automatic Mode

When the LDR reading reaches or exceeds the threshold:

int threshold = 500;


the project switches to AUTO mode.

The following sequence occurs:

The LCD displays AUTO.

The LED and buzzer turn on and off three times.

The character begins moving automatically.

The character travels from one side of the LCD to the other.

When it reaches an edge, the direction reverses.

LDR Threshold

The automatic mode is controlled by:

int threshold = 500;


You can change this value depending on the lighting conditions and your LDR circuit.

For example:

int threshold = 700;


will require a higher LDR reading before automatic mode is activated.

LCD Character

The project creates a custom character using:

byte happyface[8] = {
  B01010,
  B01010,
  B10001,
  B01110
};


The character is stored in LCD custom-character memory and displayed using:

lcd.write(byte(0));

Software Requirements

Arduino IDE

LiquidCrystal_I2C library

Arduino-compatible board

Install the LiquidCrystal_I2C library through the Arduino IDE Library Manager if it is not already installed.

Main Program Logic

The basic control flow is:

             Start
               |
               v
        Initialize LCD
               |
               v
        Read LDR value
               |
       +-------+-------+
       |               |
   Light >= 500    Light < 500
       |               |
       v               v
   AUTO MODE       MANUAL MODE
       |               |
       v               v
 LED + Buzzer      Read Buttons
    Signal             |
       |          +----+----+
       |          |         |
       |        Left      Right
       |          |         |
       |          v         v
       |       Move      Move
       |       Left      Right
       |          \         /
       |           \       /
       |            v     v
       |       Update LCD
       |
       v
 Automatic Character
      Movement
       |
       v
 Reverse Direction
    At LCD Edge
