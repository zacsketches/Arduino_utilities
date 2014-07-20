
void setup() {
  Serial.begin(57600);
  Serial.print(memory_free());
}

void loop() {
 
  delay(10);  
}

//variables creaed by the build process when compiling the sketch
extern int __bss_end;
extern void* __brkval;

int memory_free() {
  int free_value;
  if( (int)__brkval == 0) {
    free_value = ( (int)&free_value) - ((int)&__bss_end);
  } else {
    free_value = ((int)&free_value) - ((int)&__brkval);
  } 
  return free_value;
}
