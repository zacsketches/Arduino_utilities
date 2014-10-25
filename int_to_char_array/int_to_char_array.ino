//Test char manipulation to get a consistent three character
//null-terminated char*

int mtr_cmd[2] = {-80, 85};

void setup() {
  Serial.begin(9600);
  Serial.println();  
}

void loop() {
  int lt_val = mtr_cmd[0];
  int rt_val = mtr_cmd[1];
  lt_val = map(lt_val, -90, 90, 0, 180);
  rt_val = map(rt_val, -90, 90, 0, 180);
  
  char buf [4];
  sprintf (buf, "%03i", rt_val);

  Serial.print("rt_str is: ");
  Serial.print(buf);
  Serial.println();
  
  int converted_buf = atoi(buf);
  
  Serial.print("rt_int is: ");
  Serial.print(converted_buf);
  Serial.println();
  
  while(1);
}
  
  
