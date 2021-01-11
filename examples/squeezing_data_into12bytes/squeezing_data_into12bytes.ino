/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.2

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem WSSFM10R4 la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

  este ejemplo necesita un sensor de humedad de suelo capacitivo con salida analogica.
  por ejemplo este de DF-robot o una similar https://wiki.dfrobot.com/Capacitive_Soil_Moisture_Sensor_SKU_SEN0193

  Para desempaquetar esta cadena de datos usted debe configuar un callback 
  personalizado en el backend de sigfox con  las variables correspondientes con las que 
  fueron declarados en este ejemplo.
*/

#include <Ufox.h>

#define btn   13
#define RXLED  17 

Ufox wisol;



void setup() {
 Serial.begin(115200);
 wisol.begin(9600);
 
 while (!Serial);  //comentar si usará una fuente de energía externa

 pinMode(RXLED,OUTPUT);
 pinMode(btn,INPUT);
 
Serial.println("-Presione botón 13-");
}

void loop() {

  if(digitalRead(btn)==0){
    
     wisol.RST(); 
     digitalWrite(RXLED,LOW);

     float air_humidity = 35.61;//i guess your library return a float
     int16_t air_humidity_16 = air_humidity*100; //if you need to keep those 2 decimanls multiply by 100 and convert to int16
     uint8_t air_humidity_u8  = air_humidity;  // but for just the air humidity you dont need to worry about the decimals. just use byte, enough to represent from 0 to 100 %
     
     float temperature = 22.68; //again i guess your library give you floats
     int16_t temp_16 = temperature*10; // normally one decimal its more than enough. you need a int with sign cuz temperatures can be negative.
     
     float brightness_lx = 471.85; //you cant have a negative ilumination. do you really need the decimals???
     uint16_t lx_u16 = brightness_lx ;
     
     float white_light = 155.46;
     uint16_t WL_u16 = white_light ; //if the white light its never over 255 you could even use uint8_t
     
     uint16_t als = 65458;
     
     uint16_t soil_moisture = 766; //if this is relative humidity use a conversion 
     //update this values to your sensor!!!
     const int AirValue = 0;   //the value returned by the sensor while its suspended in the air. minimal humidity. 0%
     const int WaterValue = 210;  //the value returned by the sensor while its sumerged in water. maximal humidity 100%
     int   h_r = map(soil_moisture, AirValue, WaterValue, 0, 100);     //do a convertion
     if( h_r<0   ) h_r=0; // make sure its within limits
     else if( h_r>100 ) h_r=100; // make sure its within limits

     uint8_t   humedad_relativa = 0;// from 0 to 100. one byte its enough
     humedad_relativa = h_r; //1 byte
     
     char buff[30]="";
     //format to hexadecimal
     sprintf(buff,"%02x%04x%04x%04x%04x%02x",air_humidity_u8,temp_16,lx_u16,WL_u16,als,humedad_relativa); // 10 bytes. you have 2 more bytes to spare
     //and to decode the message on the sigfox back end you need:
     //Custom payload config   humAIR::uint:8 temp::int:16 lx::uint:16 WL::uint:16 als::uint:16 humREL::uint:8

     Serial.print("Enviando: ");
     Serial.println(buff);
     
     Serial.println(wisol.SEND(buff)); //Envio de datos Sigfox
     
     digitalWrite(RXLED,HIGH);
     wisol.SLEEP(); 
     
     delay(3000);
     Serial.println("-Presione botón 13-");
  }
}
