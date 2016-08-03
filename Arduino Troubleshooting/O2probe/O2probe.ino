#include <Wire.h>
#include <SoftwareSerial.h>

int model;
int serialNum;

SoftwareSerial doProbe(9,8); // RX, TX lines, Dissolved Oxygen probe
  // RX line of DO probe is striped brown, TX line for Arduino, D9 R1OUT on breakout board
  // TX line of DO probe is solid brown, RX line for Arduino, D8 R1IN on breakout board

void setup() {
  Serial.begin(19200); //communicates with computer via Serial port
  doProbe.begin(9600); //communicates with DO probe

  Serial.println("Commencing set-up...");

  WaitforSerialChar('M');
  model = doProbe.parseInt();
  serialNum = doProbe.parseInt();
  Serial.print("model: ");
  Serial.println(model);
  Serial.print("SerialNum: ");
  Serial.println(serialNum);

}

void loop() {
  WaitforSerialChar('M');
  double doMeas = getDOmgL(); //get DO measurement in mg/L
  printDOmgLToSerial(doMeas);
}

///// FUNCTIONS /////
/*
 * Prints DO to Serial in units of mg/L.
 * 
 * @parameters Pass DO in mg/L as double to be printed.
*/
static void printDOmgLToSerial (double measure) {
  Serial.print("\t DO (mg/L) = ");
  Serial.println(measure);
}

/*
 * Parse RS232 data from O2 probe to get DO in uMol from the Serial stream.
 * 
 * @parameters N/A
 * @return Returns value of DO reading in uMol.
 */
double getDOuMol(){
  WaitforSerialChar('M');
  doProbe.parseInt();
  doProbe.parseInt();
  float DOuMolMeas = doProbe.parseFloat();
}
/*
 * Calls getDOuMol and converts value of O2 from uMol to return value in mg/L.
 * 
 * @parameters N/A
 * @return Returns value of DO reading in mg/L
 */
double getDOmgL(){
  float DOuMolMeas = getDOuMol();
  float DOmgLMeas = DOuMolMeas*0.031998;  //convert uMol to mg/L
  return DOmgLMeas;
}

/*
 * Haults execution until the DO probe serial passes an 'M' at the beginning of MEASUREMENT,
 * which begins the next reading. Can pass any character as parameter start, does not need
 * to be 'M'
 * 
 * @parameters char start = the character to wait for
 */
void WaitforSerialChar(char start){
  char currChar = doProbe.read();
  while (currChar != (start)){
    currChar = doProbe.read();
  }
}
