// For testing, we manually changed the temperature and the humidity surrounding the sensor to test
// and see if the readings would change and compared the readings to credible online weather data.

#include <dht.h> // You need to download the libary and connect it
// link to libary: https://www.arduinolibraries.info/libraries/dh-tlib

dht DHT;

#define DHT11_PIN 2

void setup(){
  Serial.begin(9600);
}

void loop(){
  int chk = DHT.read11(DHT11_PIN);
  float t = DHT.temperature;        // Read temperature
	float h = DHT.humidity;           // Read humidity

	Serial.print("Temperature = ");
	Serial.print(t);
	Serial.print("°C | ");
	Serial.print((t*9.0)/5.0+32.0);        // Convert celsius to fahrenheit
	Serial.println("°F ");
	Serial.print("Humidity = ");
	Serial.print(h);
	Serial.println("% ");
	Serial.println("");

	delay(2000); // wait two seconds
}