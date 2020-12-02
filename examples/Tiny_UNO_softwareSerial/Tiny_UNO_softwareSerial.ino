//para todas las tarjetas basadas en atmega328p: UNO, Micro, Nano
//for boards based on atmega328p: UNO, Micro, Nano
#include <Tinyfox.h>
#include <SoftwareSerial.h>

/*
 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 */

#define btn   2
#define RXLED  13

SoftwareSerial mySerial(10, 11); // RX, TX

Tiny<SoftwareSerial,HardwareSerial> wisol(&mySerial,&Serial,3,true);

void setup() {
  pinMode(btn,INPUT_PULLUP);
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  Serial.println("");
  Serial.println("boot");
  wisol.begin(9600);

  while(!Serial);  //comentar si usará una fuente de energía externa

 Serial.println("-Presione botón 2-");
}

void loop() {
  
  if(digitalRead(btn)==0){

    digitalWrite(RXLED,LOW);
    Serial.println("Tx");
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
