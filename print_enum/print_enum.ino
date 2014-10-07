namespace Direction {
    enum dir {fwd, back};
    
    inline const char* text(dir d) {
      const char* res[5] = {(d == fwd) ? "frwd" : "back"};
      return res[0];
    }
}

void setup() {
  Serial.begin(57600);
  Serial.println();
  Direction::dir d = Direction::fwd;
  Serial.println(Direction::text(d));
  d = Direction::back;
  Serial.println(Direction::text(d));
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
