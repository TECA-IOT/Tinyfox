/*
recepcion de datos de punto a punto en area local
point to point data reception in local area
*/

#include <Tinyfox.h>

//leo
#define btn   13
#define RXLED  17

Tiny<HardwareSerial,Serial_> wisol(&Serial1,&Serial,12,true);//leonardo

void setup() {
  pinMode(btn,INPUT);
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  wisol.begin(9600);
  
  while(!Serial);  //comentar si usará una fuente de energía externa
  Serial.println("escuchando");

}

void loop() {
  
   String rec = wisol.command("AT$RL");  
   if(rec[0])  {//si se capturo algo, imprimirlo, sino seguir solicitando datos
    
   Serial.print("recibido: ");
   Serial.println(rec);
    
   }
      
}
