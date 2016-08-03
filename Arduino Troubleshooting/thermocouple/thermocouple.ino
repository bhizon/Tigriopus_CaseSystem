//Thermocouple library for Max31855
#include "Adafruit_MAX31855.h"

//thermocouple
const int thermoDO = 7; //data out to D7
const int thermoCS = 6; //data out to D6
const int thermoCLK = 5; //data out to D5
Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);
  Serial.println("MAX6675 test");
  delay(500);
}

void loop() {
    // basic readout test, just print the current temp
  
   Serial.print("C = "); 
   Serial.print(thermocouple.readCelsius());
   Serial.print("\t F = ");
   Serial.println(thermocouple.readFahrenheit());
 
   delay(1000);
}
