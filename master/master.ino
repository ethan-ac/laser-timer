#include <SoftwareSerial.h>
SoftwareSerial BTserial(4, 5);
SoftwareSerial HC12(6, 7);

int sensor = A0;
int batterypin = A1;
int batterybutton =8;
int led0 = 9;
int led1 = 10;
int led2 = 11;
int led3 = 12;

unsigned long startmillis;
unsigned long stopmillis;
int batteryraw = 0;
float voltage;

void setup() {
  pinMode(batterybutton, INPUT);
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  BTserial.begin(9600);
  HC12.begin(9600);
}


void loop() {
  if (HC12.read() == 1) {
    startmillis = millis();
    BTserial.println("Running...");
    while (analogRead(sensor) > 950) {
      stopmillis = millis();
    }
    BTserial.print("time: ");
    BTserial.print((stopmillis - startmillis) / 1000., 3);
    BTserial.println("s");
    while (HC12.available() > 0)
      HC12.read();
  }
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


