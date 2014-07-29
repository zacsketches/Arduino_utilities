/*
    Zac Staples
    zacstaples(at)mac.com
    July 2014
    
    I'm working on a project with two processors.  The Arduino
    is controlling a camera hardware and the closed loop feedback
    on a focusing system.  While it is sending image data over
    Serial to a Raspberry Pi so I can view the images collected and
    potentially perform some OpenCV work on them.
    
    This engine is just a simulation of the serial data sent over
    the Arduino's USB to the Pi so I can work on the c++ code
    on the Pi that monitors the serial port.
    
    Global constants come from the values of the ADNS 5020 optical
    mouse sensor I'm using as the camera.
*/

int squal = 0;              //surface quality (0:144)
const int img_len = 225;    //img is 15x15 pixels for 225 pixels
const char* msg_start = "@@@@";

void setup() {
    Serial.begin(9600);
}

void loop() {
    //send start sequence
    Serial.println(msg_start);
    
    //send squal
    squal = random(0, 145);
    Serial.println(squal);
    
    //send random image noise
    for(int i=0; i<img_len; i++){
        Serial.println(random(0, 256));  //color is greyscale (0:255)
    }
}
