#ifndef _ANALYZECOMPONENT
#define _ANALYZECOMPONENT

#include <iostream>
using namespace  std;

#include "cListContainer.h"
#include "ibisPin.h"

class analyzeComponent
{
public:
  cListContainer CLC;
  ibisPin currentPin;
    int analyzeComponent(int spiceType, int iterate, int cleanup, String spiceCommand) throws IOException {
    int result = 0;




    ibisPin enablePin_P = new ibisPin();
    ibisPin inputPin = new ibisPin();


    ibisComponent componentOut = new ibisComponent();
    findSupplyPins findSupplyPins1 = new findSupplyPins();
    getMatchingPin getMatchingPin1 = new getMatchingPin();
    analyzePin analyzePin1 = new analyzePin();
    analyzePin analyzePin2 = new analyzePin();

    pinsList tempPinsList = new pinsList();

    this.CLC.cListCont.gototop();
    for (int i1 = 0; i1 < this.CLC.cListCont.count; i1++) {

      ibisComponent componentIn = this.CLC.cListCont.current;
      tempPinsList = componentIn.pList;
      tempPinsList.gototop();

      if (componentIn.pList != null) {

        printf("\n++++\nAnalyzing component " + componentIn.component);

        componentIn.pList.gototop();
        for (int i = 0; i < componentIn.pList.count; i++)
        {
          this.currentPin = componentIn.pList.current;

          printf("\nAnalyzing pin '" + this.currentPin.pinName + "'");
          printf("modelName for above pin " + this.currentPin.modelName);
          enablePin_P = null;
          inputPin = null;









          if (goodies.THIS_PIN_NEEDS_ANALYSIS(this.currentPin.modelName) &&
            this.currentPin.model.hasBeenAnalyzed == 0) {

            printf("THIS_PIN_NEEDS_ANALYSIS");

            result = findSupplyPins1.findPins(this.currentPin, tempPinsList, componentIn.hasPinMapping);
            ibisPin pullupPin = findSupplyPins1.pullupPin;
            ibisPin pulldownPin = findSupplyPins1.pulldownPin;
            ibisPin powerClampPin = findSupplyPins1.powerClampPin;
            ibisPin gndClampPin = findSupplyPins1.gndClampPin;

            componentIn.pList.current = this.currentPin;

            if (result == 0) {

              if (!this.currentPin.enablePin.equalsIgnoreCase("")) {

                enablePin_P = getMatchingPin1.getMatchingPin(this.currentPin.enablePin, componentIn.pList);

                componentIn.pList.current = this.currentPin;
                if (enablePin_P == null) {

                  printf("Could'nt find enable pin for " + this.currentPin.pinName);
                  result++;
                }
              }
              if (!this.currentPin.inputPin.equalsIgnoreCase("")) {

                inputPin = getMatchingPin1.getMatchingPin(this.currentPin.inputPin, componentIn.pList);

                componentIn.pList.current = this.currentPin;
                if (inputPin == null) {

                  printf("Could'nt find input pin for " + this.currentPin.pinName);
                  result++;
                }
              }
              if (result == 0) {

                printf("start analyzing pin .. " + this.currentPin.pinName);

                analyzePin1.currentPin = this.currentPin;
                result = analyzePin1.analyzePin(enablePin_P, inputPin, pullupPin, pulldownPin, powerClampPin,
                    gndClampPin, spiceType, componentIn.spiceFile, componentIn.seriesSpiceFile, spiceCommand, iterate, cleanup);
                this.currentPin = analyzePin1.currentPin;
              }
              if (result > 0) {

                printf("Error in Analysis for Pin " + this.currentPin.pinName);
              } else {

                this.currentPin.model.hasBeenAnalyzed++;
              }
            }
          }  componentIn.pList.next();
        }

      } else {

        printf(". Please specify the pin list using the [Pin] Keyword");
        result++;
      }

      this.CLC.cListCont.next();
    }

    return result;
  }
};

#endif

