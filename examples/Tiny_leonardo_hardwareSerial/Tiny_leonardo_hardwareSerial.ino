#include <Tinyfox.h>

//leo
#define btn   2
#define RXLED  13

//Tiny<HardwareSerial,Stream> wisol(&Serial1,&Serial,12,false);//leonardo //no usar este
Tiny<HardwareSerial,Serial_> wisol(&Serial1,&Serial,12,false);//leonardo


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
