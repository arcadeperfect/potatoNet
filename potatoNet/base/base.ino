/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
          == Base/ Master Node 00==
  by Dejan, www.HowToMechatronics.com
  Libraries:
  nRF24/RF24, https://github.com/nRF24/RF24
  nRF24/RF24Network, https://github.com/nRF24/RF24Network
*/

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <CMRI.h>

#define led 2


int input_01 = 5;
int input_02 = 6;
int output_01 = 2;
int output_02 = 3;

CMRI cmri; // defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs


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


RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node1 = 01;      // Address of the other node in Octal format


struct node_variables {
  struct Inputs inputs;
  struct Outputs outputs;
  int address;
} ;

node_variables node_01 = {
  {0, 0, 0, 0}, // inputs
  {0, 0, 0, 0}, // outputs
  01,     // address
};

node_variables node_02 = {
  {0, 0, 0, 0}, // inputs
  {0, 0, 0, 0}, // outputs
  0,     // address
};








void setup() {
  Serial.begin(9600, SERIAL_8N2); // make sure this matches your speed set in JMRI
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  pinMode(input_01, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(7, INPUT_PULLUP);


  node_01.address = 1;

}

void loop() {

  //  network.update();
  cmri.process();


  //===== data to / from CMRI =====//
  //
  node_01.outputs.output_01 = cmri.get_bit(0);
  //node_01.outputs.output_01 = digitalRead(7);
  node_01.outputs.output_02 = cmri.get_bit(1);

  Serial.println(node_01.outputs.output_01);
  //  digitalWrite(led, node_01.outputs.output_02);

  cmri.set_bit(5, node_01.inputs.input_01);
  cmri.set_bit(6, node_01.inputs.input_02);



  //===== Receiving =====//


  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;

    Inputs incoming;
    network.read(header, &incoming, sizeof(incoming)); // Read the incoming data

    //    == == = Node 1 == == == == //
    if (header.from_node == node_01.address) {

      //      node_01.inputs.input_01 = incoming.input_01;
      //      node_01.inputs.input_02 = incoming.input_02;
      node_01.inputs = incoming;
      //digitalWrite(led, node_01.inputs.input_01);

    }
  }

  //===== Sending =====//

  Outputs outgoing;
  //    outgoing.output_01 = !digitalRead(7);
  outgoing = node_01.outputs;
  Serial.println(outgoing.output_01);


  RF24NetworkHeader header2(node1);     // (Address where the data is going)

  bool ok = network.write(header2, &outgoing, sizeof(outgoing)); // Send the data
  if (ok) {
    Serial.println("ok");
  } else {
    Serial.println("not ok");
  }

  //digitalWrite(led, node_01.inputs.input_01);
  Serial.println("buttt");
  delay(5);

}
