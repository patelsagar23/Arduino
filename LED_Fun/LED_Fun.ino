//setting the constants
const int grnPin = 9;
const int redPin = 11;
const int bluPin = 10;
const int toggle = 5;
const int flash = 2;
const int fade = 3;
int togglestate = 0;
int flashstate = 0;
int fadestate = 0;
int color=0;
int redval = 0;
int blueval = 0;
int greenval=0;
int flashing = 0;
int fader = 0;
int ledState = LOW;
long previousMillis = 0;
long interval=500;

//Color arrays
int black[3]  = { 
  0, 0, 0 };
int white[3]  = { 
  100, 100, 100 };
int red[3]    = { 
  100, 0, 0 };
int green[3]  = { 
  0, 100, 0 };
int blue[3]   = { 
  0, 0, 100 };
int yellow[3] = { 
  40, 95, 0 };
int dimWhite[3] = { 
  30, 30, 30 };

// Set initial color
int redVal = black[0];
int grnVal = black[1]; 
int bluVal = black[2];

int wait = 2;      // 10ms internal crossFade delay; increase for slower fades
int hold = 0;       // Optional hold when a color is complete, before the next crossFade
int DEBUG = 1;      // DEBUG counter; if set to 1, will write values back via serial
int loopCount = 60; // How often should DEBUG report?
int repeat = 0;     // How many times should we loop before stopping? (0 for no stop)
int j = 0;          // Loop counter for repeat

// Initialize color variables
int prevR = redVal;
int prevG = grnVal;
int prevB = bluVal;

void setup(){
  if (DEBUG) {
    Serial.begin(9600);
  }
  //Setting Inputs
  pinMode(toggle,INPUT);
  pinMode(flash,INPUT);
  pinMode(fade,INPUT);

  //setting the Outputs
  pinMode(grnPin,OUTPUT);
  pinMode(bluPin,OUTPUT);
  pinMode(redPin,OUTPUT);
}

void loop(){

  //Checks for Fade
  fadestate = digitalRead(fade);
  if(fadestate ==HIGH){
    fader++;
    Serial.print("Fader is ");
    Serial.println(fader);
    delay(500);
  }

  //Checks for button press to toggle between flash and solid modes
  flashstate = digitalRead(2);
  if(flashstate == HIGH){
    flashing++;
    Serial.print("Value of flashing ");
    Serial.println(flashing);
    delay(500);
  }

  //Checks for color input
  togglestate = digitalRead(toggle);
  if(togglestate == HIGH){
    color++;
    Serial.print("Value of color is ");
    Serial.println(color);
    delay(500);
  }    

    //rests color if too high
    if(color == 3){
      color = 0;
    }
    
    //Resets flashstate if the value becomes too high
    if (flashing == 2){
      flashing = 0;
    }
    
    //Resets fader if fader becomes too high
    if (fader == 2){
      fader = 0;
    }
  
  //If fader is 0, do the following
  if (fader == 0){


    //Sets the red value to 255 if color is 0 to create a red LED
    if(color == 0){
      redval=255;
      blueval=0;
      greenval=0;
    }

    //Sets the blue value to 255 if color is 1 to create a blue LED
    if (color == 1){
      redval=0;
      blueval=255;
      greenval=0;
    }

    //Sets the green value to 255 if color is 2 to create a green LED
    if (color == 2){
      redval=0;
      blueval=0;
      greenval=255;
    }

    //Sends signals to the LED if in solid mode
    if (flashing == 0){
      analogWrite(redPin, redval);
      analogWrite(bluPin, blueval);
      analogWrite(grnPin, greenval);
    }

    //Sends signals to the LED if in flash mode
    if (flashing == 1){
      unsigned long currentMillis = millis();
      if(currentMillis - previousMillis > interval){
        previousMillis = currentMillis;
        if (ledState == LOW)
          ledState = HIGH;
        else
          ledState = LOW;
        if(ledState == HIGH){
          analogWrite(redPin, redval);
          analogWrite(bluPin, blueval);
          analogWrite(grnPin, greenval);
        }
        if(ledState ==LOW){
          analogWrite(redPin, 0);
          analogWrite(bluPin, 0);
          analogWrite(grnPin, 0);
        }
      }
    }

    Serial.println(flashing);

    //Printing the vlaues to the serial monitor
    /*Serial.print("Red Value: ");
     Serial.print(redval);
     Serial.print("\t Green Value: ");
     Serial.print(greenval);
     Serial.print("\t Blue Value: ");
     Serial.print(blueval);
     Serial.print("Color Value ");
     Serial.println(color);*/
  }

  //If fader is 1, start the fade
  if (fader == 1){
    crossFade(red);
    crossFade(green);
    crossFade(blue);
    crossFade(yellow);

    if (repeat) { // Do we loop a finite number of times?
      j += 1;
      if (j >= repeat) { // Are we there yet?
        exit(j);         // If so, stop.
      }
    }
  }
}
/* BELOW THIS LINE IS THE MATH -- YOU SHOULDN'T NEED TO CHANGE THIS FOR THE BASICS
 * 
 * The program works like this:
 * Imagine a crossfade that moves the red LED from 0-10, 
 *   the green from 0-5, and the blue from 10 to 7, in
 *   ten steps.
 *   We'd want to count the 10 steps and increase or 
 *   decrease color values in evenly stepped increments.
 *   Imagine a + indicates raising a value by 1, and a -
 *   equals lowering it. Our 10 step fade would look like:
 * 
 *   1 2 3 4 5 6 7 8 9 10
 * R + + + + + + + + + +
 * G   +   +   +   +   +
 * B     -     -     -
 * 
 * The red rises from 0 to 10 in ten steps, the green from 
 * 0-5 in 5 steps, and the blue falls from 10 to 7 in three steps.
 * 
 * In the real program, the color percentages are converted to 
 * 0-255 values, and there are 1020 steps (255*4).
 * 
 * To figure out how big a step there should be between one up- or
 * down-tick of one of the LED values, we call calculateStep(), 
 * which calculates the absolute gap between the start and end values, 
 * and then divides that gap by 1020 to determine the size of the step  
 * between adjustments in the value.
 */

int calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = 1020/step;              //   divide by 1020
  } 
  return step;
}

/* The next function is calculateVal. When the loop value, i,
 *  reaches the step size appropriate for one of the
 *  colors, it increases or decreases the value of that color by 1. 
 *  (R, G, and B are each calculated separately.)
 */

int calculateVal(int step, int val, int i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;           
    } 
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    } 
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}

/* crossFade() converts the percentage colors to a 
 *  0-255 range, then loops 1020 times, checking to see if  
 *  the value needs to be updated each time, then writing
 *  the color values to the correct pins.
 */

void crossFade(int Color[3]) {
  // Convert to 0-255
  int R = (Color[0] * 255) / 100;
  int G = (Color[1] * 255) / 100;
  int B = (Color[2] * 255) / 100;

  int stepR = calculateStep(prevR, R);
  int stepG = calculateStep(prevG, G); 
  int stepB = calculateStep(prevB, B);

  for (int i = 0; i <= 1020; i++) {
    redVal = calculateVal(stepR, redVal, i);
    grnVal = calculateVal(stepG, grnVal, i);
    bluVal = calculateVal(stepB, bluVal, i);

    analogWrite(redPin, redVal);   // Write current values to LED pins
    analogWrite(grnPin, grnVal);      
    analogWrite(bluPin, bluVal); 

    delay(wait); // Pause for 'wait' milliseconds before resuming the loop

    if (DEBUG) { // If we want serial output, print it at the 
      if (i == 0 or i % loopCount == 0) { // beginning, and every loopCount times
        Serial.print("Loop/RGB: #");
        Serial.print(i);
        Serial.print(" | ");
        Serial.print(redVal);
        Serial.print(" / ");
        Serial.print(grnVal);
        Serial.print(" / ");  
        Serial.println(bluVal); 
      } 
      DEBUG += 1;
    }
  }
  // Update current values for next loop
  prevR = redVal; 
  prevG = grnVal; 
  prevB = bluVal;
  delay(hold); // Pause for optional 'wait' milliseconds before resuming the loop
}





