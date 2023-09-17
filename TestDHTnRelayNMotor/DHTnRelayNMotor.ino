#include <DHT.h>

#define DHTPIN D2  // Plug the signal pin of DHT11 to D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int relayPin = D7;  // Define the pin number for the relay
bool relayActive = false; // Flag to track relay state

void setup() {
  Serial.begin(9600);   // For showing the result in the serial monitor at 9600 baud
  dht.begin();
  pinMode(relayPin, OUTPUT);  // Set the relay pin as an output
}

void loop() {
  // Read temperature and humidity from DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // For error checking
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.print("°C, ");
    Serial.print("Humidity = ");  
    Serial.print(humidity);
    Serial.println("%");

    // Check if humidity is greater than 70%
    if (humidity > 80.0) {
      if (!relayActive) {
        digitalWrite(relayPin, HIGH); // Turn on the relay (connects the circuit)
        relayActive = true;
      }
    } else {
      if (relayActive) {
        digitalWrite(relayPin, LOW); // Turn off the relay (disconnects the circuit)
        relayActive = false;
      }
    }
  }

  delay(3000); // Wait for 5 seconds before checking again
}
