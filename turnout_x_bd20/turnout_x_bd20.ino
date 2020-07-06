#include <CMRI.h>
#include <TurnoutPulser.h>

int turnout_pin1 = 9;
int turnout_pin2 = 10;
int pulseLength = 50;

int pin1 = 7;
int pin2 = 6;
int pin3 = 5;
int pin4 = 4;
int pin5 = 3;
int pin6 = 2;

int state = 0;

TurnoutPulser turnout(turnout_pin1, turnout_pin2); // L9110S is connected to pins 2 and 3

CMRI cmri; // defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs

void setup() {
  turnout.begin();
  Serial.begin(9600, SERIAL_8N2); // make sure this matches your speed set in JMRI

  pinMode(13, OUTPUT);

  pinMode(turnout_pin1, OUTPUT);
  pinMode(turnout_pin2, OUTPUT);

  digitalWrite(turnout_pin1, LOW);
  digitalWrite(turnout_pin2, LOW);

  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  pinMode(pin3, INPUT_PULLUP);
  pinMode(pin4, INPUT_PULLUP);
  pinMode(pin5, INPUT_PULLUP);
  pinMode(pin6, INPUT_PULLUP);

  pinMode(13, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  turnout.loop(); // call this every time in loop()

  cmri.process();

  turnout.set(cmri.get_bit(1));

  int r1 = !digitalRead(pin1);
  int r2 = !digitalRead(pin2);
  int r3 = !digitalRead(pin3);
  int r4 = !digitalRead(pin4);
  int r5 = !digitalRead(pin5);
  int r6 = !digitalRead(pin6);

  cmri.set_bit(5, r1);
  cmri.set_bit(6, r2);
  cmri.set_bit(7, r3);
  cmri.set_bit(8, r4);
  cmri.set_bit(9, r5);
  cmri.set_bit(10, r6);


}
