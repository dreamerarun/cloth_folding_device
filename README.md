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


Hardware Requirements
Component	Quantity	Purpose
Arduino Uno	1	Main controller
Servo Motor	5	Folding mechanism
IR Sensor	1	Garment detection
Buzzer	1	Audible feedback
External 5–6 V Power Supply	1	Servo power
Breadboard	1	Circuit prototyping
Jumper Wires	As required	Electrical connections
Mechanical Folding Structure	1	Cloth folding mechanism
Pin Configuration
Servo Motors
Servo	Arduino Pin	Function
Servo 1	D9	Folding mechanism 1
Servo 2	D10	Folding mechanism 2
Servo 3	D11	Folding mechanism 3
Servo 4	D6	Folding mechanism 4
Servo 5	D5	Folding mechanism 5
IR Sensor
IR Sensor	Arduino
Analog Output	A0
VCC	5V
GND	GND
Buzzer

The code uses:

Buzzer	Arduino
Signal	D7
GND	GND

If your physical wiring uses another digital pin for the buzzer, change:

const int BUZZER_PIN = 7;

to the appropriate pin.

Circuit Diagram

The project uses an Arduino Uno as the main controller.

The IR sensor is connected to analog input A0, while the five servo motors are controlled through digital PWM-capable pins.

The buzzer provides audible feedback when a garment is detected and when the folding operation is completed.

Power Supply

The Arduino controls the servo motors, but the servo motors should be powered using a separate regulated power supply.

Recommended configuration
             +--------------------+
             |    Arduino Uno     |
             |                    |
             |  D9  -> Servo 1    |
             |  D10 -> Servo 2    |
             |  D11 -> Servo 3    |
             |  D6  -> Servo 4    |
             |  D5  -> Servo 5    |
             |  A0  <- IR Sensor  |
             |  D7  -> Buzzer     |
             +---------+----------+
                       |
                      GND
                       |
              Common Ground
                       |
        +--------------+--------------+
        |                             |
        v                             v
 Servo Power Supply              IR / Buzzer
     5–6 V
Important Power Warning

Do not connect a standard 5 V hobby servo directly to a 9 V battery.

The circuit illustration may show a 9 V battery, but the servo motors require a suitable regulated voltage.

Use an appropriate 5–6 V external supply capable of providing enough current for all five servos.

The external servo supply ground must be connected to the Arduino GND.

External Supply GND
        |
        +-------- Arduino GND
        |
        +-------- Servo GND

This creates a common ground reference between the Arduino and the servo power supply.

Servo Configuration

The initial folding angles are:

Servo	Home Position	Folding Position
Servo 1	0°	90°
Servo 2	0°	45°
Servo 3	0°	0°
Servo 4	0°	90°
Servo 5	0°	45°

These angles are only starting values.

The actual values must be calibrated according to:

Folding plate dimensions
Servo mounting position
Linkage geometry
Cloth dimensions
Servo mechanical limits
Desired folding pattern
IR Sensor Configuration

The IR sensor is connected to:

const int IR_SENSOR_PIN = A0;

The detection threshold is:

const int IR_THRESHOLD = 500;

The current program considers the garment to be present when:

IR value < IR_THRESHOLD

Therefore:

IR value < 500
        ↓
Garment detected

and:

IR value >= 500
        ↓
No garment detected

The threshold may need to be changed depending on the IR sensor, garment color, distance, lighting conditions, and sensor orientation.

IR Sensor Calibration

To calibrate the sensor:

Upload the Arduino program.
Open the Serial Monitor.
Set the baud rate to 9600.
Observe the IR value without a garment.
Place a garment in the detection area.
Observe the new sensor value.
Select an appropriate threshold between the two values.

For example:

Without garment:     700
With garment:        300

A threshold around:

const int IR_THRESHOLD = 500;

could then be appropriate.

Software Requirements

The project requires:

Arduino IDE
Arduino Uno board package
Arduino Servo library

The Servo library is included using:

#include <Servo.h>

No additional external libraries are required.

Installation
1. Clone the Repository
git clone https://github.com/YOUR_USERNAME/cloth-folding-device.git

Move into the project directory:

cd cloth-folding-device
2. Open the Arduino Code

Open:

cloth_folding_device.ino

using the Arduino IDE.

3. Select Arduino Uno

In Arduino IDE:

Tools → Board → Arduino Uno
4. Select the Arduino Port

Go to:

Tools → Port

and select the port connected to the Arduino Uno.

5. Upload

Click:

Upload

The Arduino will initialize the servos and begin monitoring the IR sensor.

Operating Sequence
Step 1 — Initialization

The Arduino initializes:

Five servo motors
IR sensor
Buzzer
Serial communication

The servos are then moved to their home positions.

Step 2 — Garment Detection

