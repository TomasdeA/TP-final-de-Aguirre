#include <math.h>

const int echo = 6;
const int trig = 5;
unsigned long previousMillis = 0;
const long interval = 100;
float alpha = 0.5; // exponential smoothing constant
//float alpha = 0.8; // exponential smoothing constant
float average_cm = 0; // initialization @ generic distance

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

void setup() {
  // put your setup code here, to run once:

  pinMode(echo,INPUT);
  
  pinMode(trig,OUTPUT);
  digitalWrite(trig, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long currentMillis = millis();
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;

  if (currentMillis-previousMillis >= interval) {
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);

    // Wait for pulse on echo pin
    while (digitalRead(echo) == 0);

    // Measure how long the echo pin was held high (pulse width)
    // Note: the micros() counter will overflow after ~70 min
    t1 = micros();
    while (digitalRead(echo) == 1);
    t2 = micros();
    pulse_width = t2-t1;
    if ( pulse_width > MAX_DIST ) {
      cm = 400;
    } else {
      cm = pulse_width/58.0;
    } 
    average_cm = alpha*cm+(1-alpha)*average_cm;    //exponential smoothing
    previousMillis = currentMillis;

    Serial.print(pulse_width);
    Serial.print(" microsegundos \t");
    Serial.print(cm);
    Serial.print(" cm \t");
    Serial.print(average_cm);
    Serial.println(" avg \t");
  }
}