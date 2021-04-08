# TINYFOX castellated Breakout board
## Modem SFM10R4 Wisol  Sigfox RC4
![](https://github.com/TECA-IOT/Tinyfox/blob/main/images/tinyfox.png )

## Visita la Wiki de TINYFOX: Documentación y ejemplos avanzados
`<link>` : <https://github.com/TECA-IOT/Tinyfox/wiki>

## Cómo funciona el constructor de la libreria Tinyfox para arduino 
- Library for radio wisol - seonji SFM10R2D, SFM10R4, SFM10R1, SFM10R3

`<link>` : <https://github.com/TECA-IOT/Tinyfox/wiki/como-funciona-el-constructor-(Arduino)>

## librería fritzing .fzpz Tinyfox:
`<link>` : <https://github.com/TECA-IOT/Tinyfox/wiki/Librer%C3%ADa-Tinyfox-para-Fritzing>


## Caracteristicas

- Diseño simple y robusto para comunicaciones IoT de baja potencia. 
- Modem WISSOL SFM10R4 permite conexiones a red Sigfox para region RC4.
- Control mediante comando AT.
- Antena Helicoidal integrada.
- Conector U.FL a SMA para conexion de antenas externas (desoldar previamente antena helicoidal para su uso).
- Soporte para Uplink y Downlink 
- Ideal para aplicaciones con microcontroladores externos, Pic, Arduino, Arm, Raspberry Pi, etc. Comunicacion via  puerto UART Serial RX-TX a 9600 baudios, niveles de tension desde 2.5V a 4.2V. funcionamiento tipico de 3.3v
- Puede ser alimentado directamente con 2 Baterias Alcalinas, o baterias de litio 3.7V 1S.

## Caracteristicas Electricas

| Descripcion | Unidad                    |
| ------------- | ------------------------------ |
| Voltaje Minimo  Vin |  2.5 VDC    |  
| Voltaje Maximo  Vin |  3.8 VDC    |  
| Voltaje  de operacion típica |  3.3 VDC    | 
| Consumo en modo Deep Sleep   | 2.5uA     |
| Potencia TX   | 23 dBm     |
| Sensibilidad  Rx   | -129 dBm     |
| Antena    | helicoidad 3 dBi      |
| Frec. Uplink     | 920.8 MHz      |
| Frec. Downlink     | 922.3 MHz      |

## Pinout

| Pin| Descripcion                    |
| ------------- | ------------------------------ |
| G |  GND    |  
| Rx  |  Rx WSSFM11R4AT    | 
| Tx   |  Tx WSSFM11R4AT     |
| Rst   | Reset WSSFM11R4AT    |
| +3V   | VIN, Voltaje de entrada [2.7 - 3.6]Voltios    |
| G   | GND     |

### Pinout castellated
Tiny Sigfox puede ser soldado directamente a una PCB, los orificios pasantes con ruptura permite la aplicacion de soldadura de estaño en los  bordes de manera sencilla

| Pin| Descripcion                    |
| --------------  | ------------------------------ |
| G   |    GND    |  
| Radio Led  |  Rx WSSFM11R4AT     | 
| GPIO 0     |  I/O ADC DAC     |
| GPIO 1     |  I/O ADC     |
| GPIO 4     |  I/O DAC     |
| RX-LED     |  RX actividad    |
| TX-LED     |  Tx actividad    |


# Tinyfox library
## Arduino Client for Wisol WSSFM10R4.
This library provides a simple way to make use of Wisol radios, sends uplink and wait for and parse downlink messages

## Examples

The library comes with a number of example sketches for different architectures. See File > Examples > Tinyfox within the Arduino application.


## Limitations



## Compatible Hardware

The library uses the Arduino Ethernet Client api for interacting with the
underlying network hardware. This means it Just Works with a growing number of
boards and shields, including:

 - Arduino UNO and other ATmega328p microcontrollers
 - Arduino Due
 - Arduino Mega – via hardwareserial and SoftwareSerial
 - Arduino Leonardo – via hardwareserial and SoftwareSerial
 - ESP8266 – with the help of a softwareSerial
 - ESP32   – via Serial2 (Tx and Rx pins are configurable)
 - Nucleo 64 STM32L476RG
 - BluePill and other STM32 devices
 - many other boards should be compatible

## Primer Sketch | leer ID y PAC | primer Uplink

### Constructor
en primer lugar necesitamos elejir que microcontrolador usaremos. en este ejemplo propondremos el Arduino UNO y el Leonardo ya que son los mas comunes.
luego debemos declarar un objeto del tipo Tiny para comunicanos con el modulo Tinyfox.
* para el UNO declaramos un objeto SoftwareSerial y un Tiny `SoftwareSerial mySerial(10, 11); // RX, TX` `Tiny<SoftwareSerial,HardwareSerial> wisol(&mySerial,&Serial,3,true);` . 
* para el arduino leonardo podemos usar el hardware serial que tiene disponible en los pines 0 y 1. `Tiny<HardwareSerial,Serial_> wisol(&Serial1,&Serial,12,false);//leonardo` 

![](https://github.com/TECA-IOT/Tinyfox/blob/main/images/uno_tinyfox_bb.png){:height="36px" width="36px"}.

![](https://github.com/TECA-IOT/Tinyfox/blob/main/images/Leonardo_tinyfox_bb.png){:height="360px" width="360px"}.

cuando llamamos al constructos de Tiny debemos especificar que tipo de puerto serial se usara para la comunicacion con el Tinyfox y el puerto de debuging entre signos de mayor y menor <>

en le caso de UNO usarmos un <SoftwareSerial,...> para la comunicacion con le modulo y un HarwareSerial para el debug <...,HardwareSerial>  . este harware serial es el que esta conectado al adaptaor USB interno del UNO

en el caso del Leonardo este posee comunicacion USB nativa, usa un Serial virtual sobre el porotcolo USB. en el framework de arduino este tipo de serial esta declaraddo como Serial_, y el Hardware serial no tiene ningun adaptador, esta conectao directamenta a los pines 1 y 0. por lo tanto el contructor queda asi Tiny<HardwareSerial,Serial_>

para mas detalles y ejemplos con diferentes arquitecturas lea los ejemplos en examples>Archs>... y visite el wiki en https://github.com/TECA-IOT/Tinyfox/wiki/como-funciona-el-constructor-(Arduino)

### setup | ID PAC
```javascript
#define btn   2 //este pin necesita un boton a tierra
#define RXLED  13 //display

void setup() {

  pinMode(btn,INPUT_PULLUP); //activa el pullup interno, necesario para etectar cuando el boton es presionado
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  wisol.begin(9600); //inicializa la comunicacion serial con le modulo tinyfox
  
  while(!Serial); //hace que el microcontrolador espere a que inicie la comunicacion serial antes de empezar la ejecucion del programa
  //si el dispositivo va a funcionar con bateria hay que quitar esta linea
  //esta linea solo es relevante en microcontroladores con USB nativo. en el Anduino UNO no tendra ningun efecto.
  
  delay(1000);

  Serial.print("ID: ");
  Serial.println(wisol.ID()); // solicita el ID al dispositivo. devolvera una cadena en hexadecimal
    
  Serial.print("PAC: ");
  Serial.println(wisol.PAC());  // solicita el PAC de fabrica al dispositivo. devolvera una cadena en hexadecimal
  
}
```
### loop | Uplink

```javascript
void loop() {
  
  if(digitalRead(btn)==0){ //lee continuamente el estado del boton, cuando sea presionado, pin pasara a estado false o 0

    digitalWrite(RXLED,LOW);
    Serial.println("Tx");
    wisol.RST(); // se pulsa el reset para despertar al dispositivo del modo deep sleep
    
    uint32_t valor = 10;
    Serial.println(wisol.SEND(valor)); //Uplink. transmite un valor a la plataforma sigfox e imprime el resultado
    
    //String valor_recibido = wisol.SEND_RCV(valor); //aproximandamente esperar 1 minuto    
    //Serial.println(valor_recibido); 
    
    digitalWrite(RXLED,HIGH);
    wisol.SLEEP(); //pone el modulo a dormir /deep sleep
    delay(3000);
    Serial.println("-Presione botón 2-");
  }
  
}
```

# API

_Constructor_
* **`Tiny<M,DBG>::Tiny(M *modulo,DBG *debug, uint8_t _rst_ws, bool _dbg)`** : this library make use of class templates to be able to work with many diferente types of Serial devices. it could use USART, UART, software serials and virtual serial ports for debuging and controlling the Wisol Module.
at declaration its necessary to especify the type of serial object that will be used for communication with the module and for debug in that order.

for example in using and Arduino Leonardo board, with the virtual serial port(USB) for debuging and the hadwareSerial on pins 0 and 1 for communication with the wisol module you need to declare:
`Tiny<HardwareSerial,Serial_> wisol(&Serial1,&Serial,12,true);`
or using a softwareSerial for the module:
`Tiny<SoftwareSerial,Serial_> wisol(&mySerial,&Serial,3,true);`
or even, just as an example, using the software serial for the moduel and the hardware serial for debug, although this is unpractical:
`Tiny<SoftwareSerial,HardwareSerial> wisol(&mySerial,&Serial1,3,true);`
more even, the other way around: softwareSerial for debug and hardwareSerial for the module:
`Tiny<HardwareSerial,SoftwareSerial> wisol(&Serial1,&mySerial,3,true);`
many examples are included.

_debug mode_
* **`void debug(bool _dbg)`** : enable or disable the debug prints at any time.


_Tiny begin_
* **`void begin(uint16_t _baudio)`** the default baud rate for the wisol its 9600. reset will be pulsed.


_sending commands_
* **`String command(String _cmd)`** send a command to the module and wait for an answer up to 7 seconds. mostly for intrenal use.

_sending commands and getting downlinks_
* **`String command2(String _cmd)`** send a command to the module and wait for an answer up to 70 seconds. mostly for intrenal use in dowlinks.

_get ID number_
* **`String ID()`** return the module's ID.

_get PAC number_
* **`String PAC()`** return the module's PAC.

_get temperature_
* **`uint16_t TEMP()`** return the module's temperature in celcius.

_get module's supply voltage_
* **`uint16_t VOLT()`** return the module's supply voltage in mV.

_Reset the module_
* **`void RST()`** reboot or wakeup the module by pulsing the reset pin.

_put in deep sleep_
* **`void SLEEP()`** put the module in deep sleep mode to save energy. 7uA are drawn in this mode. use `void RST()` to wake it up again.

_send Uplinks_
* **`String SEND(uint32_t _dataint)`** recive an 32 bits integer, format it to hexadecimal and transmit it to the sigfox plataform.
* **`String SEND(String _datastr)`** recive an hexadecimal formatted string (up to 12 bytes) and transmit it to the sigfox plataform.

_query for Downlinks_
* **`String SEND_RCV(uint32_t _dataint)`** recive an 32 bits integer, format it to hexadecimal and transmit it to the sigfox plataform, then wait up to 70 seconds for a downlink answer and return it as a hexadecima String.
* **`String SEND_RCV(String _datastr)`** recive an hexadecimal formatted string (up to 12 bytes) and transmit it to the sigfox plataform, then wait up to 70 seconds for a downlink answer and return it as a hexadecima String.

## License

This code is released under the Apache 2.0 License.
