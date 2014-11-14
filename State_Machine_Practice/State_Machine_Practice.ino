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

//State Setup
int nextState;
int currState;
int byebye;

//Variables for Mode changing
String modeList[] = {
  "solid","fade","colorFade","colorFlash"};
String mode;
int modeIndex = 0;
int currMode;

//LED setup
int redPin = 9;
int greenPin = 9;
int bluePin = 10;

//Buttons
const int colortoggle = 5;
const int flashtoggle = 3;
int modeChange;
int colorVal;
int flashVal;
int colorState = 1;
int flashState = 1;
int flashspeed = 500;

enum cases{
  solid,
  flash,
  initialize,
  idle,
  updateMode,
  updateLED,
  leave};


void setup(){
  Serial.begin(9600);
  pinMode(colortoggle,INPUT);
  pinMode(flashtoggle,INPUT);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  currState = initialize;
  Serial.println("Setup has finished!");
  Serial.print("flashState is ");
  Serial.println(flashState);
  Serial.print("colorState is ");
  Serial.println(colorState);
}

void loop(){
  while(currState != leave){
    
    modeChange = digitalRead(2);

    colorVal = digitalRead(colortoggle);
    if (colorVal == HIGH){
      colorState++;
      if (colorState == 4){
        colorState = 1;
      }
      Serial.print("colorState is ");
      Serial.println(colorState);
      delay(500);
    }

    flashVal = digitalRead(flashtoggle);
    if (flashVal == HIGH){
      flashState++;
      if (flashState == 3){
        flashState = 1;
      }
      Serial.print("flashState is ");
      Serial.println(flashState);
      delay(500);
    }
    
    mode = modeList[modeIndex];

    switch (currState){

    case initialize:
      Serial.println("Current Case is Initialize");
      nextState = idle;
      break;

    case idle:
      if(modeChange == HIGH){
        nextState = updateMode;
      }
      else if(flashState == 1){
        nextState = solid;
      }      
      else if(flashState == 2){
        nextState = flash;
      }
      break;

    case updateLED:
      analogWrite(redPin,redVal);
      analogWrite(greenPin,grnVal);
      analogWrite(bluePin,bluVal);
      nextState = idle;
      break;

    case updateMode:
      if (modeIndex == 3){
        modeIndex = 0;
      }
      else{
        modeIndex++;
      } 
      delay(500);

      currMode = modeIndex;
      nextState = currMode;
      Serial.println("Current Case: Update Mode");
      break;

    case solid:
      if(colorState = 1){
        redVal = red[0];
        grnVal = red[1];
        bluVal = red[2];
      }
      else if(colorState = 2){
        redVal = green[0];
        grnVal = green[1];
        bluVal = green[2];
      }
      else if(colorState = 2){
        redVal = blue[0];
        grnVal = blue[1];
        bluVal = blue[2];
      }
      currMode=solid;
      nextState = updateLED;
      Serial.println("Current Case: Solid");
      break;
    }
  }

  analogWrite(redPin, LOW);
  analogWrite(greenPin, LOW);
  analogWrite(bluePin, LOW);
}






