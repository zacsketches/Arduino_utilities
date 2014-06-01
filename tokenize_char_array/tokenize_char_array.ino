/* strtok() Arduino example for a string contained in 
   the source code.  

   based on the reference example at: 
   http://www.cplusplus.com/reference/cstring/strtok/

   Zac Staples. July, 2013.
*/

void setup() {
	Serial.begin(9600);
	char str[] = "{label,4,8,9}";
	char* p;
	Serial.print("Example of splitting a string into tokens: ");
	Serial.print("The input string is: '");
	Serial.print(str);
	Serial.println("'");

	p = strtok(str, "{,}");	//2nd argument is a char[] of delimiters
	while (p != NULL) {	//not equal to NULL
		Serial.println(p);
		p = strtok(NULL, "{,}");	//expects NULL for string on subsequent calls
	}
}

void loop() {
	delay(250);
}
