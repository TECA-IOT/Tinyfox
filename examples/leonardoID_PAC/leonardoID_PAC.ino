/*

Extraer ID y PAC de modem wssfm10R4
Estos Valores son requeridos para la activacion del dispositivo en la red Sigfox

*/

#include <Tinyfox.h>
#define btn   13
#define RXLED  17
Tiny<HardwareSerial,Serial_> wisol(&Serial1,&Serial,12,true);//leonardo

void setup() {
  Serial.begin(115200);
  wisol.begin(9600);
  
  while(!Serial);

  delay(1000);

  Serial.print("ID: ");
  Serial.println(wisol.ID());
    
  Serial.print("PAC: ");
  Serial.println(wisol.PAC());

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
