int potPin = A0;
int refPin = A1
;

int potVal = 0;
int encoder_val = 0;
//---------Prueba y error-----------
float kp = 0.2;
float ki = 0.00000;
float kd = 2.00;
//----------------------------------
float angulo, angulo_d;
int dt;
unsigned long t;
unsigned long t_prev = 0;
int val_prev = 0;
float err, integralError;
float e_prev = 0;
float inte_prev = 0;
float vMax = 12; // 12V motor
float vMin = -12; // 12V motor
float volt = 0.1;
const byte PWMPin = 6;
const byte DirPin1 = 9; //9 is CW
const byte DirPin2 = 10; //0 is CCW

void ControlPosicion(float volt, float vMax) {
  int PWMval = int(255 * abs(volt) / vMax);
  
  if (PWMval > 255) {
    PWMval = 255;
  }

  if (volt > 0) {
    digitalWrite(DirPin1, HIGH);
    digitalWrite(DirPin2, LOW);
  }

  else if (volt < 0) {
    digitalWrite(DirPin1, LOW);
    digitalWrite(DirPin2, HIGH);
  }
  
  else {
    digitalWrite(DirPin1, LOW);
    digitalWrite(DirPin2, LOW);
  }

  analogWrite(PWMPin, PWMval);

}

void setup() {
  Serial.begin(9600);
  pinMode(DirPin1, OUTPUT);
  pinMode(DirPin2, OUTPUT);
}

void loop() {
  potVal = analogRead(potPin);
  encoder_val = analogRead(refPin);
  t = millis();
  dt = (t - t_prev);
  angulo = potVal;
  angulo_d = encoder_val*1.96; //mapping max value is 522

  err = angulo_d - angulo;
  integralError = inte_prev + (dt * (err + e_prev) / 2); // Diferencia regresiva
  volt = kp * err + ki * integralError + (kd * (err - e_prev) / dt); // PID

  if (volt > vMax) { // Limite de posicion
    volt = vMax;
    integralError = inte_prev;
  }

  if (volt < vMin) { // Correccion de voltaje de posicion
    volt = vMin;
    integralError = inte_prev;
    val_prev = potVal;
  }
  
  ControlPosicion(volt, vMax);
  Serial.println(angulo_d);
  Serial.print(" \t");
  Serial.print(angulo);
  Serial.print(" \t ");
  t_prev = t;
  inte_prev = integralError;
  e_prev = err;
  delay(10); // Cambiar por millis
}