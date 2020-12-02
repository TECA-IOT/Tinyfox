/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.2

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem WSSFM10R4 la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

 Envío de un valor numérico simple.
 
 Los mensajes tipo entero son convertidos a hexagesimal automaticamente por el 
 metodo ".SEND()" . Soporta  variables tipo uint32_t.
 
 Para el envío de mensajes personalizados puede definir una variable String o char
 array, usted deberá dar el formato hexagesimal adecuado. puede hacer uso de la funcion 
 "sprintf()" para el formateo de datos a valores hexagesimales y entregarlo al método
 ".SEND()" para el envío.
*/

#include <Tinyfox.h>
#include <SoftwareSerial.h>

#define btn   13
#define RXLED  17 
//SoftwareSerial mySerial(10, 14); // RX, TX//leonardo
SoftwareSerial mySerial(14,12); // RX, TX//esp8266


//Ufox<HardwareSerial,HardwareSerial> wisol(&Serial2,&Serial,4);//esp32
Ufox<SoftwareSerial,HardwareSerial> wisol(&mySerial,&Serial,4,false);//esp8266
//Ufox<HardwareSerial,Stream> wisol(&Serial1,&Serial,12,false);//leonardo //no usar este
//Ufox<HardwareSerial,Serial_> wisol(&Serial1,&Serial,12,false);//leonardo
//Ufox<SoftwareSerial,Serial_> wisol(&mySerial,&Serial,3,true);//leonardo
//Ufox<SoftwareSerial,Serial_> wisol(&mySerial,&Serial);//leonardo

//bluepill f103c8:
//HardwareSerial Serial2(USART2);
//HardwareSerial Serial3(USART3);
//Ufox<HardwareSerial,HardwareSerial> wisol(&Serial2,&Serial3,12,false);//leonardo

void setup() {
  pinMode(btn,INPUT_PULLUP);
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  wisol.begin(9600);

  while(!Serial);  //comentar si usará una fuente de energía externa

 Serial.println("-Presione botón 13-");
}

void loop() {
  
  if(digitalRead(btn)==0){

    digitalWrite(RXLED,LOW);
    wisol.RST();
    
    uint32_t valor =10;
    Serial.println(wisol.SEND(valor));

    //String valor2 ="10";
    //Serial.println(wisol.SEND(valor2));
    
    digitalWrite(RXLED,HIGH);
    wisol.SLEEP();
    delay(3000);
    Serial.println("-Presione botón 13-");
  }
  
}
