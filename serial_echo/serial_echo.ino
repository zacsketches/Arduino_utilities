/*
	This is a serial echo utility for itegers.  It demonstrates
	how to read an integer from the serial monitor and echo it 
	back to the user
*/

char buf[50];		//buffer to read user input

void setup() {
	Serial.begin(115200);
	Serial.println();
	
	Serial.println("This script will echo integers.  Size of input");
	Serial.println("is limited by numeric limits (16 bit on uno, and");
	Serial.println("32 bit on Due).");
	
}

void loop() {
		
	//check to see if anything is available
	if(Serial.available()) {
		//set iteration variables
		int index = 0;
		
		// clear the input buffer
		while(Serial.available()) {
			buf[index] = serial.read();
			++index;
		}
		buf[index] = NULL;
		
		//do conversion to int
		int input = atoi(buf);
		
		//echo to user
		Serial.println("You entered:");
		Serial.print("\t");
		Serial.println(input);
	}
	
	//run the loop at about 10hz
	delay(100);
}