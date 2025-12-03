// For testing, we manually changed the temperature and the humidity surrounding the sensor to test
// and see if the readings would change and compared the readings to credible online weather data.

#include <dht.h> // You need to download the libary and connect it
// link to libary: https://www.arduinolibraries.info/libraries/dh-tlib
#include <TM1637Display.h>

dht DHT;

#define DHT11_PIN 2
#define sensor A0 
#define button 8

#define CLK1 3  
#define DIO1 4 
#define CLK2 5  
#define DIO2 6   

TM1637Display display1(CLK1, DIO1);  // For temperature
TM1637Display display2(CLK2, DIO2);  // For humidity

const uint8_t LETTER_F = SEG_A | SEG_F | SEG_E | SEG_G;    
const uint8_t LETTER_H = SEG_F | SEG_E | SEG_B | SEG_C | SEG_G;
int airQ = 0;

void setup(){
  Serial.begin(9600);
	display1.setBrightness(0x0f); 
	display2.setBrightness(0x0f);
}

void loop(){
  int chk = DHT.read11(DHT11_PIN);
  float temp = ((DHT.temperature * 9.0)/5.0 + 32.0);        // Read temperature
	float hum = DHT.humidity;           // Read humidity
	airQ = analogRead(sensor); 				// Read Air Quality

	if (isnan(temp) || isnan(hum)) {
    // Error handling
    display1.showNumberDecEx(0, 0, true);
    display2.showNumberDecEx(0, 0, true);
    delay(2000);
    return;
  }

  int t = (int)temp;
  uint8_t tempData[] = {
    display1.encodeDigit((t / 10) % 10), 
    display1.encodeDigit(t % 10),        
    0x00,                                
    LETTER_F                            
  };
  display1.setSegments(tempData);

  int h = (int)hum;
  uint8_t humData[] = {
    display2.encodeDigit((h / 10) % 10), 
    display2.encodeDigit(h % 10),        
    0x00,                               
    LETTER_H                             
  };
  display2.setSegments(humData);
	Serial.println("Air Quality = ");
	Serial.println(airQ);

	delay(1000); // wait two seconds
}
