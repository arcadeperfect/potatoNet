/*
  Potatonet node 2
*/

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <TurnoutPulser.h>

int dly = 5;

int tPin1 = A1;
int tPin2 = A2;
TurnoutPulser turnout1(tPin2, tPin1);

int tPin3 = A3;
int tPin4 = A4;
TurnoutPulser turnout2(tPin3, tPin4);

int input_01 = 2;
int input_02 = 3;
int input_03 = 4;
int input_04 = 5;

//int output_01 = 2;
//int output_02 = 3;
//int output_03 = 2;
//int output_04 = 3;


struct Inputs {
  int input_01;
  int input_02;
  int input_03;
  int input_04;

};

struct Outputs {
  int output_01;
  int output_02;
  int output_03;
  int output_04;

};

Inputs this_inputs;
Outputs this_outputs;


RF24 radio(10, 9);                  // nRF24L01 (CE,CSN)
RF24Network network(radio);         // Include the radio in the network
const uint16_t this_node = 02;      // Address of this node in Octal format ( 04,031, etc)
const uint16_t base_node = 00;      // Address of the other node in Octal format


void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  turnout1.begin();
  turnout2.begin();

  radio.setDataRate(RF24_2MBPS);

  pinMode(input_01, INPUT_PULLUP);
  pinMode(input_02, INPUT_PULLUP);
  pinMode(input_03, INPUT_PULLUP);
  pinMode(input_04, INPUT_PULLUP);
  pinMode(tPin1, OUTPUT);
  pinMode(tPin2, OUTPUT);
  pinMode(tPin3, OUTPUT);
  pinMode(tPin4, OUTPUT);


}

void loop() {
  turnout1.loop();
  turnout2.loop();
  network.update();

  //===== Receiving =====//

  while ( network.available() ) {                       // Is there any incoming data?
    RF24NetworkHeader header;
    Outputs incoming;
    network.read(header, &incoming, sizeof(incoming));  // Read the incoming data
    this_outputs = incoming;                            // store incoming data 

  }

  //===== Sending =====//

  this_inputs.input_01 = !digitalRead(input_01);
  this_inputs.input_02 = !digitalRead(input_02);
  this_inputs.input_03 = !digitalRead(input_03);
  this_inputs.input_04 = !digitalRead(input_04);

  RF24NetworkHeader header2(base_node);                 // (Address where the data is going)
  bool ok = network.write(header2, &this_inputs, sizeof(this_inputs));      // Send the data

  //====== Networksley over =====//

  turnout1.set(this_outputs.output_01);
  turnout2.set(this_outputs.output_02);

  delay(dly);
}
