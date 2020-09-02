#ifndef _FINDSUPPLYPINS
#define _FINDSUPPLYPINS
#include "ibisPin.h"
#include "pinsList.h"
#include <iostream>
using namespace std;

class findSupplyPins
{
  ibisPin pullupPin;
  ibisPin pulldownPin;
  ibisPin powerClampPin;
  ibisPin gndClampPin;

  int findPins(ibisPin currentPin, pinsList pinList, boolean hasPinMapping) {
    pinsList tempPList = new pinsList();

    if (hasPinMapping) {
      if (!currentPin.pullupRef.equalsIgnoreCase("NC")) {

        pinList.gototop();

        tempPList = pinList;
        while (tempPList != null && ((
          !tempPList.current.modelName.equalsIgnoreCase("POWER") &&
          !tempPList.current.modelName.equalsIgnoreCase("GND")) ||
          !tempPList.current.pullupRef.equalsIgnoreCase(currentPin.pullupRef)))
          tempPList.next();
        if (tempPList == null) {

          printf("No Power or Ground pin");
          return 1;
        }

        this.pullupPin = tempPList.current;
      } else {

        this.pullupPin = null;
      }


      if (!currentPin.pulldownRef.equalsIgnoreCase("NC")) {

        pinList.gototop();
        tempPList = pinList;
        while (tempPList != null && ((
          !tempPList.current.modelName.equalsIgnoreCase("POWER") &&
          !tempPList.current.modelName.equalsIgnoreCase("GND")) ||
          !tempPList.current.pulldownRef.equalsIgnoreCase(currentPin.pulldownRef)))
          tempPList.next();
        if (tempPList == null) {

          printf("No Power or Ground pin");
          return 1;
        }

        this.pulldownPin = tempPList.current;
      } else {

        this.pulldownPin = null;
      }


      if (!currentPin.powerClampRef.equalsIgnoreCase("NC")) {

        pinList.gototop();
        tempPList = pinList;
        while (tempPList != null && ((
          !tempPList.current.modelName.equalsIgnoreCase("POWER") &&
          !tempPList.current.modelName.equalsIgnoreCase("GND")) ||
          !tempPList.current.pullupRef.equalsIgnoreCase(currentPin.powerClampRef)))
          tempPList.next();
        if (tempPList == null) {

          printf("No Power or Ground pin");
          return 1;
        }

        this.powerClampPin = tempPList.current;
      } else {

        this.powerClampPin = null;
      }


      if (!currentPin.gndClampRef.equalsIgnoreCase("NC")) {

        pinList.gototop();
        tempPList = pinList;
        while (tempPList != null && ((
          !tempPList.current.modelName.equalsIgnoreCase("POWER") &&
          !tempPList.current.modelName.equalsIgnoreCase("GND")) ||
          !tempPList.current.pulldownRef.equalsIgnoreCase(currentPin.gndClampRef)))
          tempPList.next();
        if (tempPList == null) {

          printf("No Power or Ground pin");
          return 1;
        }

        this.gndClampPin = tempPList.current;
      } else {

        this.gndClampPin = null;

      }


    }
    else {

      pinList.gototop();
      tempPList = pinList;
      while (tempPList != null &&
        !tempPList.current.modelName.equalsIgnoreCase("POWER"))
        tempPList.next();
      if (tempPList == null) {

        printf("No Power pin for component. Please specify");
        printf(" at least one pin with model name POWER");
        return 1;
      }


      printf("Power pin for component available. Proceeding further ..");
      this.pullupPin = tempPList.current;
      this.powerClampPin = tempPList.current;




      pinList.gototop();
      tempPList = pinList;
      while (tempPList != null &&
        !tempPList.current.modelName.equalsIgnoreCase("GND"))
        tempPList.next();
      if (tempPList == null) {

        printf("No GND pin for component. Please specify ");
        printf(" at least one pin with model name GND");
        return 1;
      }


      printf("GND pin for component available. Proceeding further ..");
      this.gndClampPin = tempPList.current;
      this.pulldownPin = tempPList.current;
    }


    return 0;
  }
};

#endif
