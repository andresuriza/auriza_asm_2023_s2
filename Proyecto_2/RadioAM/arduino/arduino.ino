#include <arduinoFFT.h>

#define PIN_SENSOR A0
#define PIN_SALIDA 8  

const int OUTPUT_FREQUENCY =  40; // Frecuencia de la señal senoidal en Hz
const double SAMPLING_FREQUENCY = 3000; //Hz, must be less than 10000 due to ADC ///126
const double CARRIER_FREQUENCY_1 = 1000; // Frecuencia de la primera portadora
const double CARRIER_FREQUENCY_2 = 100; // Frecuencia de 

unsigned int samplingPeriod; 

void setup() {
  Serial.begin(9600);
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_SALIDA, OUTPUT);
  samplingPeriod = round((1.0/SAMPLING_FREQUENCY)*1000000);
}

void loop() {
  double now = micros();
  double time = now/1000000;
  while(true){
    if((micros()-now) >= samplingPeriod){
      double primerMensaje = analogRead(PIN_SENSOR);
      double primerPortadora = cos(2 * PI * CARRIER_FREQUENCY_1 * time);
      double primerSenalModulada = primerMensaje * primerPortadora;

      double segundoMensaje = 200 * cos(2 * PI * OUTPUT_FREQUENCY * time);
      double segundaPortadora =  cos(2 * PI * CARRIER_FREQUENCY_2 * time);
      double segundaSenalModulada = segundoMensaje * segundaPortadora;

      double mensajeAux = primerSenalModulada + segundaSenalModulada; 

      //int mensajeFinal = map(mensajeAux, -1023, 1023, 0, 255);

      //analogWrite(PIN_SALIDA, mensajeFinal);

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

      //Serial.println(mensajeAux);
      Serial.Write(mensajeAux);
      break;
    }
  }
}




