/*
 * ============================================================
 *              CLOTH FOLDING DEVICE
 * ============================================================
 *
 * Controller : Arduino Uno
 * Sensors    : IR Sensor
 * Actuators  : 5 Servo Motors + Buzzer
 *
 * Description:
 * The system detects the presence of a garment using an IR
 * sensor. Once a garment is detected, five servo motors are
 * activated sequentially to perform the predefined folding
 * operation.
 *
 * After completing the folding operation, the system waits
 * for the folded garment to be removed and then returns all
 * servos to their home positions.
 *
 * ============================================================
 */

#include <Servo.h>

// ============================================================
// SERVO OBJECTS
// ============================================================

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

// ============================================================
// PIN CONFIGURATION
// ============================================================

// IR sensor
const int IR_SENSOR_PIN = A0;

// Servo pins
const int SERVO1_PIN = 9;
const int SERVO2_PIN = 10;
const int SERVO3_PIN = 11;
const int SERVO4_PIN = 6;
const int SERVO5_PIN = 5;

// Buzzer
const int BUZZER_PIN = 7;

// ============================================================
// IR SENSOR CONFIGURATION
// ============================================================

// Adjust this value according to the actual IR sensor.
const int IR_THRESHOLD = 500;

// ============================================================
// SERVO HOME POSITIONS
// ============================================================
//
// These are the starting positions of the folding mechanism.
// Adjust them according to the mechanical design.
//

const int SERVO1_HOME = 0;
const int SERVO2_HOME = 0;
const int SERVO3_HOME = 0;
const int SERVO4_HOME = 0;
const int SERVO5_HOME = 0;

// ============================================================
// SERVO FOLDING POSITIONS
// ============================================================
//
// These angles define the folding sequence.
//

const int SERVO1_FOLD = 90;
const int SERVO2_FOLD = 45;
const int SERVO3_FOLD = 0;
const int SERVO4_FOLD = 90;
const int SERVO5_FOLD = 45;

// ============================================================
// TIMING CONFIGURATION
// ============================================================

const int SERVO_DELAY = 500;          // Delay between servo movements
const int START_BEEP_TIME = 200;      // Garment detection beep
const int COMPLETE_BEEP_TIME = 500;   // Folding completion beep
const int REMOVE_CLOTH_DELAY = 2000;  // Waiting time
const int SENSOR_DELAY = 100;         // Sensor polling interval

// ============================================================
// FUNCTION: BUZZER BEEP
// ============================================================

void beep(int duration) {

  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
}

// ============================================================
// FUNCTION: RESET SERVOS
// ============================================================
//
// Moves all servos back to their starting positions.
//

void resetServos() {

  Serial.println("Resetting folding mechanism...");

  servo1.write(SERVO1_HOME);
  delay(200);

  servo2.write(SERVO2_HOME);
  delay(200);

  servo3.write(SERVO3_HOME);
  delay(200);

  servo4.write(SERVO4_HOME);
  delay(200);

  servo5.write(SERVO5_HOME);
  delay(200);

  Serial.println("Mechanism returned to home position.");
}

// ============================================================
// FUNCTION: GARMENT DETECTION
// ============================================================
//
// Reads the analog value from the IR sensor.
//
// Current configuration:
//     IR value < threshold -> garment detected
//
// If your sensor behaves in the opposite direction,
// change '<' to '>'.
//

bool isGarmentDetected() {

  int irValue = analogRead(IR_SENSOR_PIN);

  Serial.print("IR Sensor Value: ");
  Serial.println(irValue);

  if (irValue < IR_THRESHOLD) {
    return true;
  }

  return false;
}

// ============================================================
// FUNCTION: FOLD CLOTH
// ============================================================
//
// Executes the predefined folding sequence.
//
// Servo movement order:
// Servo 1 -> Servo 2 -> Servo 3 -> Servo 4 -> Servo 5
//

void foldCloth() {

  Serial.println();
  Serial.println("================================");
  Serial.println("STARTING FOLDING SEQUENCE");
  Serial.println("================================");

  // ----------------------------------------------------------
  // STEP 1
  // ----------------------------------------------------------

  Serial.println("Step 1: Activating Servo 1");

  servo1.write(SERVO1_FOLD);

  delay(SERVO_DELAY);

  // ----------------------------------------------------------
  // STEP 2
  // ----------------------------------------------------------

  Serial.println("Step 2: Activating Servo 2");

  servo2.write(SERVO2_FOLD);

  delay(SERVO_DELAY);

  // ----------------------------------------------------------
  // STEP 3
  // ----------------------------------------------------------

  Serial.println("Step 3: Activating Servo 3");

  servo3.write(SERVO3_FOLD);

  delay(SERVO_DELAY);

  // ----------------------------------------------------------
  // STEP 4
  // ----------------------------------------------------------

  Serial.println("Step 4: Activating Servo 4");

  servo4.write(SERVO4_FOLD);

  delay(SERVO_DELAY);

  // ----------------------------------------------------------
  // STEP 5
  // ----------------------------------------------------------

  Serial.println("Step 5: Activating Servo 5");

  servo5.write(SERVO5_FOLD);

  delay(SERVO_DELAY);

  // ----------------------------------------------------------
  // FOLDING COMPLETE
  // ----------------------------------------------------------

  Serial.println();
  Serial.println("================================");
  Serial.println("FOLDING SEQUENCE COMPLETED");
  Serial.println("================================");

  // Completion beep
  beep(COMPLETE_BEEP_TIME);
}

// ============================================================
// FUNCTION: WAIT FOR GARMENT REMOVAL
// ============================================================

void waitForGarmentRemoval() {

  Serial.println("Waiting for folded garment to be removed...");

  delay(REMOVE_CLOTH_DELAY);

  /*
   * Wait until the IR sensor no longer detects the garment.
   *
   * This prevents the system from immediately starting another
   * folding cycle while the previous garment is still present.
   */

  while (isGarmentDetected()) {

    Serial.println("Garment still detected.");
    delay(500);
  }

  Serial.println("Garment removed.");
}

// ============================================================
// SETUP
// ============================================================

void setup() {

  // Start Serial Monitor
  Serial.begin(9600);

  // Configure buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);

  // Attach servo motors
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo4.attach(SERVO4_PIN);
  servo5.attach(SERVO5_PIN);

  // Move all servos to starting positions
  resetServos();

  // Startup beep
  beep(200);

  Serial.println();
  Serial.println("================================");
  Serial.println("     CLOTH FOLDING DEVICE");
  Serial.println("================================");
  Serial.println("System initialized successfully.");
  Serial.println("Waiting for garment...");
  Serial.println();
}

// ============================================================
// MAIN LOOP
// ============================================================

void loop() {

  // ----------------------------------------------------------
  // CHECK FOR GARMENT
  // ----------------------------------------------------------

  if (isGarmentDetected()) {

    Serial.println();
    Serial.println("Garment detected!");
    Serial.println("Initiating folding operation...");

    // Detection beep
    beep(START_BEEP_TIME);

    // --------------------------------------------------------
    // EXECUTE FOLDING SEQUENCE
    // --------------------------------------------------------

    foldCloth();

    // --------------------------------------------------------
    // WAIT FOR USER TO REMOVE FOLDED GARMENT
    // --------------------------------------------------------

    waitForGarmentRemoval();

    // --------------------------------------------------------
    // RESET MECHANISM
    // --------------------------------------------------------

    resetServos();

    Serial.println();
    Serial.println("System ready for the next garment.");
    Serial.println("--------------------------------");
  }

  // Small delay before checking sensor again
  delay(SENSOR_DELAY);
}
