/*  Extends the standard servo class to add a few parameters
    for controlling continuous rotation servos.  
    
    A continuous rotation servo has a center value that is set
    by rotating the potentiometer that is normally used to 
    measure feedback.  By varying the position of this pot
    a continuous rotation servo's center postion can be moved.
    
    A continuous rotation servo will continue to rotate unless the 
    incoming PWM signal is equivalent to the voltage position indicated 
    by the pot.  By setting, then calling the .write_ctr() method you can
    put the servo at its center position.  This allows you to "tune"
    the servo with your code instead of your screwdriver on the pot...
    ....Maker's call on what you find easier!
    
    Depending on the physical installation of the servos
    in your application, they may rotate in opposite directions for
    for the same command.
    
    For example, you might want two drive wheel servos to both rotate
    forward for .write(int) in the range [90, 180] and backward for 
    write(int) in the range [0, 90).  However, due to their physical 
    installation, usually mirrored, one of them will probably rotate
    in the opposite direction.  By setting one of the servos to have
    backward rotation via the .set_rotation(Dir::bacK) method you can
    send the same command to both servos, and they will rotate in
    the same direction.
    
    Finally, this class overrides the servo .write(int) function to
    implement the rotational direction, but values over 544 to the 
    write function are passed back to the base class.  See below for more
    on this.
*/

#include <Servo.h>

class Cont_rot_servo : public Servo {

public:
  enum Dir {fwd, back};
	
  Cont_rot_servo() : ctr(90), rot(fwd) {}

  int center() { return ctr; }
  void set_center(int center) { ctr = center; }
  
  //Override write() method from base class to use rot value.
  //Servos with rot==-1 will rotate in the opposite direction
  //with the same magnitude as as a Servo with rot==1.
  //
  //write values over MIN_PULSE_WIDTH (usually 544) are interpreted
  //as a microseconds command and rotation is not applied.
  void write(int value);
  
  void write_ctr() { write( ctr ); }

  int rotation() { return (rot == fwd) ? 1 : -1; }
  void set_rotation(Dir rotation) { rot = rotation; }

private:
  int ctr;
  Dir rot;
};

void Cont_rot_servo::write(int value)
{ 
  if(value < MIN_PULSE_WIDTH) 
  {// treat values less than 544 as angles in degrees (valid
   // values in microseconds are handled as microseconds)
    if(rot == fwd)
    {  
      if(value < 0) value = 0;
      if(value > 180) value = 180;
      value = map(value, 0, 180, MIN_PULSE_WIDTH,  MAX_PULSE_WIDTH);      
    } if(rot == back ) {
      //reverse the mapping for negative rotation
      if(value < 0) value = 0;
      if(value > 180) value = 180;
      value = map(value, 0, 180, MAX_PULSE_WIDTH,  MIN_PULSE_WIDTH);    
    }
  }
  this->writeMicroseconds(value);
}

Cont_rot_servo crs;

void setup() {
  crs.attach(3);
  crs.write_ctr();

  Serial.begin(9600);
}

void loop() {
  /*
    TODO I need to do a better job writing a servo based example.
  */
  static long start = millis();
  Serial.print("ctr is: ");
  Serial.print(rt.center());
  Serial.print("\trot is: ");
  Serial.print(rt.rotation());
  Serial.println();
  
  delay(10000);
}
