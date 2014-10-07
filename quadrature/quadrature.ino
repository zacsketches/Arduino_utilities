/* Increment a counter using quadrature encoding.
   
   See the link below for the best explanation of quadrature I've found 
   on the web. 
   http://letsmakerobots.com/node/24031
   
   I've adapted the code to be interupt driven.
   
   By Zac Staples, July 2014.
*/

//constants
const int A_pin = 53;
const int B_pin = 51;

volatile byte Enc_A = HIGH;
volatile byte Enc_B = HIGH;

volatile int out_val, old_val, new_val;

volatile long count = 0;

int QEM[16] = {0,-1,1,2,1,0,2,-1,-1,2,0,1,2,1,-1,0};  //see the link above for this

//volatiles updated by the interrupt service routine
volatile unsigned int count_A1 = 0;
volatile unsigned int count_A2 = 0;

void setup() {
  Serial.begin(115200);
  pinMode(A_pin, INPUT);
  pinMode(B_pin, INPUT);

  Enc_A = digitalRead(A_pin);
  Enc_B = digitalRead(B_pin);
  
  attachInterrupt(A_pin, set_A, CHANGE); 
  attachInterrupt(B_pin, set_B, CHANGE); 
  
}

void loop() {
  
  switch(out_val) {
    case 0:
      Serial.print("stop");
      break;
    case -1:
      Serial.print("back");
      break;
    case 1:
      Serial.print("frwd");
      break;
  }
  
  char buf[75];
  sprintf(buf, "\tout is:%d\told is:%d\tnew is:%d\tcount is:%d", out_val, old_val, new_val, count);
  Serial.println(buf);
  delay(100);
  
}

//ISR's
void set_A() {
  old_val = new_val;
  Enc_A = !Enc_A;
  new_val = Enc_A * 2 + Enc_B;
  out_val = QEM [old_val * 4 + new_val];
  switch(out_val){
    case 1:
      ++count;
      break;
    case -1:
      --count;
      break;
  }
}

void set_B() {
  old_val = new_val;
  Enc_B = !Enc_B;
  new_val = Enc_A * 2 + Enc_B;
  out_val = QEM [old_val * 4 + new_val];
  switch(out_val){
    case 1:
      ++count;
      break;
    case -1:
      --count;
      break;
  }
}

