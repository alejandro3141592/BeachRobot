//Codigo elaborado por Mike, Carlos, David, Alonso y Fausto


//Patas delanteras, canales 11 y 12. Patas traseras canales 6 y 7
#include "BTS7960.h"




const uint8_t motor1_pins[3] = { 2, 12, 13};  //Enable, Left_PWM, Right_PWM //RPWM3 EN PLACA
const uint8_t motor2_pins[3] = { 2, 18, 5 };  //Enable, Left_PWM, Right_PWM //RPWM6 EN PLACA
const uint8_t motor3_pins[3] = { 2, 17, 16 };  //Enable, Left_PWM, Right_PWM //RPWM7 EN PLACA
const uint8_t motor4_pins[3] = { 2, 4, 0 };  //Enable, Left_PWM, Right_PWM //RPWM8 EN PLACA

BTS7960 motorController1(motor1_pins[0], motor1_pins[1], motor1_pins[2]);
BTS7960 motorController2(motor2_pins[0], motor2_pins[1], motor2_pins[2]);
BTS7960 motorController3(motor3_pins[0], motor3_pins[1], motor3_pins[2]);
BTS7960 motorController4(motor4_pins[0], motor4_pins[1], motor4_pins[2]);


int velocidad = 255;

void setup() {
  Serial.begin(115200);
  motorController1.Enable();
  motorController2.Enable();
  motorController3.Enable();
  motorController4.Enable();

}

///************************CAMBIAR canales por variables************************

void loop() {

  adelante();
  delay(1000);

  atras();
  delay(1000);

  
  izquierda();
  delay(1000);

  
  derecha();
  delay(1000);

  
  alto();
  delay(1000);

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

