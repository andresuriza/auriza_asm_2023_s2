#include <arduinoFFT.h>
#define PIN_SENSOR 28
//--------TRANSMISOR-----------------------------------------------------------
const int OUTPUT_FREQUENCY =  100; // Frecuencia del tono senoidal enviado
const double SAMPLING_FREQUENCY = 10000; // Frecuencia a la que se envian las muestras
const double CARRIER_FREQUENCY_1 = 500; // Frecuencia de la primera portadora
const double CARRIER_FREQUENCY_2 = 5000; // Frecuencia de la segunda portadora

const double primerFrecuencia = 2 * PI * CARRIER_FREQUENCY_1; // Frecuencia en radianes
const double segundaFrecuencia = 2 * PI * CARRIER_FREQUENCY_2; // Frecuencia en radianes
const double tonoSenoidal = 2 * PI * OUTPUT_FREQUENCY; // Frecuencia en radianes

unsigned int samplingPeriod; 

//-----------------------------------------------------------------------------
const uint16_t SAMPLES = 1024; //This value MUST ALWAYS be a power of 2
//const double SAMPLING_FREQUENCY = 16000; //Hz, must be less than 10000 due to ADC ///126


double inputSignal[SAMPLES];

double signal1[SAMPLES];
double signal2[SAMPLES];

double lp1filteredSignal1[SAMPLES];
double lp1filteredSignal2[SAMPLES];

double hpfilteredSignal1[SAMPLES];
double hpfilteredSignal2[SAMPLES];

double lp2filteredSignal1[SAMPLES];
double lp2filteredSignal2[SAMPLES];

double vReal1[SAMPLES];
double vImag1[SAMPLES];

double vReal2[SAMPLES];
double vImag2[SAMPLES];

bool initialized;

double timeStamp;

double dominantFrecuency1;
double dominantFrecuency2;

//sample number
int sampleNumber;

//actual sample
int sample;

String str;

arduinoFFT FFT = arduinoFFT();

//lowpass 1kHz
void lowPass1(){
  //coeficients for x
  double b[] = {0.067,0.135,0.067};
  //coeficients for y
  double a[] = {1.143,-0.413};
  lp1filteredSignal1[0] = 0;
  lp1filteredSignal1[1] = 0;
  for (int i =2;i<SAMPLES;i++){
    lp1filteredSignal1[i] = inputSignal[i]*b[0] + inputSignal[i-1]*b[1]
    + inputSignal[i-2]*b[2] + lp1filteredSignal1[i-1]*a[0] 
    + lp1filteredSignal1[i-2]*a[1];
  } 
}
//LP 6kHz
void lowPass2(){
  //coeficients for x
  double b[] = {0.391,0.783,0.391};
  //coeficients for y
  double a[] = {-0.370,-0.196};
  lp1filteredSignal2[0] = 0;
  lp1filteredSignal2[1] = 0;
  for (int i =2;i<SAMPLES;i++){
    lp1filteredSignal2[i] = inputSignal[i]*b[0] + inputSignal[i-1]*b[1]
    + inputSignal[i-2]*b[2] + lp1filteredSignal2[i-1]*a[0] 
    + lp1filteredSignal2[i-2]*a[1];
  } 
}

//HP 0Hz
void highPass1(){
  //coeficients for x
  double b[] = {1.000,-1.999,1.00};
  //coeficients for y
  double a[] = {1.999,-0.999};
  hpfilteredSignal1[0] = 0;
  hpfilteredSignal1[1] = 0;
  for (int i =2;i<SAMPLES;i++){
    hpfilteredSignal1[i] = lp1filteredSignal1[i]*b[0] + lp1filteredSignal1[i-1]*b[1]
    + lp1filteredSignal1[i-2]*b[2] + hpfilteredSignal1[i-1]*a[0] 
    + hpfilteredSignal1[i-2]*a[1];
    
  } 
}

