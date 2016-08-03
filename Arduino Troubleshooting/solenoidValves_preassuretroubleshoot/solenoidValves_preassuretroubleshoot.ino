/*  Global Variables  */
const int O2valve = 4;
const int N2valve = 3;
const int CO2valve = 2;


void setup() {
  Serial.begin(4800);

}

void loop() {
  delay(1500); //delay off to keep sensors off for 3 sec

  digitalWrite(O2valve, HIGH); //open solenoid valve  
  Serial.print("\t");
  Serial.print("O2 ON");
  delay(5000); //delay to stay on for 2 sec
  digitalWrite(O2valve, LOW); //close solenoid valve 
  delay(50);
  
  digitalWrite(N2valve, HIGH); //open solenoid valve  
  Serial.print("\t");
  Serial.print("N2 ON");
  delay(5000); //delay to stay on for 2 sec
  digitalWrite(N2valve, LOW); //close solenoid valve
  delay(50);
  digitalWrite(CO2valve, HIGH); //open solenoid valve  
  Serial.print("\t");
  Serial.print("CO2 ON");
  delay(5000); //delay to stay on for 2 sec
  digitalWrite(CO2valve, LOW); //close solenoid valve 
  delay(50);
  Serial.println(""); //start new print out line
}
