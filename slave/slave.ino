#include <SoftwareSerial.h>
SoftwareSerial HC12(6, 7); // TX | RX

int sensor = A0;
int batterypin = A1;
int batterybutton = 8;
int led0 = 9;
int led1 = 10;
int led2 = 11;
int led3 = 12;

int batteryraw = 0;
float voltage;

void setup() {
  pinMode(batterybutton, INPUT);
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  HC12.begin(9600);
}

void loop() {
  //if photocell is covered start timer, else wait
  if (analogRead(sensor) < 950)
    HC12.write(byte(1));
  else
    HC12.write(byte(0));
  while (digitalRead(batterybutton) == 1) {
    if ( voltage >= 5.325) {
      digitalWrite(led0, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
    }
    else if ( voltage >= 4.65) {
      digitalWrite(led0, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
    }
    else if ( voltage >= 3.975) {
      digitalWrite(led0, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    }
    else{
      digitalWrite(led0, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    }
    batteryraw = analogRead(batterypin);
    voltage = batteryraw * (6.0 / 1024);
  }
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

