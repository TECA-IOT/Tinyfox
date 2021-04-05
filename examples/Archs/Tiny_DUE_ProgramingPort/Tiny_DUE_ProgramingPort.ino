#include <Tinyfox.h>

#define btn   2
#define RXLED  13

Tiny<HardwareSerial,HardwareSerial> wisol(&Serial2,&Serial,3,true);
//Tiny<HardwareSerial,HardwareSerial> wisol(&Serial1,&Serial,3,true);

void setup() {
  pinMode(btn,INPUT_PULLUP);
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  //while(!Serial);  //comentar si usará una fuente de energía externa
  Serial.println("");
  Serial.println("boot");
  wisol.begin(9600);

  

 Serial.println("-Presione botón 2-");
}

void loop() {
  
  if(digitalRead(btn)==0){

    digitalWrite(RXLED,LOW);
    Serial.println("Tx");
    Serial.flush();
    wisol.RST();
    
    uint32_t valor = 10;
    Serial.println(wisol.SEND(valor));
    
    //String valor_recibido = wisol.SEND_RCV(valor); //aproximandamente esperar 1 minuto    
    //Serial.println(valor_recibido); 
    
    digitalWrite(RXLED,HIGH);
    wisol.SLEEP();
    delay(3000);
    Serial.println("-Presione botón 2-");
  }
  
}
