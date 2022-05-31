#include <Servo.h>
Servo servo1;
int Trig=2;
int Echo=3;
float duracion;
//-----------Entrada sensor, x de referencia
float x;
float xg;
float k = 20;
//-----------Estados de entrada
float CE, CN, L;
//-----------Estados de error
float P, C, N;
//-----------Hecho
float AP;
//-----------Centroides
float cderecha = 89, ccentro = 98, cizquierda = 105;
float k1, k2, k3, k4, k5, k6, k7;
float a1, a2, a3, a4, a5, a6, a7, as;
int Y;

void setup() {
  Serial.begin(9600); 
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  servo1.attach(4);
}

void loop() {
  digitalWrite(Trig,HIGH);
  delay(1);
  digitalWrite(Trig,LOW);
  duracion = pulseIn(Echo,HIGH);
  x = duracion/58.2;
  if (x <= 30 && x >= 10){ 
 delay(10); // demora proporcional a la distancia
 }

 if (x>=40){ 
  x = 20;
 }
 
 
//----Cerca
 CE = exp((-0.03)*sq(x));  
//----Centrado
  CN = exp((-0.03)*sq(x-20));  
//----Lejos
  L = exp((-0.03)*sq(x-40));
//------------Error
  xg = 20-x;
//----Positivo
  P = exp((-0.03)*sq(xg-20));
//----Medio
  C = exp((-0.03)*sq(xg-0));
//----Negativo
  N = exp((-0.03)*sq(xg-(-20)));
//------------A'
  AP = exp((-0.02)*sq(x-20));
//------------Cálculo de antecedentes
    k1 = min(CE,P);
    k2 = min(CE,C);
    k3 = min(CN,P);
    k4 = min(CN,C);
    k5 = min(CN,N);
    k6 = min(L,C);
    k7 = min(L,N);
//------------Cálculo de grado de consistencia
    a1 = min(k1,AP);
    a2 = min(k2,AP);
    a3 = min(k3,AP);
    a4 = min(k4,AP);
    a5 = min(k5,AP);
    a6 = min(k6,AP);
    a7 = min(k7,AP);
    as = a1+a2+a3+a4+a5+a6+a7;
//-----------Defusificación
  Y = ((a1*cderecha)+(a2*ccentro)+(a3*ccentro)+(a4*ccentro)+(a5*ccentro)+(a6*ccentro)+(a7*cizquierda))/as;
  Serial.print("Distacia:  ");
  Serial.print(x);
  Serial.print("  Ángulo:  ");  
  Serial.println(Y); 
  servo1.write(Y);
  delay(2);
 
 }
