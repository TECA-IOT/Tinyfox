#include <TinySigfox.h>
#include <TinySigfox.cpp>

#define btn   15
#define RXLED  13//este es el led del nodemcu. varia segun modelo

//usando Serial2 para el modulo wisol, Serial para debuging y pin 4 como reset.
Tiny<HardwareSerial,HardwareSerial> wisol(&Serial2,&Serial,4);//esp32

void setup() {
  pinMode(btn,INPUT_PULLUP);
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  Serial.println("");
  Serial.println("boot");
  wisol.begin(9600);
  //si desea cambiar la configuracion de Serial2 llame a Serial2.begin() inmeditamente despues de llamar a wisol.begin()
  //Serial2 permite configurar los pines para rx y tx
  //begin de serial2: begin(unsigned long baud, uint32_t config=SERIAL_8N1, int8_t rxPin=-1, int8_t txPin=-1, bool invert=false, unsigned long timeout_ms = 20000UL);
  //wisol.Modulo->begin(baud_ws,SERIAL_8N1,18,19, false, 20000UL);//usando pin Rx=18 y pin Tx=19
  //descomentar la linea anterior para cambiar los pines del Serial2

 Serial.println("-Presione botón en el pin 15-"); //pulsador entre pin 15 y tierra
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
    Serial.println("-Presione botón 15-");
  }
  
}
