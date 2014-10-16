/* 
  An example to demonstrate a macro command that allows
  logging data to a Serial port.  In the case of the Mega
  or Due this allows you to connect an OpenLog device from
  Sparkfun and log to it using the macro....saves a lot of 
  typing Serial.print!

  using capital Log prevents a namespace conflict with the 
  log(x) command for logarithms.
*/

#define LOG_UART Serial
#define Log(x) LOG_UART.println(x);

// This version allows logging with precision specified for floating
// point numbers Log_precision
#define Log_p(x, y) LOG_UART.println(x, y);


void setup() {
  Serial.begin(115200);
  Serial.println();
  
  Log("test");
  Log_p(3.145789,3);
  Log(4);
  const char* c = "another test";
  Log(c);

}

void loop() {
  // put your main code here, to run repeatedly:

}
