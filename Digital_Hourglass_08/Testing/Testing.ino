int led = 2;

void setup(){
  for(int x = 2;x<8;x++){
    pinMode(x,OUTPUT);
  }
}

void loop(){
  /*  digitalWrite(led,HIGH);
   delay(500);
   digitalWrite(led,LOW);
   led ++;
   if(led == 8){
   led = 2;
   }
   */  for(int x = 2;x<8;x++){
    digitalWrite(x,HIGH);
    delay(250);
    digitalWrite(x,LOW);
  }
}


