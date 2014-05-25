Continuous Rotation Servo for Arduino

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