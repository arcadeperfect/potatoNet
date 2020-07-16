/*
  Potatonet node 3
*/

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
//#include <TurnoutPulser.h>

int dly = 5;

//#define led 2

//int tPin1 = 3;
//int tPin2 = 4;
//TurnoutPulser turnout(tPin2, tPin1);

int input_01 = 6;
int input_02 = 7;
//int input_03 = 7;
//int input_04 = 8;

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


RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 03;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t base_node = 00;      // Address of the other node in Octal format
//const uint16_t node012 = 012;
//const uint16_t node022 = 022;


int rando = 0;


void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  pinMode(input_01, INPUT_PULLUP);
  //pinMode(output_01, OUTPUT);
  //  turnout.begin();

}

void loop() {
  //  turnout.loop();
  network.update();

  //===== Receiving =====//
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    Outputs incoming;
    network.read(header, &incoming, sizeof(incoming)); // Read the incoming data
    this_outputs = incoming;
    //Serial.println(incoming);

    //    digitalWrite(led, this_outputs.output_01);

  }
  //===== Sending =====//

  this_inputs.input_01 = !digitalRead(input_01);
  this_inputs.input_02 = !digitalRead(input_02);
  Serial.print(this_inputs.input_01);
  Serial.println(this_inputs.input_02);

  RF24NetworkHeader header2(00);     // (Address where the data is going)
  bool ok = network.write(header2, &this_inputs, sizeof(this_inputs)); // Send the data
  if (ok) {
    Serial.println("sent ok");

  } else {
    Serial.println("not sent");
  }

  //====== Netorksley over =====//

  //  turnout.set(this_outputs.output_01);

  delay(dly);
}
