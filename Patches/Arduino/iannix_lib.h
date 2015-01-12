/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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


