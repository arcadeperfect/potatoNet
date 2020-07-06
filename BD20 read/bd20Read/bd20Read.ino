int pin1 = 6;
int pin2 = A1;
int pin3 = A2;
int pin4 = A3;
int pin5 = A4;
int pin6 = A5;


void setup() {
  // put your setup code here, to run once:
  //  pinMode(pin1, INPUT);
  pinMode(13, OUTPUT);
  pinMode(6, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {

  digitalWrite(13, digitalRead(pin1));

  if (!digitalRead(pin1)) {
    Serial.println("1");
  }


  if (!digitalRead(pin2)) {
    Serial.println("2");
  }

  if (!digitalRead(pin3)) {
    Serial.println("3");
  }

  if (!digitalRead(pin4)) {
    Serial.println("4");
  }

  if (!digitalRead(pin5)) {
    Serial.println("5");
  }

  if (!digitalRead(pin6)) {
    Serial.println("6");
  }



}
