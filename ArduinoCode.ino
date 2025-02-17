// Sensor Pins
#define tempSensorPin  A0 // TMP36 on A0
#define waterSensorPin A1 // Water level sensor on A1
#define ldrPin         A2 // Photoresistor (LDR) on A2
#define sensorPower    7  // Water level sensor power
#define ledPin         9  // LED controlled by LDR
#define ldrThreshold   120 // Light threshold (adjust as needed)

void setup() {
  Serial.begin(9600); // Start Serial communication
  
  // Set up water level sensor power
  pinMode(sensorPower, OUTPUT); 
  digitalWrite(sensorPower, LOW); // Start with sensor OFF

  // Set LED as OUTPUT
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read TMP36 temperature
  float tempReading = analogRead(tempSensorPin);
  float tempVoltage = tempReading * (3.3 / 1023.0); // Convert to voltage (3.3V ref)
  float temperatureC = (tempVoltage - 0.5) * 100.0; // Convert to Celsius
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0; // Convert to Fahrenheit

  // Print temperature in "F, C" format
  Serial.print("Temperature (F, C): ");
  Serial.print(temperatureF, 2);
  Serial.print(", ");
  Serial.println(temperatureC, 2);

  // Read water level sensor
  int waterLevel = readWaterSensor();

  // Print water level
  Serial.print("Water Level: ");
  Serial.println(waterLevel);

  // Read LDR (photoresistor) value
  int lightLevel = analogRead(ldrPin);

  // Print light level
  Serial.print("Light Level: ");
  Serial.println(lightLevel);

  // Control LED based on light threshold
  if (lightLevel < 130) {
    digitalWrite(ledPin, HIGH); // Turn LED ON (dark environment)
  } else {
    digitalWrite(ledPin, LOW);  // Turn LED OFF (bright environment)
  }

  delay(1000); // Wait 1 second before next reading
}

// Function to read water level sensor
int readWaterSensor() {
  digitalWrite(sensorPower, HIGH); // Turn the sensor ON
  delay(10); // Wait 10 milliseconds for stable reading
  int val = analogRead(waterSensorPin); // Read analog value from sensor
  digitalWrite(sensorPower, LOW); // Turn the sensor OFF
  return val; // Return current reading
}
