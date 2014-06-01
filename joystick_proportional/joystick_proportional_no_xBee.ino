#include <Esplora.h>

/*  develop proportional motor commands for Williams based off joystick
    input.  Output the control solution to serial for debugging.

*/

int rgb[3];        //values of red, green and blue for onboard LED

int y_base[2];     //vector of motor servo commands { servo_left, servo_right }
int dir_mod[2];    //directional modifiers to base values to implement steering
int motor_cmd[2];  //vector sum of y_base and dir_mod

const int max_y = 70;  //70/90 = max amount of servo power for y_stick response
const int max_x = 20;  //20/90 = max amount of servo power for x_stick response

int* find_base(const int stick_y, int* y_base_vals) {
//motor vals is int[2].  stick_y is read from joystick
//returns pointer to motor_vals with motor_vals[0] = servo_left

  int base_mag = map(stick_y, -512, 512, 100, -100);
  
  short r_mult = -1;  //servos are mounted opposite one another so
                      //we have to multiply by -1 for the right servo
                      //to match the left servo's direction
  short l_mult =  1;
  
  int lt_y = l_mult * base_mag * 70 / 100;
  int rt_y = r_mult * base_mag * 70 / 100;
  
  y_base_vals[0] = lt_y;
  y_base_vals[1] = rt_y;
  
  return y_base_vals;
}

int* find_dir_mods(const int stick_x, const int* y_mag, int* dir_mods){
  //take the sign of the direction and speed up each wheel based on 
  //proportional input from x stick
  short lt_mod = 0;
  short rt_mod = 0;
  
  short lt_dir = 0;
  lt_dir = (y_mag[0] >=0 )  ? 1 : -1; 
  
  short rt_dir = 0;
  rt_dir = (y_mag[1] >=0 ) ? 1 : -1;
    
  if( stick_x >= 0 ) {    //left stick input then speed up rt wheel
    rt_mod = map(abs(stick_x), 0, 512, 0, 20);    
  } else {                //right stick input then speed up lt wheel
    lt_mod = map(abs(stick_x), 0, 512, 0, 20);
  }
  
  //adust for direction
  lt_mod *= lt_dir;
  rt_mod *= rt_dir;
  
  dir_mods[0] = lt_mod;
  dir_mods[1] = rt_mod;
  
  return dir_mods;
}

int* find_mtr_vec(int* base, int* mods, int* mtr_cont) {
  //all pointers are two element arrays
  mtr_cont[0] = base[0] + mods[0];
  mtr_cont[1] = base[1] + mods[1];
  return mtr_cont;
}


void setup()
{
  Serial.begin(57600);       // initialize serial communication with your computer
} 

void loop()
{
  int x_val = Esplora.readJoystickX();        // read the joystick's X position
  int y_val = Esplora.readJoystickY();        // read the joystick's Y position
  
  set_rgb(x_val, y_val);
  write_rgb(rgb);
  
  find_base(y_val, y_base);
  find_dir_mods(x_val, y_base, dir_mod);
  find_mtr_vec(y_base, dir_mod, motor_cmd);
  
  stick_print(x_val, y_val, y_base[0], y_base[1], 
              dir_mod[0], dir_mod[1],
              motor_cmd[0], motor_cmd[1]);
  
  delay(10);                                  // a short delay before moving again
}


