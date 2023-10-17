const int carrier_freq = 200000;
const float mod_index = 0.5;
const int arrayLength = 1000;

float generate_cos_signal(float frequency, float time){
  return cos(2*PI*frequency * time);
}

float amplitude_modulate_signal(float signal, float carrier_signal, float modulation_index){
  return (1 + modulation_index*signal) * carrier_signal; // modulation_index
}

float amplitude_demodulate_signal(float modulated_signal, float carrier_signal){
  return modulated_signal * carrier_signal;
}

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
}

void loop() {
  int valMuestreo[arrayLength] = {0};
  int sensorValue = analogRead(A0); // 0 a 1024

  for (int i=0; i < arrayLength - 1; i++){
      valMuestreo[i+1] = valMuestreo[i];
  }
  
  valMuestreo[arrayLength - 1] = sensorValue;

  float carrier_signal = generate_cos_signal(carrier_freq, millis() / 1000.0);

  float modulated_signal = amplitude_modulate_signal(sensorValue, carrier_signal, mod_index);

  float demodulated_signal = amplitude_demodulate_signal(modulated_signal, carrier_signal);

  if (millis()%1000==0){
    Serial.print("Señal original: ");
    Serial.print(sensorValue);
    Serial.println();
    

    Serial.print("Señal modulada: ");
    Serial.print(modulated_signal);
    Serial.println();

    Serial.print("Señal demodulada: ");
    Serial.print(demodulated_signal);
    Serial.println();
    Serial.println();
  }
  

  
  //tone(, sensorValue);  
}