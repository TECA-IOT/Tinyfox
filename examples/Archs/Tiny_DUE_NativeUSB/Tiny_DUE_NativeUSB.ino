#include <Tinyfox.h>

#define btn   2
#define RXLED  13

Tiny<HardwareSerial,Serial_> wisol(&Serial2,&SerialUSB,3,true);
//Tiny<HardwareSerial,Serial_> wisol(&Serial1,&SerialUSB,3,true);

void setup() {
  pinMode(btn,INPUT_PULLUP);
  pinMode(RXLED,OUTPUT);
  
  SerialUSB.begin(115200);
  while(!SerialUSB);  //comentar si usará una fuente de energía externa
  SerialUSB.println("");
  SerialUSB.println("boot");
  wisol.begin(9600);

  

 SerialUSB.println("-Presione botón 2-");
}

void loop() {
  
  if(digitalRead(btn)==0){

    digitalWrite(RXLED,LOW);
    SerialUSB.println("Tx");
    wisol.RST();
    
    uint32_t valor = 10;
    SerialUSB.println(wisol.SEND(valor));
    
    //String valor_recibido = wisol.SEND_RCV(valor); //aproximandamente esperar 1 minuto    
    //Serial.println(valor_recibido); 
    
    digitalWrite(RXLED,HIGH);
    wisol.SLEEP();
    delay(3000);
    SerialUSB.println("-Presione botón 2-");
  }
  
}
