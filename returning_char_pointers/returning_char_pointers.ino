void alter(char* b) {
  char test[] = "This is the test string";
  strcpy(b, test);
}

void setup() {
  
  Serial.begin(57600);
  Serial.println();
  char buf[75];

  alter(buf);
  
  Serial.println(buf);

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
