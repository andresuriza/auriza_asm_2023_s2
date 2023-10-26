#include <arduinoFFT.h>

#define PIN_SENSOR A0

const int OUTPUT_FREQUENCY =  100; // Frecuencia del tono senoidal enviado
const double SAMPLING_FREQUENCY = 8000; // Frecuencia a la que se envian las muestras
const double CARRIER_FREQUENCY_1 = 3000; // Frecuencia de la primera portadora
const double CARRIER_FREQUENCY_2 = 500; // Frecuencia de la segunda portadora

const double primerFrecuencia = 2 * PI * CARRIER_FREQUENCY_1; // Frecuencia en radianes
const double segundaFrecuencia = 2 * PI * CARRIER_FREQUENCY_2; // Frecuencia en radianes
const double tonoSenoidal = 2 * PI * OUTPUT_FREQUENCY; // Frecuencia en radianes

unsigned int samplingPeriod; 


void setup() {
  Serial.begin(9600);
  pinMode(PIN_SENSOR, INPUT);
  samplingPeriod = round((1.0/SAMPLING_FREQUENCY)*1000000);
}

void loop() {
  double now = micros();
  double time = now/1000000;
  while(true){
    if((micros()-now) >= samplingPeriod){
      double primerMensaje = analogRead(PIN_SENSOR);
      double primerPortadora = cos(primerFrecuencia * time);
      double primerSenalModulada = primerMensaje * primerPortadora;

      double segundoMensaje = 200 * cos(tonoSenoidal * time);
      double segundaPortadora =  cos(segundaFrecuencia * time);
      double segundaSenalModulada = segundoMensaje * segundaPortadora;

      int mensajeCombinado = primerSenalModulada + segundaSenalModulada; 

      /*
      Serial.print(primerMensaje);
      Serial.print(",");
      Serial.print(primerPortadora);
      Serial.print(",");
      Serial.println(primerSenalModulada);*/
      
      /*
      Serial.print(segundoMensaje);
      Serial.print(",");
      Serial.print(segundaPortadora);
      Serial.print(",");
      Serial.println(segundaSenalModulada);*/

      //Serial.println(mensajeCombinado);

      Serial.println(mensajeCombinado);
      break;
    }
  }
}




