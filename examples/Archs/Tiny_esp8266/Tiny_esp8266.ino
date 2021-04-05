#include <Tinyfox.h>
#include <SoftwareSerial.h>

//esp8266
#define btn   D3 // este pin si tiene pull_up interno en el esp8266. no todos tienen  //no usar cualquier pin xk se cuelga!
#define RXLED  D4//este es el led del nodemcu

SoftwareSerial mySerial(D5,D6); // RX, TX//esp8266

Tiny<SoftwareSerial,HardwareSerial> wisol(&mySerial,&Serial,D7,false);//esp8266

void setup() {
  pinMode(btn,INPUT_PULLUP);
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  Serial.println("");
  Serial.println("boot");
  wisol.begin(9600);


 Serial.println("-Presione botón D3-");
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
    Serial.println("-Presione botón D3-");
  }
  
}
