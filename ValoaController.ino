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
 *        
 *###############################################        
 */
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];

boolean newData = false;

/* Output pins, you may need to change these depending on
 * your board and wiring
*/
int redPin = 9;
int greenPin = 10;
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

  Serial.begin(9600);
}

void loop() {
recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        newData = false;
        writeValuesToPins();
    }
}

//##################### Writes PWM signals to output pins
 void writeValuesToPins() {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 }

//##################### Serial reading and parsing functions

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars, ",");
    red = atoi(strtokIndx);     // convert this part to an integer
 
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    green = atoi(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    blue = atoi(strtokIndx);     // convert this part to an integer

}



