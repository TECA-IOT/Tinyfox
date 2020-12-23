/*
envio de datos de punto a punto en area local
point to point data transmision in local area
*/

#include <Tinyfox.h>
#define btn   13
#define RXLED  17
Tiny<HardwareSerial,Serial_> wisol(&Serial1,&Serial,12,true);//leonardo

void setup() {
  pinMode(btn,INPUT);
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  wisol.begin(9600);
  
  //while(!Serial);  //comentar si usará una fuente de energía externa

  delay(5000);
  Serial.println("-Presione botón 13-");
}

void loop() {
  
   if(digitalRead(btn)==0){
    
      digitalWrite(RXLED,LOW);
      wisol.RST();
      
      String id=wisol.ID();
      
      Serial.println(wisol.command("AT$SL="+id));
      
      digitalWrite(RXLED,HIGH);
      wisol.SLEEP();
      delay(3000);
      
      Serial.println("-Presione botón 13-");
   }
}
