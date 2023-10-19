#include <arduinoFFT.h>

const int OUTPUT_FREQUENCY =  50;// Frecuencia de la señal senoidal en Hz
const uint16_t SAMPLES = 512; //This value MUST ALWAYS be a power of 2
const double SAMPLING_FREQUENCY = 1500; //Hz, must be less than 10000 due to ADC ///126
const double CARRIER_FREQUENCY = 300;
double signall[SAMPLES];
double carrier[SAMPLES];
double modulatedSignal[SAMPLES];
double demodulatedSignal[SAMPLES];
double vReal[SAMPLES];
double vImag[SAMPLES];

bool signallGenerated;
unsigned int samplingPeriod; 
unsigned int carrierPeriod;

double dominantFrecuency;

arduinoFFT FFT = arduinoFFT();
void generateSineWave(double frequency) {
  double now = micros();
  int i = 0;
  while (i < SAMPLES) {
    if((micros()-now) >= samplingPeriod){
      double time = now;
      signall[i] = sin(2 * PI * frequency * time/1000000);
      now = micros();
      i++;
    }
  }
}

void generateCarrierCos(double frequency){
  double now = micros();
  int i = 0;
  while(i<SAMPLES){
    if((micros()-now) >= samplingPeriod){
      double time = now;
      carrier[i] = cos(2* PI * frequency * time/1000000);
      now = micros();
      i++;
    }
  }
}

void amplitude_modulate_signal(){
  for (int i = 0;i<SAMPLES;i++){
    modulatedSignal[i] = signall[i]*carrier[i];
  }
}

void amplitude_demodulate_signal(){
  for (int i = 0;i<SAMPLES;i++){
    demodulatedSignal[i] = modulatedSignal[i]*carrier[i];
  }
}

void setup() {
  Serial.begin(9600);
  samplingPeriod = round((1.0/SAMPLING_FREQUENCY)*1000000);
  signallGenerated = false;
}

void loop() {
  if(!signallGenerated){
    Serial.println("Generating signals...");
    generateSineWave(OUTPUT_FREQUENCY);
    generateCarrierCos(CARRIER_FREQUENCY);
    amplitude_modulate_signal();
    amplitude_demodulate_signal();
    
    for (int i = 0;i<SAMPLES;i++){
      Serial.print("Senal_senoidal:");
      Serial.print(signall[i]);
      Serial.print(",");

      Serial.print("Senal_carrier:");
      Serial.print(carrier[i]);
      Serial.print(",");

      Serial.print("Senal_modulada:");
      Serial.print(modulatedSignal[i]);
      Serial.print(",");

      Serial.print("Senal_demodulada:");
      Serial.println(demodulatedSignal[i]);
    }
    signallGenerated = true;
  }
  

  
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = signall[i];
    vImag[i] = 0;
  }

  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_RECTANGLE, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  FFT.DCRemoval(vReal, SAMPLES);
  dominantFrecuency = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  
  Serial.print("Frecuencia senal (Hz): ");
  Serial.println(dominantFrecuency); //Print out what frequency is the most dominant.
  
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = carrier[i];
    vImag[i] = 0;
  }

  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_RECTANGLE, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  FFT.DCRemoval(vReal, SAMPLES);
  dominantFrecuency = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  
  Serial.print("Frecuencia carrier (Hz): ");
  Serial.println(dominantFrecuency); //Print out what frequency is the most dominant.
  delay(500);

  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = modulatedSignal[i];
    vImag[i] = 0;
  }

  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_RECTANGLE, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  FFT.DCRemoval(vReal, SAMPLES);
  dominantFrecuency = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  
  Serial.print("Frecuencia modulada (Hz): ");
  Serial.println(dominantFrecuency); //Print out what frequency is the most dominant.
  delay(500);

  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = demodulatedSignal[i];
    vImag[i] = 0;
  }

  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_RECTANGLE, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  FFT.DCRemoval(vReal, SAMPLES);
  dominantFrecuency = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  
  Serial.print("Frecuencia demodulada (Hz): ");
  Serial.println(dominantFrecuency); //Print out what frequency is the most dominant.
  Serial.println();
  Serial.println();
  delay(5000);
}




