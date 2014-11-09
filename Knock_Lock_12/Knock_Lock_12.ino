#include <Servo.h>
Servo myServo;

//constants
const int piezo = A0;
const int switchPin = 2;
const int yellow = 4;
const int green = 3;
const int red = 5;
int knockVal;
int switchVal;
const int quietKnock = 10;
const int loudKnock = 100;
boolean locked = false;
int numberOfKnocks = 0;

//setup
void setup(){
  myServo.attach(9);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
  digitalWrite(green, HIGH);
  myServo.write(0);
  Serial.println("The box is unlocked!");
}

void loop(){
  //Check to see if device is locked and if it is then check for switch press
  if(locked == false){
    switchVal = digitalRead(switchPin);
    
    //if switch is pressed, then lock the device
    if(switchVal == HIGH){
      locked = true;
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      myServo.write(90);
      Serial.println("The box is locked!");
      delay (1000);
    }
  }
  if (locked == true){
    knockVal = analogRead(piezo);
    if(numberOfKnocks < 3 && knockVal > 0){
      if(checkForKnock(knockVal) == true){
      numberOfKnocks++;
      }
      Serial.print(3-numberOfKnocks);
      Serial.println(" more knocks to go");
    }
    if(numberOfKnocks >= 3){
      locked = false;
      numberOfKnocks = 0;
      myServo.write(0);
      delay(20);
      digitalWrite(green,HIGH);
      digitalWrite(red, LOW);
      Serial.println("The box is unlocked!");
    }
  }
}

//checking for the knock
boolean checkForKnock(int value){
  if(value > quietKnock && value < loudKnock){
    digitalWrite(yellow, HIGH);
    delay(50);
    digitalWrite(yellow,LOW);
    Serial.print("Valid knock of value ");
    Serial.println (value);
    return true;
  }
  else {
    Serial.print("Bad knock value ");
    Serial.println(value);
    return false;
  }
}
