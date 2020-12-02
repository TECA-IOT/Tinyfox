/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.5
Contibutor: Paul Portocarrero Hernandez
*/
#include "TinySigfox.h"
#include "Arduino.h"


template <class M,class DBG >
Tiny<M,DBG>::Tiny(M *modulo,DBG *debug, uint8_t _rst_ws, bool _dbg) {
  dbg = _dbg;
  pin_rst_wisol=_rst_ws;
  Modulo = modulo;
  Debug = debug;
}

template <class M,class DBG >
void Tiny<M,DBG>::debug(bool _dbg) {
  dbg = _dbg;
}

template <class M,class DBG >
void Tiny<M,DBG>::begin(uint16_t _baudio) {
  baudio = _baudio;
  pinMode(pin_rst_wisol, OUTPUT);
  Modulo->begin(baud_ws );
  digitalWrite(pin_rst_wisol, LOW);
  delay(100);
  digitalWrite(pin_rst_wisol, HIGH);
  delay(100);
  //if (dbg) {

  //  Debug->begin(baudio);
    // while (!Serial);
  //}
}

template <class M,class DBG >
String Tiny<M,DBG>::comand(String _cmd) {
  cmd = _cmd;
  if (dbg) {
     //UDebug->begin(baudio);
     //while (!Serial);
  }

  if (dbg){ Debug->print(ENV);Debug->println(cmd);}

 //Debug->println(cmd);
  long lastMsg = millis();
  caracter = 0x00;
  i = 0;
 for(int a=0;a<=40;a++){cadena_cad[a]= 0x00;}
  Modulo->println(cmd);
  do{
       long now = millis();
       if(now - lastMsg > 70000){
           break;
       }
      if(Modulo->available()){
         caracter = Modulo->read();
         cadena_cad[i] = caracter;
        i++;
      }
      else { delay(100); }//PANDA :3 //eso para k el RTos no se cuelge
   } while (caracter != 0x0A);
  delay(10);
  lastMsg = millis();
  do{
     long now = millis();
     if(now - lastMsg > 70000){
          break;
       }
     if(Modulo->available()){
        caracter = Modulo->read();
        cadena_cad[i] = caracter;
        i++;
    }
    else { delay(100); }//PANDA :3 //eso para k el RTos no se cuelge
   }while (caracter != 0x0A);
  cadena_cad[i] = 0x00;
  cadena_cad[i- 1] = 0x00;

  if (dbg) {Debug->print(RCV);Debug->println(cadena_cad); }
  caracter = 0x00;
  //Debug->println( strlen(cadena_cad));
  return cadena_cad;
}

template <class M,class DBG >
String Tiny<M,DBG>::comand2(String _cmd) {
  cmd = _cmd;
  if (dbg) {
    //Debug->begin(baudio);
   // while (!Serial);
  }
  if(dbg){ Debug->print(ENV);Debug->println(cmd);}

  caracter = 0x00;

  i = 0;
  uint32_t t = 0;
  for(int a=0;a<=30;a++){cadena_cad[a]= 0x00;}
  Modulo->println(cmd);
      Debug->println(cmd);
  long lastMsg = millis();
  
  
  while (true)
  {
    //ESP.wdtDisable();//PANDA :3
    //ESP.wdtEnable(WDTO_8S);
    //ESP.wdtFeed();
    //yield();
    //delay(1);//k carajos, aqui no; en el while!
    long now = millis();

    if(Modulo->available()) {
       caracter = Modulo->read();
       if(caracter == 0x0D)caracter = ' ';
       if(caracter == 0x0A)caracter = ' ';
       cadena_cad[i] = caracter;
          //Debug->print(caracter);
       i++;
    }
    else { delay(100); }//PANDA :3 //eso para k el RTos no se cuelge
    if (now - lastMsg > 70000) {

        //Debug->println("salio");
        delay(10);
      break;
    }
    if(i==32){
      if(cadena_cad[0]=='O') break;
    }
    if(i==37) break;

  }
  //Debug->println(t);
  //Debug->println(i);
  if (i == 32) {
    cadena_cad[0] = ' ';
    cadena_cad[1] = ' ';
    cadena_cad[2] = ' ';
    char cadena_cad2[35];
    int c = 0;
    for ( c = 0; c <= i - 7; c++) {
      cadena_cad2[c] = cadena_cad[c + 7];
    }
    for ( c = 0; c < sizeof(cadena_cad); c++) {
      cadena_cad[c] = 0x00;
    }

 int k=0,j=0;
 while (cadena_cad2[k]!='\0') 
 {
  if(cadena_cad2[k]!=' ')
  {
   cadena_cad[j]=cadena_cad2[k];
   j++;
  }
  k++;
 }
    //Debug->println(cadena_cad2);
   // Debug->println(cadena_cad);
  }
    //delay(100);
    if (dbg) {Debug->print(RCV);Debug->println(cadena_cad);} 
    caracter = 0x00;
    return String(cadena_cad);
  }

