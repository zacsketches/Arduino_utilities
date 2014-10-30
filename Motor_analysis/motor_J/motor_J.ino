/* Written by Zac Staples, zacstaples@mac.com
 * Designed to work with a simple encoder kit based on hall effect
 * sensor attached to digital pin 2.  A DC motor signal is controlled
 * on pin 5.  
 * 
 * This sketch will provide data to find the rotor inertia of a DC motor.
 * The data must be cut and pasted from the Serial Monitor into MATLAB
 * where the time constant of the velcity decay can be calculated based off
 * the shape of the plot.
 *
 * to avoid delay in writing to the serial port data points are stored into
 * an array and then the entire array is written to Serial at the end of the 
 * test.  For my small DC motors one second of data is plenty to capture.
 */

#include <Serial.h>

const int counts_per_rev = 8;  //this will depend on the specs for your encoder
const int array_size = 250;    //too big will overflow arduino RAM

const int motor = 5;
bool on = false;
bool test_running = false;
unsigned long t_0=0;      //start time
unsigned long t_f=0;      //final time
volatile unsigned long count=0;
char ch;

int measurement[array_size];
int counts[array_size];

void add_count() {
  ++count;
}

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(motor, OUTPUT);
  attachInterrupt(0, add_count, FALLING);
  Serial.println("Press 1 to start motor armature inertia (J) test");
}

void loop() {
  if (Serial.available() > 0) {
    ch = Serial.read();
    if(ch=='1' && !on){
      on = !on;
      Serial.println("Turning motor on.");
      Serial.println("Allow motor to reach steady state and press '2' to");
      Serial.println("begin taking data.  Test will complete in about 2 second.");
    }
    if(ch=='0' && on) {
      Serial.println("Turning motor off."); 
      on = !on; 
    }
    if(ch=='2' && on && !test_running) {
      test_running = true;
      t_0=millis();
      count = 0;
      //shut off the motor
      on = !on;
      digitalWrite(motor, on);
      //take datapoints
      int i = 0;
      while(i < array_size) {
        measurement[i] = i;
        counts[i] = count;
        ++i;
        //shut motor off after 25 datapoints
        delay(2);  
      }
      t_f=millis();
      Serial.println("Test complete.");
      Serial.println("Press 3 to dump data to Serial.");
      test_running = false;
    }
    if(ch=='3' && !on && !test_running) {
      Serial.print("t_0=");
      Serial.println(t_0);
      Serial.print("t_f=");
      Serial.println(t_f);
      test_running = false;
      for (int i=0; i<array_size; ++i) {
        Serial.print(measurement[i]);
        Serial.print(", ");
        Serial.println(counts[i]);
      }
    }
  }
  digitalWrite(motor, on);
}
