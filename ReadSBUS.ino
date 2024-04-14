/*-----------Inclusión de Librerías-----------*/

#include "sbus.h"

bfs::SbusRx sbus_rx(&Serial2, 15,2,true, false);
bfs::SbusData data;
/*----------Declaración de Variables----------*/

bool sbusFlag = false;



void setup()
{
  Serial.begin(115200);        //Baudrate del puerto serie
  Serial.setTimeout(200);       //Timeout de lectura
  sbus_rx.Begin();

}



void loop () {
  if (sbus_rx.Read()) {
    /* Grab the received data */
    data = sbus_rx.data();
    /* Display the received data */
    for (int8_t i = 0; i < data.NUM_CH; i++) {
      Serial.print(data.ch[i]);
      Serial.print("\t");
    }
    Serial.println("\t");

  }

}