//HP 4kHz
void highPass2(){
  //coeficients for x
  double b[] = {0.391,-0.783,0.391};
  //coeficients for y
  double a[] = {0.370,-0.196};
  hpfilteredSignal2[0] = 0;
  hpfilteredSignal2[1] = 0;
  for (int i =2;i<SAMPLES;i++){

    hpfilteredSignal2[i] = lp1filteredSignal2[i]*b[0] + lp1filteredSignal2[i-1]*b[1]
    + lp1filteredSignal2[i-2]*b[2] + hpfilteredSignal2[i-1]*a[0] 
    + hpfilteredSignal2[i-2]*a[1];
    
  } 
}

void setup() {
  
  Serial.begin(9600);
  samplingPeriod = round((1.0/SAMPLING_FREQUENCY)*1000000);
  initialized = false;
  sampleNumber = 0;
  pinMode(PIN_SENSOR, INPUT);
}

void loop() {
  if(!initialized){
    timeStamp = micros();
    initialized = true;
  }
  
  if(timeStamp>=samplingPeriod){
    double time = timeStamp/1000000;
    
    double primerMensaje = 200 * cos(tonoSenoidal * time);
    double primerPortadora = cos(primerFrecuencia * time);
    double primerSenalModulada = primerMensaje * primerPortadora;

    double segundoMensaje = analogRead(PIN_SENSOR);
    //Serial.println(segundoMensaje);
    double segundaPortadora =  cos(segundaFrecuencia * time);
    double segundaSenalModulada = segundoMensaje * segundaPortadora;
    sample = primerSenalModulada + segundaSenalModulada; 
    /**
    if (sample<0){
      sample = 0;
    }**/
    //Serial.print("Detector_Envolvente: ");
    //Serial.println(sample);
    //Serial.print(",");
    inputSignal[sampleNumber] = sample;
    
    
    sampleNumber++;
    
    timeStamp = micros();
    
  }
  if(sampleNumber == SAMPLES){
        lowPass1();
        lowPass2();

        highPass1();
        highPass2();
        

        for (int i = 0; i < SAMPLES; i++) {
          if(hpfilteredSignal1[i]<0){
            hpfilteredSignal1[i] = abs(hpfilteredSignal1[i]);
          }
          if(hpfilteredSignal2[i]<0){
            hpfilteredSignal2[i] =abs(hpfilteredSignal2[i]) ;
          }
          vReal1[i] = hpfilteredSignal1[i]*2;
          vImag1[i] = 0;

          vReal2[i] = hpfilteredSignal2[i]*2;
          vImag2[i] = 0;

        }

        //signal 1 FFT 
        FFT.Windowing(vReal1, SAMPLES, FFT_WIN_TYP_RECTANGLE, FFT_FORWARD);
        FFT.Compute(vReal1, vImag1, SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal1, vImag1, SAMPLES);
        FFT.DCRemoval(vReal1, SAMPLES);
        dominantFrecuency1 = FFT.MajorPeak(vReal1, SAMPLES, SAMPLING_FREQUENCY);


        //Signal 2 FFt
        FFT.Windowing(vReal2, SAMPLES, FFT_WIN_TYP_RECTANGLE, FFT_FORWARD);
        FFT.Compute(vReal2, vImag2, SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal2, vImag2, SAMPLES);
        FFT.DCRemoval(vReal2, SAMPLES);
        dominantFrecuency2 = FFT.MajorPeak(vReal2, SAMPLES, SAMPLING_FREQUENCY);

        sampleNumber = 0;
        tone(20, dominantFrecuency1);
        Serial.println(dominantFrecuency1);
        tone(21, dominantFrecuency2);
        Serial.println(dominantFrecuency2);
        for (int i = 0; i< SAMPLES;i++){
          Serial.print("SenalMezclada:");
          Serial.print(inputSignal[i]);
          Serial.print(",");
          Serial.print("Señal1:");
          Serial.print(hpfilteredSignal1[i]*2);
          Serial.print(",");
          Serial.print("Señal2:");
          Serial.println(hpfilteredSignal2[i]*2);
        }
    }
}




