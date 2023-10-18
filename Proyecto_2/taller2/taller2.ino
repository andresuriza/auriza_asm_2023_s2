#include <arduinoFFT.h>

const int OUTPUT_FREQUENCY = 100; // Frecuencia de la señal senoidal en Hz
const uint16_t SAMPLES = 128; //This value MUST ALWAYS be a power of 2
const double SAMPLING_FREQUENCY = 300; //Hz, must be less than 10000 due to ADC ///126

double signal[SAMPLES];
double vReal[SAMPLES];
double vImag[SAMPLES];

unsigned int samplingPeriod; 

arduinoFFT FFT = arduinoFFT();

void setup() {
  Serial.begin(115200);
  samplingPeriod = round((1.0/SAMPLING_FREQUENCY)*1000000);
}

void loop() {
  generateSineWave(OUTPUT_FREQUENCY);
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = signal[i];
    vImag[i] = 0;
  }
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_RECTANGLE, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  FFT.DCRemoval(vReal, SAMPLES);
  double dominantFrecuency = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

  Serial.print("Frecuencia (Hz): ");
  Serial.println(dominantFrecuency); //Print out what frequency is the most dominant.

  delay(5000);
}

void generateSineWave(double frequency) {
  double now = micros();
  int i = 0;
  while (i < SAMPLES) {
    if((micros()-now) >= samplingPeriod){
      double time = now;
      signal[i] = sin(2 * PI * frequency * time/1000000);
      Serial.println("Senal senoidal: ");
      Serial.println(signal[i]);
      now = micros();
      i++;
    }
  }
}


