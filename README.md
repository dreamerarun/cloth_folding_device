# Cloth Folding Device

An Arduino Uno based automated cloth folding system that detects the presence of a garment using an IR sensor and performs a predefined folding sequence using five servo motors.

The system combines **sensor-based garment detection, servo motor control, sequential actuation, and audible feedback** to automate a basic cloth-folding process.

---

## Features

- Automatic garment detection using an IR sensor
- Five-servo mechanical folding system
- Sequential servo actuation
- Configurable servo angles
- Configurable IR detection threshold
- Buzzer feedback
- Automatic mechanism reset
- Serial Monitor status messages
- Protection against immediately repeating the folding cycle
- Simple Arduino-based control architecture

---

## Working Principle

The system continuously monitors an IR sensor placed near the garment loading area.

When a garment is detected:

1. The Arduino detects the garment through the IR sensor.
2. The buzzer provides an indication that the garment has been detected.
3. Servo 1 performs the first folding movement.
4. Servo 2 performs the second folding movement.
5. Servo 3 performs the third folding movement.
6. Servo 4 performs the fourth folding movement.
7. Servo 5 performs the final folding movement.
8. The buzzer indicates that folding is complete.
9. The system waits for the folded garment to be removed.
10. All servos return to their home positions.
11. The system waits for the next garment.

---

## System Flow

```text
                 START
                   |
                   v
          Initialize Arduino
                   |
                   v
        Initialize 5 Servos
                   |
                   v
          Initialize IR Sensor
                   |
                   v
             Read IR Sensor
                   |
          +--------+--------+
          |                 |
     No Garment         Garment Found
          |                 |
          |                 v
          |          Buzzer Indication
          |                 |
          |                 v
          |             Servo 1
          |                 |
          |                 v
          |             Servo 2
          |                 |
          |                 v
          |             Servo 3
          |                 |
          |                 v
          |             Servo 4
          |                 |
          |                 v
          |             Servo 5
          |                 |
          |                 v
          |          Folding Complete
          |                 |
          |                 v
          |       Wait for Cloth Removal
          |                 |
          |                 v
          |          Reset All Servos
          |                 |
          +<----------------+
