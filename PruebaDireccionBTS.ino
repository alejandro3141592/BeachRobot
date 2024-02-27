// Control de motor con BTS7960

int L_EN = 4;
int R_EN = 4;
int L_PWM = 6;
int R_PWM = 5;

void setup() {
 pinMode(L_EN, OUTPUT);
 pinMode(R_EN, OUTPUT);
 pinMode(L_PWM, OUTPUT);
 pinMode(R_PWM, OUTPUT); 

 // Activa la salida
 digitalWrite(R_EN, HIGH);
 digitalWrite(L_EN, HIGH);
}

void loop() {

   int velocidad = 158; // Valor entre 0 y 254

   // Giro derecha
   analogWrite(R_PWM, velocidad);
   analogWrite(L_PWM, 0);

   delay(5000); // Esperamos 1 segundo

   // Giro izquierda
   analogWrite(R_PWM, 0);
   analogWrite(L_PWM, velocidad);   
 
   delay(5000); // Esperamos 1 segundo
}