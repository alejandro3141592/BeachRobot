//Codigo elaborado por Mike, Carlos, David, Alonso y Fausto


//Patas delanteras, canales 11 y 12. Patas traseras canales 6 y 7
#include "BTS7960.h"

#include "sbus.h"

bfs::SbusRx sbus_rx(&Serial2, 15, 2, true, false);
bfs::SbusData data;


int incomingByte;

const uint8_t motor1_pins[3] = { 2, 12, 13 };  //Enable, Left_PWM, Right_PWM //RPWM3 EN PLACA
const uint8_t motor2_pins[3] = { 2, 18, 5 };   //Enable, Left_PWM, Right_PWM //RPWM6 EN PLACA
const uint8_t motor3_pins[3] = { 2, 17, 16 };  //Enable, Left_PWM, Right_PWM //RPWM7 EN PLACA
const uint8_t motor4_pins[3] = { 2, 4, 0 };    //Enable, Left_PWM, Right_PWM //RPWM8 EN PLACA

const uint8_t motor5_pins[3] = { 2, 32, 33 };  //Enable, Left_PWM, Right_PWM //RPWM1 EN PLACA
const uint8_t motor6_pins[3] = { 2, 26, 27 };  //Enable, Left_PWM, Right_PWM //RPWM2 EN PLACA
const uint8_t motor7_pins[3] = { 2, 23, 22 };  //Enable, Left_PWM, Right_PWM //RPWM4 EN PLACA
const uint8_t motor8_pins[3] = { 2, 21, 19 };  //Enable, Left_PWM, Right_PWM //RPWM5 EN PLACA

BTS7960 motorController1(motor1_pins[0], motor1_pins[1], motor1_pins[2]);
BTS7960 motorController2(motor2_pins[0], motor2_pins[1], motor2_pins[2]);
BTS7960 motorController3(motor3_pins[0], motor3_pins[1], motor3_pins[2]);
BTS7960 motorController4(motor4_pins[0], motor4_pins[1], motor4_pins[2]);


BTS7960 motorControllerPatita1(motor5_pins[0], motor5_pins[1], motor5_pins[2]);
BTS7960 motorControllerPatita2(motor6_pins[0], motor6_pins[1], motor6_pins[2]);
BTS7960 motorControllerPatita3(motor7_pins[0], motor7_pins[1], motor7_pins[2]);
BTS7960 motorControllerPatita4(motor8_pins[0], motor8_pins[1], motor8_pins[2]);

int velocidad = 255;
int velocidadPatita = 180;
void setup() {
  Serial.begin(115200);
  motorController1.Enable();
  motorController2.Enable();
  motorController3.Enable();
  motorController4.Enable();
  sbus_rx.Begin();
}

///************************CAMBIAR canales por variables************************

void loop() {

  if (Serial.available() > 0) {
    /* Grab the received data */
    incomingByte = Serial.read();  //Leer puerto serie hasta timeout
    if (incomingByte < 10){
      detenerPatita(motorControllerPatita1);
      detenerPatita(motorControllerPatita2);
      detenerPatita(motorControllerPatita3);
      detenerPatita(motorControllerPatita4);
    }else{
      alto();
    }

    //Traccion
    if (incomingByte == 0){
      alto();
    } else if (incomingByte == 1){
      adelante();
    }else if (incomingByte == 2){
      atras();
    }else if (incomingByte == 3){
      izquierda();
    }else if (incomingByte == 4){
      derecha();
      
    //Sentido Horario  
    }else if (incomingByte == 10){
      giroSentidoHorario(motorControllerPatita1);
    } else if (incomingByte == 11){
      giroSentidoHorario(motorControllerPatita2);
    }else if (incomingByte == 12){
      giroSentidoHorario(motorControllerPatita3);
    }else if (incomingByte == 13){
      giroSentidoHorario(motorControllerPatita4);
    }
    
    //Sentido AntiHorario
    else if (incomingByte == 20){
      giroSentidoAntiHorario(motorControllerPatita1);
    }else if (incomingByte == 21){
      giroSentidoAntiHorario(motorControllerPatita2);
    }else if (incomingByte == 22){
      giroSentidoAntiHorario(motorControllerPatita3);
    }else if (incomingByte == 23){
      giroSentidoAntiHorario(motorControllerPatita4);
    }

  }
}

void adelante() {

  motorController1.TurnLeft(velocidad);
  motorController2.TurnLeft(velocidad);
  motorController3.TurnLeft(velocidad);
  motorController4.TurnLeft(velocidad);
}

void atras() {

  motorController1.TurnRight(velocidad);
  motorController2.TurnRight(velocidad);
  motorController3.TurnRight(velocidad);
  motorController4.TurnRight(velocidad);
}

void derecha() {

  motorController1.TurnLeft(velocidad);
  motorController2.TurnRight(velocidad);
  motorController3.TurnLeft(velocidad);
  motorController4.TurnRight(velocidad);
}

void izquierda() {

  motorController1.TurnRight(velocidad);
  motorController2.TurnLeft(velocidad);
  motorController3.TurnRight(velocidad);
  motorController4.TurnLeft(velocidad);
}
void alto() {

  motorController1.Stop();
  motorController2.Stop();
  motorController3.Stop();
  motorController4.Stop();
}

void giroSentidoHorario(BTS7960 controller) {
  controller.TurnLeft(velocidadPatita);
}

void giroSentidoAntiHorario(BTS7960 controller) {
  controller.TurnRight(velocidadPatita);
}

void detenerPatita(BTS7960 controller) {
  controller.Stop();
}
