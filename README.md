# TINYFOX castellated Breakout board
## Modem SFM10R4 Wisol  Sigfox RC4
![](https://github.com/TECA-IOT/Tinyfox/blob/main/images/tinyfox.png )

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
 - BLuePill and other STM32 devices
 - many other boards should be compatible

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
