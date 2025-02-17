// TMP36 Temperature Sensor
#define tempSensorPin  A0 // TMP36 on A0
#define waterSensorPin  A1 // Water level sensor on A1
#define sensorPower  7 // Water level sensor power

void setup() {
  Serial.begin(9600); // Start Serial communication
  pinMode(sensorPower, OUTPUT); // Set water sensor power pin as output
  digitalWrite(sensorPower, LOW); // Start with sensor OFF
}

void loop() {
  // Read TMP36 temperature
  float tempReading = analogRead(tempSensorPin);
  float tempVoltage = tempReading * (3.3 / 1023.0); // Corrected for 3.3V reference
  float temperatureC = (tempVoltage - 0.5) * 100.0; // Convert to Celsius
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0; // Convert to Fahrenheit

  // Print temperature in "F, C" format
  Serial.print(temperatureF, 2);
  Serial.print(", ");
  Serial.println(temperatureC, 2);

  // Read water level
  int waterLevel = readWaterSensor();

  // Print water level
  Serial.print("Water level: ");
  Serial.println(waterLevel);

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
