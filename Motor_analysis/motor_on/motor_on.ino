/* Test sketch to ensure the control circuit for a DC circuit is
 * wired properly.  This control loop is designed to work with 
 * a current sink power transistor below the motor.
 * 
 * See http://zacsketches.com/sink for the intended schematic
 */

const int motor = 5;

void setup() {
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
  Serial.println("Turning motor on.");
}

void loop() {
  digitalWrite(motor, HIGH);
}

