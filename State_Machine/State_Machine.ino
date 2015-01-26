//Timer
long interval = 1000;
long previousMillis = 0;
long currMillis = 0;

//LED Pins
const int redPin = 11;
const int bluPin = 10;
const int grnPin = 9;

//Colors
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

//Set the initial colors
int redVal = black[0];
int grnVal = black[1];
int bluVal = black[2];

//Buttons
const int power = 2;
const int pattern = 3;
const int color = 4;
const int crossfade = 5;

//State Setup
int nextState;
int currState;

//Setup enum
enum cases{
  solid,
  fade,
  colorFade,
  colorFlash,
  initialize,
  idle,
  updateMode,
  updateLEDs,
  leave
};

//Mode Changing Variables
String modeList[] = {
  "solid","fade","colorFade","colorFlash"};
String mode;
int modeIndex = 0;
int currMode;

//Random Constants
int Monitor = 1;
int powerState = 0;
int on;
int off;
int currColor = 1;
int currPattern = 1;
int flashState = 1;

void setup(){
  if (Monitor == 1){
    Serial.begin(9600);
  }

  //Inputs
  pinMode(power,INPUT);
  pinMode(pattern,INPUT);
  pinMode(color,INPUT);
  pinMode(crossfade,INPUT);

  //Outputs
  pinMode(grnPin,OUTPUT);
  pinMode(bluPin,OUTPUT);
  pinMode(redPin,OUTPUT);

  currState = solid;

  Serial.println("Setup has finished");
}

void loop(){
  //Serial.println(powerState);
  //Serial.println(currColor);

  if (powerState == 1){

    //Serial.println("ON");

    //Checks to see if power is being pushed
    if(digitalRead(power) == HIGH){
      delay(500);
      Serial.println("LED has now turned off");
      powerState = 0;
    }  

    //Reads the color button to check if color should change
    if(digitalRead(color) == HIGH){
      delay(500);
      Serial.println("Color button has been pressed");
      currColor++;
      //Resets currColor if it becomes too high
      if(currColor == 4){
        currColor = 1;
      }
      //Prints the new color values
      if(currColor == 1){
        Serial.println("New color is now red");
      }
      if(currColor == 2){
        Serial.println("New color is now green");
      }
      if(currColor == 3){
        Serial.println("New color is now blue");
      }
    }

    switch (currColor) {
    case 1:
      redVal = red[0];
      grnVal = red[1];
      bluVal = red[2];
      break;

    case 2:
      redVal = green[0];
      grnVal = green[1];
      bluVal = green[2];
      break;

    case 3:
      redVal = blue[0];
      grnVal = blue[1];
      bluVal = blue[2];
      break;    
    }

   /* if(digitalRead(pattern == HIGH)){
      delay(500);
      Serial.println("Pattern button has been pressed");
      currPattern ++;
      //Prints the current pattern
      if(currPattern == 1){
        Serial.println("Current pattern is solid");
      }
      if(currPattern == 2){
        Serial.println("Current pattern is flashing");
      }
    }*/

    //Cases that write the values to the LED
    switch (currPattern) {
    case 1:
      digitalWrite(redPin,redVal);
      digitalWrite(grnPin,grnVal);
      digitalWrite(bluPin,bluVal);
      break;

    case 2:
      currMillis = millis();
      if(currMillis - previousMillis > interval){
        previousMillis = currMillis;
        if(flashState == 1){
          flashState = 2;
        }
        else{
          flashState =1;
        }
      }
      switch(flashState) {
      case 1:
        digitalWrite(redPin,redVal);
        digitalWrite(grnPin,grnVal);
        digitalWrite(bluPin,bluVal);
        break;

      case 2:
        digitalWrite(redPin,LOW);
        digitalWrite(grnPin,LOW);
        digitalWrite(bluPin,LOW);
        break;
      }
      break;

    default:
      currPattern = 1;
      break;
    } 

  }

  if (powerState == 0){

    if(digitalRead(power) == HIGH){
      delay(500);
      Serial.println("LED is now on");
      powerState = 1;
    }  

    digitalWrite(redPin,LOW);
    digitalWrite(grnPin,LOW);
    digitalWrite(bluPin,LOW);
    //Serial.println("OFF");
  }
}

















