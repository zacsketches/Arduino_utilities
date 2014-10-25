#include <quadrature.h>

/*
	This script is designed to work with the Arduino Motor Shield.
	It accepts user integer input from the serial monitor and
	changes the PWM Signal sent to Motor B.
	
	It is compatible with the master branch of my Encoder library
	available at:
		https://github.com/zacsketches/Encoder.git
		
	Using the quadrature counts the sketch writes a data line
	to the serial port of the timestamp in milliseconds and the
	count on the encoder.  Copy and past this data into a text
	file and then open the data file in MATLAB.  Transform position
	into velocity in MATLAB and then plot the velocity vs time.
	
	From the shape of this plot you should be able to determine
	if the motor transfer function is first or second order.
	
*/

//Physical constants for motor a
const int pwm_pin = 11;
const int dir_pin = 13;
const int brake_pin = 8;
const int current_sense_pin = A1;

//Boolean flags
bool valid_command = false;

//Objects
Quadrature_encoder<0,1> encoder;

//Globals
typedef uint32_t Time;
typedef int32_t Count;
const Time test_length = 3000;	//in milliseconds

char buf[50];		//buffer to read user input

void setup() {
	Serial.begin(115200);
	Serial.println();
	
	Serial.println("This script will provide a step input to Motor_B");
	Serial.println("based off input received on the serial monitor in");
	Serial.println("the range [0:255].  The script will output time in");
	Serial.println("ms and encoder counts {stamp:long,counts:long} to the");
	Serial.print("the serial port for ");
	Serial.print(test_length);
	Serial.println("ms.  Cut and paste this");
	Serial.println("data into a text file an then import into excel or");
	Serial.println("MATLAB to analyze the data.");
	Serial.println();
	Serial.println("Enter a PWM command: ");
	
	pinMode(pwm_pin, OUTPUT);
	pinMode(dir_pin, OUTPUT);
	digitalWrite(dir_pin, HIGH);

	encoder.begin();
}

void loop() {
		
	//check to see if anything is available
	if(Serial.available()) {
		//set iteration variables
		int index = 0;
		
		// clear the input buffer
		while(Serial.available()) {
			buf[index] = Serial.read();
			++index;
		}
		buf[index] = NULL;
		
		//do conversion to int
		int input = atoi(buf);
		
		//check to make sure the command is range
		if(input < 256 && input >= 0) {
			//set flag
			valid_command = true;
			if(valid_command) {
				//echo to user
				Serial.print("Running test at PWM:");
				Serial.println(input);
				
				//run the test
				run_test(input);
				
				//set up to run again
				Serial.println();
				Serial.println("Enter a PWM command: ");

			} else {
				Serial.println("You did not enter a valid command");
			}
		}
		
	}
	
	//run the input checking loop at about 10hz
	delay(100);
}

void run_test(int pwm) {
	Time now = millis();
	Time finish = now + test_length;
	
	while(now < finish) {
		analogWrite(pwm_pin, pwm);
		Time stamp = now;
		Count pos = encoder.count();
		Serial.print("{stamp:");
		Serial.print(now);
		Serial.print(",count:");
		Serial.print(pos);
		Serial.println("}");
		now = millis();
	}
	
	//shut the motor off
	analogWrite(pwm_pin, 0);
}
