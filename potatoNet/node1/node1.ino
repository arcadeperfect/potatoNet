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
#include <TurnoutPulser.h>

//#define input_1 5
//#define input_2 6
//#define output1 2
//#define output2 3
#define led 2

int tPin1 = 3;
int tPin2 = 4;
TurnoutPulser turnout(tPin2, tPin1);

int input_01 = 5;
int input_02 = 6;
//int output_01 = 2;
int output_02 = 3;


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
const uint16_t this_node = 01;   // Address of this node in Octal format ( 04,031, etc)
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
  turnout.begin();

}

void loop() {
  turnout.loop();
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
  
    RF24NetworkHeader header2(base_node);     // (Address where the data is going)
    bool ok = network.write(header2, &this_inputs, sizeof(this_inputs)); // Send the data

  //====== Netorksley over =====//
  Serial.println(this_outputs.output_01);
  turnout.set(this_outputs.output_01);
  Serial.println(this_outputs.output_01);
  delay(5);
}
