/*
 * you can test your code using 2 Serial ports, in this case, using double usb ports on an Arduino Due
 * using the native_usb_port/ SerialUSB/ ttyACM0 for the usual arduino debug
 * and opening the programming_port/ Serial/ ttyUSB0 with some Serial terminal to simulate the wisol module. 
 * being able to read the commands send to the module and to send your downlink strings to test the behavior of your code
 */
 
/*
 * puedes probar tu codigo usando dos puertos seriales, usano ambos puertos usb en un Arduino Due
 * usando el puesto usb_nativo/ SerialUSB/ ttyACM0 para el debing usual de arduino
 * y abriendo en programming_port/ Serial/ ttyUSB0 con alguna terminal serial para simular el modulo wisol.
 * siendo asi capaz de leer los comandos enviados al modulo y enviar tus propias respuestas de downlink para comprobar el comportamiento de tu codigo
 */


#include <Tinyfox.h>

#define btn   2
#define RXLED  13
//Due
Tiny<HardwareSerial,Serial_> wisol(&Serial,&SerialUSB,3,true);
//Tiny<HardwareSerial,Serial_> wisol(&SerialUSB,&Serial,3,true);//you could even use the virtual_com to simulate the module
//leonardo
//Tiny<HardwareSerial,Serial_> wisol(&Serial1,&Serial,12,true);// you could also use a Leonardo and an uart ttl to usb adaptor

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
    
    SerialUSB.println(a);
    SerialUSB.println(b);
    
    digitalWrite(RXLED,HIGH);
    wisol.SLEEP();
    delay(3000);
    SerialUSB.println("-Presione botón 2-");
  }
  
}
