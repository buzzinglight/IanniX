#include "iannix_lib.h"

void setup() {
  IanniX::setup();
  IanniX::send("zoom 110");
}

float value = 0;
void loop() {
  //Get analog value from PIN A0 (Arduino UNO)
  float dest = analogRead(0);
  //Smooth value
  value = value + (dest - value) / 5;
  
  //Control zoom with sensor on PIN A0 (Arduino Uno)
  Serial.print("zoom ");
  Serial.println(value);
  delay(10); 
  
  //Reception of events from IanniX
  if((IanniX::hasData()) && (IanniX::count() >= 3))
    tone(IanniX::toInt(1), IanniX::toInt(2), IanniX::toInt(3));
}

