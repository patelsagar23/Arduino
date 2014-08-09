int red = 0;
int green = 0;
int blue = 0;

//Constants for the LED
const int greenpin = 9;
const int redpin = 11;
const int bluepin = 10;

void setup(){
  Serial.begin(9600);
  
  //Setting pins as outputs
  pinMode(greenpin,OUTPUT);
  pinMode(redpin,OUTPUT);
  pinMode(bluepin,OUTPUT);
}

void loop(){
  analogWrite(greenpin,128);
  analogWrite(redpin,255);
  analogWrite(bluepin,0);
} 
