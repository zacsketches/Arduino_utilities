/*
	This script is designed to work with the Arduino Motor Shield.
	It accepts user integer input from the serial monitor and
	changes the PWM Signal sent to Motor B.
	
	I use Motor B instead of Motor A because, the Motor A pwm
	pin is on D3.  I need D3 for another purpose if I later
	want to implement quadrature encoding because D3 is the 
	pin for INT_1 on the Arduino Uno.
*/

//Physical constants for motor a
const int pwm_pin = 11;
const int dir_pin = 13;
const int brake_pin = 8;
const int current_sense_pin = A1;

//Boolean flags
bool valid_command = false;

char buf[50];		//buffer to read user input

void setup() {
	Serial.begin(115200);
	Serial.println();
	
	Serial.println("This script will set the pwm value of Motor_B");
	Serial.println("based off input received on the serial monitor in");
	Serial.println("the range [0:255].");
	
	pinMode(pwm_pin, OUTPUT);
	pinMode(dir_pin, OUTPUT);
	digitalWrite(dir_pin, HIGH);
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
				analogWrite(pwm_pin, input);

				//echo to user
				Serial.println("You entered:");
				Serial.print("\t");
				Serial.println(input);

			} else {
				Serial.println("You did not enter a valid command");
			}
		}
		
	}
	
	//run the loop at about 10hz
	delay(100);
}
