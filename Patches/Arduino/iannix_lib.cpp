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




