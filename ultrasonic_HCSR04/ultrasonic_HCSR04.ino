#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();

long startDistance = 12;
long distance = 0;

void setup() {
  Serial.begin (9600);


  Serial.println("16x8 LED Matrix Test");
  // changed from default address of 0x70 b/c soldered
  matrix.begin(0x70);  // pass in the address
  matrix.setRotation(1);

  
  //pinMode(ultrasonicPin, INPUT);
}

void loop() {
  Serial.println(analogRead(A0)/1023.0*5.0*1000/9.8);
  distance = int(analogRead(A0)/1023.0*5.0*1000/9.8);
  //setMatrix();
  printMatrix();
}


//void setMatrix() {
//  if (digitalRead(buttonPin)) {
//    printMatrix(); 
//  }
//  else {
//    matrix.clear();
//    matrix.writeDisplay();
//  }
//}



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


