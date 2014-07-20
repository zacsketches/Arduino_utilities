/*  I2C_expander_example
    
    This program flashes an series of 5 LEDs connected to P00 of the PCF8575 breakout 
    board from Sparkfun.  The LEDs areconnected so that current is sourced form VCC and the 
    PCF8575 sinks current when P00 is written low.  From the PCF8575 datasheet the chip can
    source or sink up to 100ma.  My five LEDs are connected through 470Ohm resistors so they
    pull a max of 10.6ma each or a total of less than 55ma.   
*/

#include <Wire.h>

const int exp1_address = 0x26; //7 bit hex address for PCF8575 with A2=H, A1=H, A0=L
const int delay_int = 100;
const int led_array_size = 5;

byte byte_1 = 0x00;
byte byte_2 = 0x00;
byte print_byte;
char typeset_byte[led_array_size +1];



void setup() {
  Wire.begin();  //join i2c bus
  Serial.begin(57600);
}

void loop() {
  byte_1 = 0x00;
  for (int i = 0; i<led_array_size; i++) {
    byte rand_bit = random_bit();
    rand_bit = rand_bit << i;
    byte_1 = byte_1 | rand_bit;  
  }

  write_to_I2C_expander();
  print_config_to_serial();
  delay(delay_int);
}

byte random_bit() {
  static long rand_int;
  byte res = 0x00;
  rand_int = random(0, 2);
  res = res | rand_int;
  return res;
}

void write_to_I2C_expander() {
   Wire.beginTransmission(exp1_address);
   Wire.write(byte_1);
   Wire.write(byte_2);
   Wire.endTransmission();
}

void print_config_to_serial() {
  print_byte = byte_1;
  
  //set the right values in the typeset_byte
  for(int i=0; i<led_array_size; i++) {
      if(bitRead(print_byte, ((led_array_size-1)-i)) == 1) {
        typeset_byte[i] = '0';
      } else {
        typeset_byte[i] = '1';
      }
  }
 
  Serial.print(F("Switching the config to: "));
  Serial.println(typeset_byte);
}
