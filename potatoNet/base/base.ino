/*
  Potatonet base node
*/

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <CMRI.h>

#define led 2

int dly = 1;

//
//int input_01 =  5;
//int input_02 =  6;
int output_01 = 2;
int output_02 = 3;

CMRI cmri(1, 24, 48); // defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs


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
  02,     // address
};

node_variables node_03 = {
  {0, 0, 0, 0}, // inputs
  {0, 0, 0, 0}, // outputs
  03,     // address
};







void setup() {
  Serial.begin(9600, SERIAL_8N2); // make sure this matches your speed set in JMRI
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  //pinMode(input_01, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  //pinMode(7, INPUT_PULLUP);

  Serial.println("init base");

  node_01.address = 01;

}

void loop() {

  //  network.update();
  cmri.process();


  //===== data from CMRI =====//

  node_01.outputs.output_01 = cmri.get_bit(0);
  node_01.outputs.output_02 = cmri.get_bit(1);

  node_02.outputs.output_01 = cmri.get_bit(2);
  node_02.outputs.output_02 = cmri.get_bit(3);

  node_03.outputs.output_01 = cmri.get_bit(4);
  node_03.outputs.output_02 = cmri.get_bit(5);


  cmri.set_bit( 1, node_01.inputs.input_01);
  cmri.set_bit( 2, node_01.inputs.input_02);

  cmri.set_bit( 3, node_02.inputs.input_01);
  cmri.set_bit( 4, node_02.inputs.input_02);
  cmri.set_bit( 5, node_02.inputs.input_03);
  cmri.set_bit( 6, node_02.inputs.input_04);

  cmri.set_bit( 7, node_03.inputs.input_01);
  cmri.set_bit( 8, node_03.inputs.input_02);




  //===== Receiving =====//


  while ( network.available() ) {     // Is there any incoming data?

    RF24NetworkHeader header;

    Inputs incoming;
    network.read(header, &incoming, sizeof(incoming)); // Read the incoming data

    //    == == = Node 1 == == == == //
    if (header.from_node == 01) {

      node_01.inputs = incoming;
      //      Serial.println("node 1");
      //      Serial.print(node_01.inputs.input_01);
      //      Serial.print("     ");
      //      Serial.println(node_01.inputs.input_02);
      //      Serial.println("");
      //      delay(dly);

    }

    if (header.from_node == node_02.address) {

      node_02.inputs = incoming;
      //      Serial.println("node 2");
      //      Serial.print(node_02.inputs.input_01);
      //      Serial.print("     ");
      //      Serial.print(node_02.inputs.input_02);
      //      Serial.print("     ");
      //      Serial.print(node_02.inputs.input_03);
      //      Serial.print("     ");
      //      Serial.println(node_02.inputs.input_04);
      //      Serial.println("");
      //      delay(dly);

    }

    if (header.from_node == node_03.address) {

      node_03.inputs = incoming;
      //      Serial.println("node 1");
      //      Serial.print(node_03.inputs.input_01);
      //      Serial.print("     ");
      //      Serial.println(node_03.inputs.input_02);
      //      Serial.println("");
      //      delay(dly);

    }

  }


  //===== Sending =====//

  //  Outputs outgoing;
  //  outgoing = node_01.outputs;
  //  Serial.println(outgoing.output_01);


  //  RF24NetworkHeader header2(node1);     // (Address where the data is going)
  //
  //  bool ok = network.write(header2, &outgoing, sizeof(outgoing)); // Send the data
  //  if (ok) {
  //    Serial.println("ok");
  //  } else {
  //    Serial.println("not ok");
  //  }


  //  delay(dly);

  for (int i = 0; i < 3; i++) {
    if (i == 0) {
      Outputs outgoing;
      outgoing = node_01.outputs;
      RF24NetworkHeader header2(node_01.address);
      bool ok = network.write(header2, &outgoing, sizeof(outgoing)); // Send the data
      //      delay(dly);
    }
    if (i == 1) {
      Outputs outgoing;
      outgoing = node_02.outputs;
      RF24NetworkHeader header2(node_02.address);
      bool ok = network.write(header2, &outgoing, sizeof(outgoing)); // Send the data
      //      delay(dly);
    }
    if (i == 2) {
      Outputs outgoing;
      outgoing = node_03.outputs;
      RF24NetworkHeader header2(node_03.address);
      bool ok = network.write(header2, &outgoing, sizeof(outgoing)); // Send the data
      //      delay(dly);
    }
  }


  //===== data to CMRI =====//

  delay(dly);

}
