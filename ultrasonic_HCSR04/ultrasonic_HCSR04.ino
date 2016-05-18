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
  matrix.begin(0x71);  // pass in the address
  matrix.setRotation(1);

  
  pinMode(ultrasonicPin, INPUT);
}

void loop() {
  distance = int(analogRead(A0)/1023.0*5.0/1000/9.8);
  setMatrix();
  
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
#include <Adafruit_NeoPixel.h>
#define PIN 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

// pins for the ultrasonic sensor
int ultrasonicPin = A0;
int arraysize = 9; // quantity of values to find the median (sample size). Needs to be an odd number
int rangevalue[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
long pulse;
int modE;

void setup() {
 
}

void loop() {
  
 for(int i = 0; i < arraysize; i++){                    
    //pulse = pulseIn(ultrasonicPin, HIGH);
    pulse = analogRead(ultrasonicPin);
    rangevalue[i] = pulse;
    delay(10);
  }
  //Serial.print("Unsorted: ");
  //printArray(rangevalue,arraysize);
  isort(rangevalue,arraysize);
  //Serial.print("Sorted: ");
  //printArray(rangevalue,arraysize);
  modE = mode(rangevalue,arraysize);
  //Serial.print("The mode/median is: ");
  Serial.print(modE);
  Serial.println();
 
}


void printArray(int *a, int n) {
  for (int i = 0; i < n; i++)
  {
    Serial.print(a[i], DEC);
    Serial.print(' ');
  }
  Serial.println();
}

// Sorting function (Author: Bill Gentles, Nov. 12, 2010)
void isort(int *a, int n){
  for (int i = 1; i < n; ++i)  {
    uint16_t j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--) {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}
 
// Mode function, returning the mode or median.
int mode(int *x,int n){
  int i = 0;
  int count = 0;
  int maxCount = 0;
  uint16_t mode = 0;
  int bimodal;
  int prevCount = 0;
  while(i<(n-1)){
    prevCount=count;
    count=0;
    while( x[i]==x[i+1] ) {
      count++;
      i++;
    }
    if( count > prevCount & count > maxCount) {
      mode=x[i];
      maxCount=count;
      bimodal=0;
    }
    if( count == 0 ) {
      i++;
    }
    if( count == maxCount ) {      //If the dataset has 2 or more modes.
      bimodal=1;
    }
    if( mode==0 || bimodal==1 ) {  // Return the median if there is no mode.
      mode=x[(n/2)];
    }
    return mode;
  }
}




