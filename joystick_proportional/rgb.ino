void rgb_print(const int* rgb_val) {
  Serial.print("\tRGB led: r,");                // print a label for the X value
  Serial.print(rgb_val[0]);                        // print the X value
  Serial.print("\tg,");                       // print a tab character and a label for the Y value
  Serial.print(rgb_val[1]);                      // print the Y value  
  Serial.print("\tb,");                       // print a tab character and a label for the Y value
  Serial.println(rgb_val[2]);                      // print the Y value  
}

int* set_rgb(const int x_val, const int y_val) {
  //set values in the rgb[] array based on joystick feedback
  /*  calculate RBG LED color and intensity based off stick direction
      to provid on-board feedback for joystick input.
     
                           Red
                            ^ 
                     Blue <   > Yellow
                            |
                          Green
  */
  int red = 0;
  int green = 0;
  int blue = 0;
  int yellow = 0;
  
  if(y_val < 0) {
    red = map(y_val, -512, 0, 255, 0);
  }
  if(y_val >=0) {
    green = map(y_val, 0, 512, 0, 255);
  }
  if(x_val >=0) {
    blue = map(x_val, 0, 512, 0, 255);  
  }
  if(x_val < 0) {
    //trickier case of activating yellow because it is a blend of
    //primary red and green light.
    yellow = map(x_val, -512, 0, 255, 0);
    if(yellow > green)
      green = yellow;
    if(yellow > red)
      red = yellow;
  }
  rgb[0] = red;
  rgb[1] = green;
  rgb[2] = blue;
  
  return rgb;
}

void write_rgb(const int* rgb_val){
   Esplora.writeRGB(rgb_val[0], rgb_val[1], rgb_val[2]); 
}

