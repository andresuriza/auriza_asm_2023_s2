const int CW = 9; 
const int CCW =  10; 
const int POSITION =  A0;
int motorState;
float angle;
unsigned long prev = 0;
unsigned long now;
const int impulseTime = 500;
void setup() {
  pinMode(CW, OUTPUT);
  pinMode(CCW, OUTPUT);
  pinMode(POSITION, INPUT);
  motorState = 0;
  Serial.begin(9600);
  
}

void loop() {
  
  angle = analogRead(POSITION)*0.69;
  
  if (angle<350 && (now-prev)<impulseTime){
    analogWrite(CW, 255);
    motorState = 1;
  } else{
    analogWrite(CW, 0);
    motorState = 0;
  }
  if ((now-prev)<impulseTime+100){
    Serial.print("Position:");
    Serial.print(angle/360); //angulo normalizados
    Serial.print(",");
    Serial.print("Input:");
    Serial.println(motorState);
  }
    
  now = millis();
  
  if(angle>-5 && angle<5){
    digitalWrite(LED_BUILTIN, HIGH);
    
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

}
