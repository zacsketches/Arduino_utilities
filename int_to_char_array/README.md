Convert an integer to a character array on Arduino.

passing large integer values over the serial port is not entirely
obvious with Arduino.

This example shows how to use the sprintf function to change and 
integer or other larger number into a string so it can be easily
passes over the Serial port.  Once it's received you can use the
atoi(char*) function to convert back to a numeric format.
