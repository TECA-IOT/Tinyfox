#include <Tinyfox.h>

#define btn   PA4
#define RXLED  PC13


//bluepill f103c8:
HardwareSerial Serial2(USART2);
HardwareSerial Serial3(USART3);
Tiny<HardwareSerial,HardwareSerial> wisol(&Serial2,&Serial3,PA1,false);

void setup() {
  pinMode(btn,INPUT_PULLUP);
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  Serial.println("");
  Serial.println("boot");
  wisol.begin(9600);

  while(!Serial);  //comentar si usará una fuente de energía externa

 Serial.println("-Presione botón PA4-");
}

void loop() {
  
  if(digitalRead(btn)==0){

    digitalWrite(RXLED,LOW);
    Serial.println("Tx");
    wisol.RST();
    
    uint32_t valor =10;
    //Serial.println(wisol.SEND(valor));
    
    String valor_recibido = wisol.SEND_RCV(valor); //aproximandamente esperar 1 minuto    
    Serial.println(valor_recibido); 
    
    digitalWrite(RXLED,HIGH);
    wisol.SLEEP();
    delay(3000);
    Serial.println("-Presione botón PA4-");
  }
  
}
