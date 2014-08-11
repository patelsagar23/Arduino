//Constants for the LED and Potentiometer
const int green = 9;
const int red = 11;
const int blue= 10;
int const bluepot = A0;
int const greenpot = A1;
int const redpot = A2;
int redout;
int greenout;
int blueout;
int redmap;
int bluemap;
int greenmap;

void setup(){
  Serial.begin(9600);
  
  //Setting the Outputs
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(red,OUTPUT);
}

void loop(){
  
  //Reading the Values
  redout = analogRead(redpot);
  greenout = analogRead(greenpot);
  blueout = analogRead(bluepot);
  
  //Mapping the values to the LED
  redmap = map(redout, 0, 1023, 0, 255);
  greenmap = map(greenout, 0, 1023, 0, 255);
  bluemap = map(blueout, 0, 1023, 0, 255);
  
  //Sending the values to the LED
  analogWrite(red, redmap);
  analogWrite(green, greenmap);
  analogWrite(blue, bluemap);
  
  //Printing the vlaues to the serial monitor
  Serial.print("Red Value: ");
  Serial.print(redmap \t);
  Serial.print("Green Value: ");
  Serial.print(greenmap \t);
  Serial.print("Blue Value: ");
  Serial.println(bluemap);
}
  
