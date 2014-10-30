/* Written by Zac Staples, zacstaples@mac.com
 * Designed to work with a simple encoder kit based on hall effect
 * sensor attached to digital pin 2.  A DC motor signal is controlled
 * on pin 5.  
 * 
 * This sketch will compute the velocity of the motor in counts per
 * second and revolutions per second if counts_per_rev is initialized
 * in the top of the script.
 *
 */
#include <Serial.h>

const int counts_per_rev = 8;  //this will depend on the specs for your encoder

const int motor = 5;
bool on = false;
bool test_running = false;
unsigned long t_0=0;      //start time
unsigned long t_f=0;      //final time
volatile unsigned long count=0;
char ch;

void add_count() {
  ++count;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(motor, OUTPUT);
  attachInterrupt(0, add_count, FALLING);
  Serial.println("Press 1 to start motor for velocity test");
}

void loop() {
  if (Serial.available() > 0) {
    ch = Serial.read();
    if(ch=='1' && !on){
      on = !on;
      Serial.println("Turning motor on.");
      Serial.println("Allow motor to reach steady state and press '2' to");
      Serial.println("begin velocity calculation.");
    }
    if(ch=='0' && on) {
      Serial.println("Turning motor off."); 
      Serial.println("Press 1 to turn motor back on and run another test."); 
      on = !on; 
    }
    if(ch=='2' && on && !test_running) {
      test_running = true;
      t_0=millis();
      count = 0;
      Serial.print("t_0 is: ");
      Serial.println(t_0);
      Serial.print("Count at t_0 is: ");
      Serial.println(count);
      Serial.println("Press 3 to end measurement and 0 to stop motor.");
    }
    if(ch=='3' && on && test_running) {
      t_f =millis();
      unsigned long count_f = count;
      Serial.print("t_f in ms was: ");
      Serial.println(t_f);
      Serial.print("Total counts was: ");
      Serial.println(count_f);
      double v = double(count_f)/(t_f - t_0);
      Serial.print("Velocity in counts per ms: ");
      Serial.println(v);
      if(counts_per_rev) {
        v = v * 1000 / counts_per_rev;
        Serial.print("Velocity in revs per sec: ");
        Serial.println(v);
      }
      test_running = false;
    }
  }
  digitalWrite(motor, on);
}
