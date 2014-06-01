void stick_print(const int x_val, const int y_val,
                 const int l_mag, const int r_mag,
                 const int l_mod, const int r_mod,
                 const int l_final, const int r_final) 
{
  Serial.print("Joystick X: ");                // print a label for the X value
  Serial.print(x_val);                        // print the X value
  Serial.print("\tY: ");                       // print a tab character and a label for the Y value
  Serial.print(y_val);                      // print the Y value  
  Serial.print("\tl_base: ");
  Serial.print(l_mag);
  Serial.print("\tr_base: ");
  Serial.print(r_mag);
  Serial.print("\tl_mod: ");
  Serial.print(l_mod);
  Serial.print("\tr_mod: ");
  Serial.print(r_mod);
  Serial.print("\tl_fin: ");
  Serial.print(l_final);
  Serial.print("\tr_fin: ");
  Serial.print(r_final);
 
  Serial.println();
}

