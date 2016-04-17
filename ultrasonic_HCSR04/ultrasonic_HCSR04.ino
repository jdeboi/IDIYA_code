#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();

#define trigPin 11
#define echoPin 10
#define buttonPin 2

long startDistance = 12;
long distance = 0;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);

  Serial.println("16x8 LED Matrix Test");
  // changed from default address of 0x70 b/c soldered
  matrix.begin(0x71);  // pass in the address
  matrix.setRotation(1);
}

void loop() {
  for(int i = 0; i < 10; i++) {
    setDistance();
    delayCheck(500);
    //delay(500);
  }
  printDistance(); 
  setMatrix();
  
}

void delayCheck(int delayTime) {
  long t = millis();
  while(millis() - t < delayTime) setMatrix();
}

void setMatrix() {
  if (digitalRead(buttonPin)) {
    printMatrix(); 
  }
  else {
    matrix.clear();
    matrix.writeDisplay();
  }
}

void setDistance() {
  long tempdis, duration;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  tempdis = startDistance - ((duration/2) / 29.1*0.394);
  if(tempdis < startDistance && tempdis >=0) {
    distance = distance *.5 + tempdis *.5; 
  }
}


void printMatrix() {
  matrix.setTextSize(0);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  matrix.clear();
  matrix.setCursor(3,0);
  if(distance < 100) matrix.print(distance);
  matrix.writeDisplay();
}

void printDistance() {
  // print out distance
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" in");
  }
}


