//Timer
long interval = 1000;
long previousMillis = 0;
long currMillis = 0;

//Constants for fading the LED
long fadeBrightness = 0;
long fadeAmount = 100; //Bigger value means fade will become slower
long redFade = 0;
long greenFade = 0;
long blueFade = 0;
int direct = 1;

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

//Set the initial mapped values
int redValM;
int grnValM;
int bluValM;

//Buttons
const int power = 2;
const int pattern = 3;
const int color = 4;
const int crossfade = 5;

//Random Constants
int Monitor = 1;
int powerState = 0;
int on;
int off;
int currColor = 1;
int currPattern = 1;
int flashState = 1;

//Constants for crossfade
int i = 0;
int crossState = 1;
int wait = 10;
int previ = 1;
int DEBUGcount = 1;
int redValF = 255;
int grnValF = 0;
int bluValF = 0;

//Constants for colorToggle
int toggleWait = 2000;

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

  Serial.println("Setup has finished");
}

void loop(){
  //Serial.println(powerState);
  //Serial.println(currColor);

  //Maps the values of redVal, bluVal, and grnVal
  redValM = map(redVal, 0, 100, 0, 255);
  bluValM = map(bluVal, 0, 100, 0, 255);
  grnValM = map(grnVal, 0, 100, 0, 255);

  if (powerState == 1){

    //Serial.println("ON");

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

    default:
      currColor = 1;
      break;
    }

    //Cases that write the values to the LED
    switch (currPattern) {
    case 1:
      digitalWrite(redPin,redValM);
      digitalWrite(grnPin,grnValM);
      digitalWrite(bluPin,bluValM);
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
        digitalWrite(redPin,redValM);
        digitalWrite(grnPin,grnValM);
        digitalWrite(bluPin,bluValM);
        break;

      case 2:
        digitalWrite(redPin,LOW);
        digitalWrite(grnPin,LOW);
        digitalWrite(bluPin,LOW);
        break;
      }
      break;

    case 3:
      if (fadeBrightness == 100 * fadeAmount){
        direct = 2;
      }
      if (fadeBrightness == 0){
        direct = 1;
      }

      switch(direct) {
      case 1:
        fadeBrightness = fadeBrightness + 1;
        break;

      case 2:
        fadeBrightness = fadeBrightness - 1;
        break;
      }

      redFade = redVal * fadeBrightness / 100 / fadeAmount;
      greenFade = grnVal * fadeBrightness / 100 / fadeAmount;
      blueFade = bluVal * fadeBrightness / 100 / fadeAmount;

      analogWrite(redPin,redFade);
      analogWrite(bluPin,blueFade);
      analogWrite(grnPin,greenFade);

      //Turning on debug in this area will affect the fade
      //speed due to the Serial.println command speed limit
      //Serial.println(redFade);
      //Serial.println(blueFade);
      //Serial.println(greenFade);
      //Serial.println(fadeBrightness);
      //Serial.println(direct);

      break;

    default:
      currPattern = 1;
      break;
    }

    //Checks to see if power is being pushed
    if(digitalRead(power) == HIGH){
      delay(500);
      Serial.println("LED has now turned off");
      powerState = 0;
    }  

    //Checks to see if crossfade button is pushed
    if(digitalRead(crossfade) == HIGH){
      delay(500);
      crossState ++;
      if(crossState == 2){
        Serial.println("Cross fade is now on");
      }
    }

    switch (crossState) {
    case 1:

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

      if(digitalRead(pattern) == HIGH){
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
        if(currPattern == 3){
          Serial.println("Current pattern is fading");
        }
      }

      break;

    case 2:

      currMillis = millis();
      if(currMillis - previousMillis > wait){
        previousMillis = currMillis;
        i ++; 
        /*Serial.print(previ);
         Serial.print("\t");
         Serial.println(i);*/
      }

      if(previ != i){
        //Serial.println(i);
        previ = i;   // Sets prev i back to i
        if (i < 257) // First phase
        {
          redValF   -= 1; 
          grnValF += 1; 
          bluValF   = 0; 
        }

        else if (i < 512) // Second phase
        {
          redValF    = 0; 
          grnValF -= 1;
          bluValF  += 1;
        } 

        else if (i < 767) // Third phase
        {
          redValF  += 1;
          grnValF = 0; 
          bluValF -= 1; 
        }

        else // Re-set the counter
        {
          i = 1;
        }  
      }

      analogWrite(redPin,   redValF); 
      analogWrite(grnPin, grnValF); 
      analogWrite(bluPin,  bluValF);

       Serial.print(i);     
       Serial.print("\t");    
       Serial.print("R:");    
       Serial.print(redValF);  
       Serial.print("\t");    
       Serial.print("G:");    
       Serial.print(grnValF);
       Serial.print("\t");    
       Serial.print("B:");    
       Serial.println(bluValF);

      /*Serial.print(previ);
       Serial.print("\t");
       Serial.println(i);*/
      break;

    case 3:
      currMillis = millis();
      if(currMillis - previousMillis > toggleWait){
        previousMillis = currMillis;
        currColor ++;
      }
      analogWrite(redPin,   redValM); 
      analogWrite(grnPin, grnValM); 
      analogWrite(bluPin,  bluValM);
      break;

    default:
      crossState = 1;
      if(crossState == 1){
        Serial.println("Cross fade is now off");
      }
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





































