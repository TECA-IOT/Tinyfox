#include <Tinyfox.h>

//leo
#define btn   2
#define RXLED  13 

//Tiny<HardwareSerial,Stream> wisol(&Serial1,&Serial,12,true);//leonardo //no usar este
Tiny<HardwareSerial,Serial_> wisol(&Serial1,&Serial,12,true);//leonardo


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

    uint32_t distancia = 23435; //mm
    uint16_t bateria = 3124;    //mV
    byte estados = 0b00110101;  //8 switches
    boolean dbg = true;         //debug 
    int angulo = -45;           //enteros / integer
    
    

    char msg[35];
    for(int i=0;i<35;i++){    msg[i] = 0;    }
    snprintf (msg, 35, "AT$SF=%08lx%04x%02x02x%04x\n", distancia, bateria, estados, dbg, angulo);
    
    String valor_recibido = wisol.SEND_RCV( String(msg) ); //aproximandamente esperar 1 minuto    
    
    uint8_t  a = int( valor_recibido.substring(0,2), HEX);//primeros 2 digitos hex. fisrt 2 hex digitis
    uint16_t b = int( valor_recibido.substring(2,6), HEX);//siguientes 4 digitos hex. next 4 hex digitis
    
    Serial.println(a);
    Serial.println(b);
    
    digitalWrite(RXLED,HIGH);
    wisol.SLEEP();
    delay(3000);
    Serial.println("-Presione botón 2-");
  }
  
}
