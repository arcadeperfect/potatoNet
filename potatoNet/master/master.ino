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

#define button 5
#define led 2

RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t that_node = 01;      // Address of the other node in Octal format
//const uint16_t node012 = 012;
//const uint16_t node022 = 022;

void setup() {
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  network.update();



  //===== Receiving =====//
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    //unsigned long incomingData;
    int buttonIn;
    network.read(header, &buttonIn, sizeof(buttonIn)); // Read the incoming data
    digitalWrite(led, buttonIn);
  }
  //===== Sending =====//

  int buttonOut = !digitalRead(button);
  RF24NetworkHeader header2(that_node);     // (Address where the data is going)
  bool ok = network.write(header2, &buttonOut, sizeof(buttonOut)); // Send the data

  //  digitalWrite(led, buttonIn || buttonOut);
  delay(5);
}
