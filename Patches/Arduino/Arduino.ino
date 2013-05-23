#include "iannix_lib.h"

void setup() {
  IanniX::setup();
  Serial.println("zoom 110");
}

void loop() {
  if((IanniX::hasData()) && (IanniX::count() >= 3))
    tone(IanniX::toInt(1), IanniX::toInt(2), IanniX::toInt(3));
}