template <class M,class DBG >
  String Tiny<M,DBG>::ID() {
    return Tiny<M,DBG>::comand(ATS + "I=10");
  }

template <class M,class DBG >
  String Tiny<M,DBG>::PAC() {
    return Tiny<M,DBG>::comand(ATS + "I=11");
  }

template <class M,class DBG >
  uint16_t  Tiny<M,DBG>::TEMP() {
    return String(Tiny<M,DBG>::comand(ATS + "T?")).toInt();
  }

template <class M,class DBG >
  uint16_t  Tiny<M,DBG>::VOLT() {

    return  String(Tiny<M,DBG>::comand(ATS + "V?")).toInt();
  }

template <class M,class DBG >
  void Tiny<M,DBG>::RST() {
    digitalWrite(pin_rst_wisol, LOW);
    delay(100);
    digitalWrite(pin_rst_wisol, HIGH);
    delay(100);
  }

template <class M,class DBG >
  String Tiny<M,DBG>::SLEEP() {
    return Tiny<M,DBG>::comand(ATS + "P=2");
  }

template <class M,class DBG >
  String Tiny<M,DBG>::SEND(uint32_t _dataint) {
    dataint = _dataint;
    Tiny<M,DBG>::comand(ATS + GI);
    Tiny<M,DBG>::comand(ATS + RC);
    char cadena_cad[15] = "";
    sprintf(cadena_cad, "SF=%08lx", dataint);
    return Tiny<M,DBG>::comand(ATS + cadena_cad);
  }
  
  template <class M,class DBG >
 String Tiny<M,DBG>::SEND(String _datastr) {
    datastr = _datastr;
    if (datastr.length() > 24) return ("error");
    if (datastr.length() % 2 != 0)datastr = "0" + datastr;
    Tiny<M,DBG>::comand(ATS + GI);
    Tiny<M,DBG>::comand(ATS + RC);
    return Tiny<M,DBG>::comand(ATS + "SF=" + datastr);
  }
  
  template <class M,class DBG >
  String Tiny<M,DBG>::SEND_RCV(uint32_t _dataint_rcv) {
    dataint_rcv = _dataint_rcv;
    Tiny<M,DBG>::comand(ATS + GI);
    Tiny<M,DBG>::comand(ATS + RC);
    char cadena_cad[20] = "";
    sprintf(cadena_cad, "SF=%08lx,1", dataint_rcv);
    return Tiny<M,DBG>::comand2(ATS + cadena_cad);
  }

template <class M,class DBG >
   String Tiny<M,DBG>::SEND_RCV(String _datastr_rcv) {
    datastr_rcv = _datastr_rcv;
    if (datastr_rcv.length() > 24) return ("error");
    if (datastr_rcv.length() % 2 != 0)datastr_rcv = "0" + datastr_rcv;
    Tiny<M,DBG>::comand(ATS + GI);
    Tiny<M,DBG>::comand(ATS + RC);
    char cadena_cad[20] = "";
    return Tiny<M,DBG>::comand2(ATS + "SF=" + datastr_rcv+",1");
  }
