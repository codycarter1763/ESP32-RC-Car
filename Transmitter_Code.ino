#include <BluetoothSerial.h>

// Bluetooth server setup
BluetoothSerial SerialBT;

// Joystick pin definitions
#define THROTTLE_PIN 34  // Throttle (Y-axis)
#define STEERING_PIN 36  // Steering (X-axis)
#define STATUSLEDPIN 33  // BT connection status LED
#define LJOYSTICKBUTTON 26 // Pin for L Joystick switch

int buttonOld = 1;
int buttonNew;
int headlightState = 0;

// Slave MAC address
uint8_t address[6] = {0xC0, 0x5D, 0x89, 0xB0, 0x45, 0xD2}; // MAC address of RC car for BT connection

void setup() {
  Serial.begin(115200);

  // Initialize Bluetooth Serial
  if (!SerialBT.begin("ESP32_Transmitter")) {
    Serial.println("Bluetooth initialization failed!");
    while (1);
  }

  pinMode(THROTTLE_PIN, INPUT);
  pinMode(STEERING_PIN, INPUT);
  pinMode(STATUSLEDPIN, OUTPUT);
  pinMode(LJOYSTICKBUTTON, INPUT_PULLUP);

  // Attempt to connect to RC car
  Serial.println("Attempting to connect to RC car...");
  bool connected = SerialBT.connect(address);

  if (connected) {
    Serial.println("Connected successfully to RC car!");
    digitalWrite(STATUSLEDPIN, HIGH); // Turn on LED when connected
  } else {
    Serial.println("Failed to connect to RC car. Entering blinking mode...");
  }
}
void loop() {
  if (!SerialBT.connected()) {
    // Blink LED if not connected
    digitalWrite(STATUSLEDPIN, HIGH);
    delay(500);
    digitalWrite(STATUSLEDPIN, LOW);
    delay(500);
  } else {
    buttonNew = digitalRead(LJOYSTICKBUTTON);

    // Detect a rising edge (button released when using INPUT_PULLUP)
    if (buttonOld == 1 && buttonNew == 0) {
      // Toggle the LED state
      if (headlightState == 0) {
        headlightState = 1; // On
        Serial.println("Headlights On");
      } else {
        headlightState = 0; // Off
        Serial.println("Headlights Off");
      }
    }
    buttonOld = buttonNew; // Save current state for next iteration

    // Read joystick values
    int throttleRaw = analogRead(THROTTLE_PIN) >> 4; // Map to 0-255
    int steeringRaw = analogRead(STEERING_PIN) >> 4; // Raw steering value
    
    int steeringValue = map(steeringRaw, 0, 255, 127, -128); // Map to 127 to -128 for reversing
    int throttleValue = map(throttleRaw, 0, 255 , 127, -128); // Map to 255 to 0 for reversing

    // Prepare data for sending
    uint8_t send_data[6];
    send_data[0] = 'T';                // Start byte
    send_data[1] = (uint8_t)throttleValue + 128;      // Throttle value
    send_data[2] = (uint8_t)steeringValue + 128; // Adjust to send as unsigned
    send_data[3] = headlightState;     // Headlight value
    send_data[4] = 0;                  // Reserved for future use
    send_data[5] = send_data[1] + send_data[2] + send_data[3]; // Checksum

    SerialBT.write(send_data, 6); // Send data to RC car
    Serial.printf("Sent: Throttle=%d, Steering=%d, HeadlightState=%d\n", throttleValue, steeringValue, headlightState);

    delay(50); // Adjust delay for smoother communication
  }
}