The Arduino continuously reads the IR sensor.

int irValue = analogRead(IR_SENSOR_PIN);

If the value crosses the configured detection threshold, the system identifies that a garment is present.

Step 3 — Detection Feedback

The buzzer produces a short beep.

Garment detected!

is also displayed on the Serial Monitor.

Step 4 — Folding

The five servos move sequentially:

Servo 1
   ↓
Servo 2
   ↓
Servo 3
   ↓
Servo 4
   ↓
Servo 5

A delay is provided between each movement to allow the mechanical mechanism to complete each folding action.

Step 5 — Completion

After the final servo movement, the buzzer produces a longer beep.

The Serial Monitor displays:

FOLDING SEQUENCE COMPLETED
Step 6 — Garment Removal

The system waits for the folded garment to be removed.

This prevents the same garment from immediately triggering another folding cycle.

Step 7 — Reset

After the garment is removed, all five servos return to their home positions.

The system is then ready for the next garment.

Serial Monitor

Set the Arduino Serial Monitor to:

9600 baud

Example output:

================================
     CLOTH FOLDING DEVICE
================================
System initialized successfully.
Waiting for garment...

IR Sensor Value: 720
IR Sensor Value: 715
IR Sensor Value: 310

Garment detected!
Initiating folding operation...

================================
STARTING FOLDING SEQUENCE
================================

Step 1: Activating Servo 1
Step 2: Activating Servo 2
Step 3: Activating Servo 3
Step 4: Activating Servo 4
Step 5: Activating Servo 5

================================
FOLDING SEQUENCE COMPLETED
================================

Waiting for folded garment to be removed...
Garment removed.

Resetting folding mechanism...
Mechanism returned to home position.

System ready for the next garment.
Adjusting the Folding Sequence

The servo angles can be modified in the following section:

const int SERVO1_FOLD = 90;
const int SERVO2_FOLD = 45;
const int SERVO3_FOLD = 0;
const int SERVO4_FOLD = 90;
const int SERVO5_FOLD = 45;

For example:

const int SERVO1_FOLD = 80;
const int SERVO2_FOLD = 60;
const int SERVO3_FOLD = 20;
const int SERVO4_FOLD = 100;
const int SERVO5_FOLD = 40;

Always test new angles gradually to avoid mechanical collisions.

Adjusting Folding Speed

The delay between servo movements is controlled by:

const int SERVO_DELAY = 500;

Increasing the value:

const int SERVO_DELAY = 1000;

will make the sequence slower.

Reducing it:

const int SERVO_DELAY = 300;

will make the sequence faster.

The optimum value depends on the mechanical system.

Project Structure
cloth-folding-device/
│
├── cloth_folding_device.ino
├── README.md
├── circuit_diagram.png
└── LICENSE
Safety Considerations
Servo Power

Do not power five servo motors directly from the Arduino Uno 5 V pin.

Use a suitable external 5–6 V servo power supply.

Common Ground

The Arduino GND and external servo power supply GND must be connected.

Mechanical Safety

Keep hands and fingers away from moving folding plates, linkages, and servo horns.

Servo Calibration

Start testing with small servo angles.

Do not immediately command servos to extreme positions.

Battery Safety

If using a 9 V battery in the prototype, do not connect it directly to the servo power terminals unless the voltage is appropriately regulated.

Limitations

The current system uses a predefined folding sequence.

It does not currently perform:

Automatic garment classification
Garment size estimation
Garment orientation detection
Computer vision
Dynamic folding path generation
Automatic servo position feedback
Closed-loop folding control

The servo angles therefore need to be calibrated for the particular mechanical design.

Future Improvements

Possible improvements include:

Computer vision based garment detection
Automatic garment orientation
Different folding patterns for different garments
Shirt, trouser, and towel folding modes
Multiple IR/distance sensors
Limit switches
Servo position feedback
Emergency stop button
OLED/LCD status display
Adjustable folding speed
Automatic garment size detection
Camera-based cloth detection
Machine-learning based garment classification
Automatic folded-cloth removal
Closed-loop motor control
Mobile/IoT monitoring
Applications

The concept can be extended to:

Smart laundry systems
Automated garment handling
Textile automation
Domestic automation
Educational robotics
Mechatronics projects
Robotic manipulation
Assistive automation
Automated clothing processing
Project Objective

The primary objective of this project is to develop a low-cost prototype capable of automating a basic cloth-folding operation using readily available embedded-system components.

The project demonstrates the integration of:

Embedded control
Sensor-based detection
Servo actuation
Sequential motion control
Mechanical automation
Human-machine interaction

Author

Arun M.

Robotics & Automation Engineering

Interests: Robotics, Physical AI, Autonomous Systems, Robotic Manipulation and Intelligent Automation.
