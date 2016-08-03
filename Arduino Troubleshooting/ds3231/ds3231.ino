/*
 * From example Arduino code. 
 * Modified by F. King July 14, 2014
 * 
 * To test RTC, runs RTC and prints time to Serial monitor every 3 sec 
 * along with day of the week and 2 modifications of the time.
 * 
 * Wiring:
 * RTC should be powered with +5 V, be connected with CMN GND and
 * SCL pin to A5 and SDA pin to A4.
 */

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {

#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  Serial.begin(9600);
  Serial.println("Beginning set-up... ");

  DateTime compileTime = DateTime(F(__DATE__), F(__TIME__));
  rtc.adjust(compileTime); //remove once battery added
  Serial.println("");
  Serial.print("setting RTC to compile time:\t");
  printTimeToSerial(compileTime);
  Serial.println("");
  
  rtc.adjust(compileTime);
  
  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
    DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");
    
    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (now + TimeSpan(7,12,30,6));
    
    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    
    Serial.println();
    delay(3000);
}

/*
 * Prints current time to Serial.
 * 
 * @parameters Pass current DateTime object to be printed to SD.
*/
static void printTimeToSerial (DateTime curr) {
  Serial.print(curr.year(), DEC);
  Serial.print('/');
  Serial.print(curr.month(), DEC);
  Serial.print('/');
  Serial.print(curr.day(), DEC);
  Serial.print('\t');
  Serial.print(curr.hour(), DEC);
  Serial.print(':');
  Serial.print(curr.minute(), DEC);
  Serial.print(':');
  Serial.print(curr.second(), DEC);
}
