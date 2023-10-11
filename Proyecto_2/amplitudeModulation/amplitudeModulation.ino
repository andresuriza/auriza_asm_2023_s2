//formulas de https://www.tutorialspoint.com/analog_communication/analog_communication_amplitude_modulation.htm
#define sine_freq = 100;
#define carrier_freq = 1000;

#define mod_index = 0.5;



float generate_sine_signal(float frequency, float time){
  return sin(2*PI*frecuency, time);
}

float generate_cos_signal(float frequency, float time){
  return cos(2*PI*frecuency, time);
}

float amplitude_modulate_sine_signal(float sine_signal, float carrier_signal, float modulation_index){
  return (1+modulation_index*sine_signal)*carrier_signal;
}

float amplitude_demodulate_sine_signal(float modulated_signal, float carrier_signal){
  return modulated_signal*carrier_signal;
}
void setup() {
  Serial.begin(9600);

}

void loop() {
  float sine_signal = generate_sine_signal(sine_freq, millis()/1000.0);
  float carrier_signal = generate_cos_signal(carrier_freq, millis() / 1000.0);

  float modulated_signal = amplitude_modulate_sine_signal(sine_signal, carrier_signal, mod_index);

  float demodulated_signal = amplitude_demodulate_sine_signal(modulated_signal, carrier_signal);

  Serial.print("Señal original: ");
  Serial.print(sine_signal);
  Serial.println();
  Serial.println();

  Serial.print("Señal modulada: ");
  Serial.print(modulated_signal);
  Serial.println();
  Serial.println();

  Serial.print("Señal demodulada: ");
  Serial.print(demodulated_signal);
  Serial.println();
  Serial.println();


}
