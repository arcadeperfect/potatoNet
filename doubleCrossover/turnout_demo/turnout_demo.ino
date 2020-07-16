#include <TurnoutPulser.h>

int tPin1 = 3;
int tPin2 = 4;
TurnoutPulser turnout(tPin2, tPin1); 

void setup() {
  // put your setup code here, to run once:
  turnout.begin();
  pinMode(7, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  turnout.loop(); // call this every time in loop()
  int readState = digitalRead(7);
  Serial.println(readState);
  turnout.set(readState);
  delay(5);
}
