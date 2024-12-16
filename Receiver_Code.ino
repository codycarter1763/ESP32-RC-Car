//Reciever Code

#include <BluetoothSerial.h>
#include <ESP32Servo.h>

// Bluetooth server setup
BluetoothSerial SerialBT;

// Servo object for steering and ESC
Servo myservo;
Servo brushlessMotor;

// Pin definitions for motor, servo, and LEDs
#define MOTOR_PWM_PIN 18      // PWM pin for controlling Brushless Motor (ESC)
#define SERVO_PIN 33          // PWM pin for controlling Servo
#define STATUSLEDPIN 2       // Pin for BT status LED
#define HEADLIGHTPIN 13       // Pin for headlights

// Motor control and servo control settings
#define PWM_FREQ 50           // PWM frequency for the motor (ESC)
#define MOTOR_LOW_SPEED 1000  // Minimum speed (full reverse in microseconds)
#define MOTOR_NEUTRAL 1000    // Neutral speed (no movement)
#define MOTOR_HIGH_SPEED 2000 // Maximum speed (full forward in microseconds)

// Speed adjustment constants
const float FORWARD_SPEED_FACTOR = 0.3; // Scale forward speed (0.0 to 1.0)
const float REVERSE_SPEED_FACTOR = 0.5; // Scale reverse speed (0.0 to 1.0)

// Safety timeout variables
#define TIMEOUT_PERIOD 2000   // Timeout period in milliseconds (2 seconds)
unsigned long lastDataTime = 0; // Timestamp of the last valid data

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_RC_Car"); // Initialize Bluetooth with a device name
  Serial.println("Bluetooth started. Waiting for connection...");

  
  pinMode(STATUSLEDPIN, OUTPUT);
  pinMode(HEADLIGHTPIN, OUTPUT);

  // Allocate PWM timers for ESP32
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Initialize brushless motor (ESC)
  brushlessMotor.setPeriodHertz(PWM_FREQ); // Set standard ESC PWM frequency (50 Hz)
  brushlessMotor.attach(MOTOR_PWM_PIN, MOTOR_LOW_SPEED, MOTOR_HIGH_SPEED);

  // Initialize servo for steering
  myservo.setPeriodHertz(PWM_FREQ); // Set standard servo PWM frequency (50 Hz)
  myservo.attach(SERVO_PIN, 600, 2000); // Min and max pulse width for servo

  // ESC Calibration Routine
  Serial.println("Calibrating ESC...");
  
  // Step 1: Send Maximum PWM (Full Forward Throttle)
  Serial.println("Sending full forward throttle...");
  brushlessMotor.writeMicroseconds(MOTOR_HIGH_SPEED);
  delay(2000); // Wait for ESC to register maximum throttle

  // Step 2: Send Minimum PWM (Full Reverse Throttle)
  Serial.println("Sending full reverse throttle...");
  brushlessMotor.writeMicroseconds(MOTOR_LOW_SPEED);
  delay(2000); // Wait for ESC to register minimum throttle

  // Step 3: Send Neutral PWM (No Movement)
  Serial.println("Sending neutral throttle...");
  brushlessMotor.writeMicroseconds(MOTOR_NEUTRAL);
  delay(2000); // Wait for ESC to register neutral position

  Serial.println("ESC Calibration Complete!");
}

void loop() {
  if (SerialBT.hasClient()) {
    Serial.println("Client connected!");
    digitalWrite(STATUSLEDPIN, HIGH); // LED on for successful connection
  } else {
    Serial.println("Waiting for client...");

    // Blink LED for no connection
    digitalWrite(STATUSLEDPIN, HIGH);
    delay(500);
    digitalWrite(STATUSLEDPIN, LOW);
    delay(500);

    // Stop the motor for safety if no client is connected
    brushlessMotor.writeMicroseconds(MOTOR_NEUTRAL);
    myservo.write(90); // Center the steering
    digitalWrite(HEADLIGHTPIN, LOW); // Turn off headlights
    return; // Skip the rest of the loop until a client connects
  }

  // Receives data array from controller
  if (SerialBT.available()) {
    uint8_t recv_data[6];
    SerialBT.readBytes(recv_data, 6);

    // Verify start byte
    if (recv_data[0] != 'T') {
      Serial.println("Invalid data received!");
      return;
    }

    // Calculate checksum
    uint8_t checksum = 0;
    for (int i = 1; i <= 4; i++) {
      checksum += recv_data[i];
    }

    // Check if checksum from controller is valid
    if (recv_data[5] != checksum) {
      Serial.println("Checksum error!");
      return;
    }

    // Update the last valid data timestamp
    lastDataTime = millis();

    // Parse data
    int throttleValue = recv_data[1];
    int steeringValue = recv_data[2];
    int headlightState = recv_data[3];

    // Control headlights
    if (headlightState == 1) {
      digitalWrite(HEADLIGHTPIN, HIGH);
      Serial.println("Headlights On");
    } else {
      digitalWrite(HEADLIGHTPIN, LOW);
      Serial.println("Headlights Off");
    }

    Serial.printf("Throttle: %d | Steering: %d\n", throttleValue, steeringValue);

    // Map throttle value to motor speed (reversed)
    int motorSpeed;
     if (throttleValue < 127) {
      // Reverse motion
      motorSpeed = map(throttleValue, 0, 127, MOTOR_LOW_SPEED, MOTOR_NEUTRAL);
      motorSpeed = MOTOR_NEUTRAL - (MOTOR_NEUTRAL - motorSpeed) * REVERSE_SPEED_FACTOR;
    } else if (throttleValue > 127) {
      // Forward motion
      motorSpeed = map(throttleValue, 127, 255, MOTOR_NEUTRAL, MOTOR_HIGH_SPEED);
      motorSpeed = MOTOR_NEUTRAL + (motorSpeed - MOTOR_NEUTRAL) * FORWARD_SPEED_FACTOR;
    } else {
      // Dead zone (neutral)
      motorSpeed = MOTOR_NEUTRAL;
    }

    // Send the calculated PWM motor speed to the ESC
    brushlessMotor.writeMicroseconds(motorSpeed);

    // Map steering value to servo angle (reversed steering)
    int steeringAngle = map(steeringValue, 0, 255, 180, 0);
    myservo.write(steeringAngle);
  }

  // Safety check: Stop the motor if no valid data received in the timeout period
  if (millis() - lastDataTime > TIMEOUT_PERIOD) {
    Serial.println("Connection lost! Stopping motor and centering steering.");
    brushlessMotor.writeMicroseconds(MOTOR_NEUTRAL); // Stop the motor
    myservo.write(90); // Center the steering
    digitalWrite(HEADLIGHTPIN, LOW); // Turn off headlights
  }
}