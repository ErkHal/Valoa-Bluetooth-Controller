/*
 *##############################################
 * 
 * LedController Arduino Sketch
 * 
 * Author: Erkki Halinen ©2018
 * 
 * Notes: Written for Arduino Uno board to control an IKEA
 *        Ledberg common cathode LED strips. Uses three NPN 
 *        transistors and PWM to adjust the color and 
 *        brightness of the LED strip. Receives input via
 *        bluetooth serial in the future revisions.
 *        
 *###############################################        
 */

/* Output pins, you may need to change these depending on
 * your board and wiring
*/
int redPin = 10;
int greenPin = 9;
int bluePin = 11;

//Global variables for each color
int red;
int green;
int blue;

void setup() {
  //Setup output pins we defined before
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  //Start serial communication with a specified baud rate
  Serial.begin(9600);

}

void loop() {
  if(Serial.available() > 0) {
    readColorValues();
    writeValuesToPins();
  }
 }

 //Reads the color values from the serial input
 void readColorValues() {
  red = Serial.parseInt();
  green = Serial.parseInt();
  blue = Serial.parseInt();
  //Serial messages for debugging
  Serial.println(red);
  Serial.println(green);
  Serial.println(blue);
 }

 //Writes PWM signals to output pins
 void writeValuesToPins() {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 }

