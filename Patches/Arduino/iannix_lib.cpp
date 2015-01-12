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

#include "iannix_lib.h"

char IanniX::iannixBuffer[iannixBufferArgumentIndexMax][iannixBufferDataIndexMax];
unsigned int IanniX::iannixBufferDataIndex = 0;
unsigned int IanniX::iannixBufferArgumentIndex = 0;
unsigned int IanniX::iannixBufferArgumentIndexCache = 0;

boolean IanniX::hasData() {
  boolean hasDataReturn = false;
  while(Serial.available() > 0) {
    //Received char
    char iannixByte = Serial.read();
    
    //End of frame
    if((iannixByte == iannixBufferCharEnd1) || (iannixByte == iannixBufferCharEnd2)) {
      hasDataReturn = true;
    }
    //Frame payload
    else {
      //Argument separator
      if(iannixByte == iannixBufferCharSeparator) {
        //Can store ?
        if(iannixBufferArgumentIndex < iannixBufferArgumentIndexMax) {
          //Close the previous argument
          iannixBuffer[iannixBufferArgumentIndex][iannixBufferDataIndex] = 0;
          //Open a new argument
          iannixBufferArgumentIndex++;
          iannixBufferDataIndex = 0;
        }
        //No more memory
        else
          hasDataReturn = true;
      }
      //Message content
      else if(iannixBufferDataIndex < iannixBufferArgumentIndexMax)
        iannixBuffer[iannixBufferArgumentIndex][iannixBufferDataIndex++] = iannixByte;
      //No more memory
      else
        hasDataReturn = true;
    }
  }
  //If the message is over (end of frame OR no more memory)
  if(hasDataReturn) {
    iannixBufferArgumentIndexCache = iannixBufferArgumentIndex;
    iannixBufferDataIndex = 0;
    iannixBufferArgumentIndex = 0;
  }
  
  //Returns
  return hasDataReturn;
}




