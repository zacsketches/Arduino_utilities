//This sketch is loaded on the arduino receiving the
//esplora's software serial output
//listen for serial data incoming and echo to the serial monitor

//connect esplora's tx line to D0 of RCVR arduino

char in;

void setup() {
  Serial.begin(9600);
}
void loop() {
  if(Serial.available()>0) {
    in = Serial.read();
    Serial.print(in);
  }
}
