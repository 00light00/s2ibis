#ifndef _GETMATCHINGPIN
#define _GETMATCHINGPIN

#include <iostream>
#include <string>
using namespace  std;
using String = std::string;

#include "ibisPin.h"

ibisPin getMatchingPin(String searchName, pinsList pinList) {
    pinList.gototop();
    ibisPin tempPin = new ibisPin();
    tempPin = pinList.current;

    if (searchName.equalsIgnoreCase(""))
      return null;
    while (tempPin != null &&
      !searchName.equalsIgnoreCase(tempPin.pinName)) {

      tempPin = pinList.current;
      pinList.next();
    }
    if (tempPin == null)
    {
      printf("Pin " + searchName + " Not Found in pin list");
    }
    return tempPin;
  }
}


#endif
