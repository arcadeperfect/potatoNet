#include <CMRI.h>

// toggles the position of your turnout every 5 seconds

//#include <TurnoutPulser.h>

int pin1 = 9;
int pin2 = 10;
int dly = 5000;
int pulseLength = 50;

//TurnoutPulser turnout(9, 10); // L9110S is connected to pins 2 and 3

int interval = 10000;
int pulse = 0;

void setup() {
  //turnout.begin();

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);

  Serial.begin(9600);


  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);

}

void loop() {

  //
  //  turnout.loop(); // call this every time in loop()
  //  turnout.set(pulse);
  //  Serial.println(pulse);
  //  pulse = 1 - pulse;
  //  turnout.loop(); // call this every time in loop()
  //  delay(  2000);


  ////
  digitalWrite(pin1, HIGH);

  delay(pulseLength);

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  ////

  delay(dly);

  ////
  digitalWrite(pin2, HIGH);

  delay(pulseLength);

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  ////

  delay(dly);


}
