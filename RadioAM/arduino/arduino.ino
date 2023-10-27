#include <arduinoFFT.h>
#include <SPI.h>
#define SS_PIN 10
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
  Serial.begin(250000);
  pinMode(SS_PIN, OUTPUT);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);
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

      Serial.println( (int)primerMensaje);
      
      digitalWrite(SS_PIN, LOW);
      SPI.transfer(primerMensaje);
      digitalWrite(SS_PIN, HIGH);
      Serial.println(primerMensaje);
      Serial.println(mensajeCombinado);
      
      break;
    }
  }
}




