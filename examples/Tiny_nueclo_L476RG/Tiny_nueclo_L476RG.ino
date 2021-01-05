#include <Tinyfox.h>

#define btn   PC13 // boton usuario azul / blue user button
#define RXLED  PA5
#define rstPin PC12


//nucleo-64 STM32L476RG:

//HardwareSerial Serial2(USART2);
HardwareSerial Serial3(USART3);
Tiny<HardwareSerial,HardwareSerial> wisol(&Serial3,&Serial,rstPin,false);

void setup() {
  pinMode(btn,INPUT_PULLUP);
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  Serial.println("");
  Serial.println("boot");
  wisol.begin(9600);

  while(!Serial);  //comentar si usará una fuente de energía externa

 Serial.println("-Presione botón PC13-");
}

void loop() {
  
  if(digitalRead(btn)==0){

    digitalWrite(RXLED,LOW);
    Serial.println("Tx");
    wisol.RST();
    
    uint32_t valor =10;
    Serial.println(wisol.SEND(valor));
    
    //String valor_recibido = wisol.SEND_RCV(valor); //aproximandamente esperar 1 minuto    
    //Serial.println(valor_recibido); 
    
    digitalWrite(RXLED,HIGH);
    wisol.SLEEP();
    delay(3000);
    Serial.println("-Presione botón PC13-");
  }
  
}
