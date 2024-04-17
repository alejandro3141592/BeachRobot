//Codigo elaborado por Mike, Carlos, David, Alonso y Fausto


//Patas delanteras, canales 11 y 12. Patas traseras canales 6 y 7
#include "BTS7960.h"

#include "sbus.h"

bfs::SbusRx sbus_rx(&Serial2, 2, 15, true, false);
bfs::SbusData data;

#define ALTO 0
#define DERECHA 1
#define IZQUIERDA 2
#define ADELANTE 3
#define ATRAS 4

const uint8_t motor1_pins[3] = { 2, 12, 13};  //Enable, Left_PWM, Right_PWM //RPWM3 EN PLACA
const uint8_t motor2_pins[3] = { 2, 18, 5 };  //Enable, Left_PWM, Right_PWM //RPWM6 EN PLACA
const uint8_t motor3_pins[3] = { 2, 17, 16 };  //Enable, Left_PWM, Right_PWM //RPWM7 EN PLACA
const uint8_t motor4_pins[3] = { 2, 4, 0 };  //Enable, Left_PWM, Right_PWM //RPWM8 EN PLACA

const uint8_t motor5_pins[3] = { 2, 32, 33};  //Enable, Left_PWM, Right_PWM //RPWM1 EN PLACA
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

int velocidad_max = 255;
int velocidad_actual = 0;

int steps_velocidad = 10;
int inc_velocidad = velocidad_max/steps_velocidad;
int velocidadPatita = 180;
int current_movement = ALTO;

int velocidad_inferior = velocidad_max - 70;
int velocidad_actual_inferior = 0;


hw_timer_t *timer = NULL;
volatile bool timerFlag = false;

void IRAM_ATTR onTimer() {

  if (velocidad_actual + inc_velocidad > velocidad_max){
    velocidad_actual = velocidad_max;
  }else{
    velocidad_actual = velocidad_actual + inc_velocidad;
  }

}


void setup() {
  Serial.begin(115200); // Quitar para que no interfiera con los pines 0 y 2
  motorController1.Enable();
  motorController2.Enable();
  motorController3.Enable();
  motorController4.Enable();
  sbus_rx.Begin();

    // Initialize timer
  timer = timerBegin(0, 80, true); // Timer 0, prescaler 80 (1 tick = 1 microsecond)
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 100000, true); // 0.1 seconds (100,000 microseconds)
  timerAlarmEnable(timer);

   
}

///************************CAMBIAR canales por variables************************

void loop() { 

  
  if (sbus_rx.Read()) {
    /* Grab the received data */
    data = sbus_rx.data();

    //Traccion
    if (data.ch[1]<1100 && data.ch[1]>900){
      if (data.ch[0]<1100 && data.ch[0]>900){
        detenerse();
        Serial.println("alto");
      }else if(data.ch[0]>1100){
        girar_derecha();
        Serial.println("derecha");
      }else{
        girar_izquierda();
        Serial.println("izquierda");
      }
    }else if(data.ch[1]>1100){
      retroceder();
      Serial.println("atras");
    }else{
      avanzar();
      Serial.println("adelante");
    }

    //Pata adelante derecha
    if(data.ch[10]<1100 && data.ch[10]>900){
      detenerPatita(motorControllerPatita1);
    } else if (data.ch[10]>1100){
      giroHorario(motorControllerPatita1);
    } else{
      giroAntiHorario(motorControllerPatita1);
    }

    //Pata adelante izquierda
    if(data.ch[11]<1100 && data.ch[11]>900){
      detenerPatita(motorControllerPatita2);
    } else if (data.ch[11]>1100){
      giroHorario(motorControllerPatita2);
    } else{
      giroAntiHorario(motorControllerPatita2);
    }

    //Pata atras derecha
    if(data.ch[5]<1100 && data.ch[5]>900){
      detenerPatita(motorControllerPatita3);
    } else if (data.ch[5]>1100){
      giroHorario(motorControllerPatita3);
    } else{
      giroAntiHorario(motorControllerPatita3);
    }

    //Pata atras izuierda
    if(data.ch[6]<1100 && data.ch[6]>900){
      detenerPatita(motorControllerPatita4);
    } else if (data.ch[6]>1100){
      giroHorario(motorControllerPatita4);
    } else{
      giroAntiHorario(motorControllerPatita4);
    }

  }

}

void avanzar() {
  if (current_movement != ADELANTE){
    current_movement = ADELANTE;
    velocidad_actual = 0;
    
  } 

  motorController1.TurnLeft(velocidad_actual);
  motorController2.TurnLeft(velocidad_actual);
  motorController3.TurnLeft(velocidad_actual);
  motorController4.TurnLeft(velocidad_actual);
}

void retroceder() {
    if (current_movement != ATRAS){
    current_movement = ATRAS;
    velocidad_actual = 0;
  } 

  motorController1.TurnRight(velocidad_actual);
  motorController2.TurnRight(velocidad_actual);
  motorController3.TurnRight(velocidad_actual);
  motorController4.TurnRight(velocidad_actual);
}

void girar_derecha() {
  if (current_movement != DERECHA){
    current_movement = DERECHA;
    velocidad_actual = 0;
    velocidad_actual_inferior = velocidad_actual -50;
    if (velocidad_actual_inferior<0){
      velocidad_actual_inferior = 0;
    }
  } 
  motorController1.TurnLeft(velocidad_actual);
  motorController2.TurnLeft(velocidad_actual_inferior);
  motorController3.TurnLeft(velocidad_actual);
  motorController4.TurnLeft(velocidad_actual_inferior);
}

void girar_izquierda() {
  if (current_movement != IZQUIERDA){
    current_movement = IZQUIERDA;
    velocidad_actual = 0;
    velocidad_actual_inferior = velocidad_actual -50;
    if (velocidad_actual_inferior<0){
      velocidad_actual_inferior = 0;
    }
  } 
  motorController1.TurnLeft(velocidad_actual_inferior);
  motorController2.TurnLeft(velocidad_actual);
  motorController3.TurnLeft(velocidad_actual_inferior);
  motorController4.TurnLeft(velocidad_actual);
}
void detenerse() {
  if (current_movement != ALTO){
    current_movement = ALTO;
    velocidad_actual = 0;
  } 
  motorController1.Stop();
  motorController2.Stop();
  motorController3.Stop();
  motorController4.Stop();
}

void giroHorario(BTS7960 controller){
  controller.TurnLeft(velocidadPatita);
}

void giroAntiHorario(BTS7960 controller){
  controller.TurnRight(velocidadPatita);
}

void detenerPatita(BTS7960 controller){
  controller.Stop();
}


