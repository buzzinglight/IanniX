#ifndef IANNIX_LIB_H
#define IANNIX_LIB_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

#define iannixBufferDataIndexMax       16
#define iannixBufferArgumentIndexMax   10
#define iannixBufferCharEnd1           ';'
#define iannixBufferCharEnd2           '\n'
#define iannixBufferCharSeparator      ' '

class IanniX {
public:
  static char iannixBuffer[iannixBufferArgumentIndexMax][iannixBufferDataIndexMax];
  static unsigned int iannixBufferDataIndex, iannixBufferArgumentIndex, iannixBufferArgumentIndexCache;
public:
  static const int count() {
    return iannixBufferArgumentIndexCache;
  }
  static char* toChar(const unsigned int argumentIndex) {
    return iannixBuffer[argumentIndex];
  }
  static int toInt(const unsigned int argumentIndex) {
    return atoi(iannixBuffer[argumentIndex]);
  }
  static float toFloat(const unsigned int argumentIndex) {
    return atof(iannixBuffer[argumentIndex]);
  }
  
public:
  static boolean hasData();
  static void setup() {
    Serial.begin(115200); 
  }
  static void send(const char* message) {
    Serial.println(message); 
  }
};

#endif IANNIX_LIB_H


