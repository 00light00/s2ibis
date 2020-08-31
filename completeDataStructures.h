#ifndef _COMPLETEDATASTRUCTURES
#define _COMPLETEDATASTRUCTURES

#include "ibisTOP.h"
#include "ibisComponent.h"
#include "ibisGlobal.h"
#include "ibisModel.h"
#include "getMatchingModel.h"
#

class completeDataStructures
{
  ibisTOP ibis;
  ibisComponent currentComponent;

  int completeDataStructures(ibisGlobal global) {
    copyGlobalDataToComponents(global);
    copyComponentDataToModels();

    this.ibis.cList.gototop();
    for (int i = 0; i < this.ibis.cList.count; i++) {

      this.currentComponent = this.ibis.cList.current;
      if (this.currentComponent.hasPinMapping &&
        copyPinMapToPins() == 1)
        return 1;
      if (linkPinsToModels() == 1) {
        return 1;
      }


      if (linkSeriesPinsToSeriesModels() == 1)
        return 1;
      if (copySeriesPinToPins() == 1)
        return 1;
      this.ibis.cList.current = this.currentComponent;
      this.ibis.cList.next();
    }
    this.ibis.cList.gototop();
    if (setModelDefaults() == 1) {
      return 1;
    }
    return 0;
  }


  int linkSeriesPinsToSeriesModels() {
    ibisModel currentSeriesModel = new ibisModel();

    getMatchingModel getMModel = new getMatchingModel();
    if (this.currentComponent.spList != null) {

      this.currentComponent.spList.gototop();
      for (int i = 0; i < this.currentComponent.spList.count; i++) {

        ibisSeriesPin currentSeriesPin = this.currentComponent.spList.current;




        currentSeriesModel = getMModel.getMatchingModel(currentSeriesPin.modelName,
            this.currentComponent.mList);
        currentSeriesPin.seriesModel = currentSeriesModel;
        this.currentComponent.spList.current = currentSeriesPin;

        this.currentComponent.spList.next();
      }
    }
    return 0;
  }


  int linkPinsToModels() {
    ibisModel currentModel = new ibisModel();

    getMatchingModel getMModel = new getMatchingModel();

    this.currentComponent.pList.gototop();
    for (int i = 0; i < this.currentComponent.pList.count; i++) {

      ibisPin currentPin = this.currentComponent.pList.current;
      if (!currentPin.modelName.equalsIgnoreCase("POWER") &&
        !currentPin.modelName.equalsIgnoreCase("GND") &&
        !currentPin.modelName.equalsIgnoreCase("NC")) {

        currentModel = getMModel.getMatchingModel(currentPin.modelName,
            this.currentComponent.mList);

        if (currentModel == null) {

          printf("Please check that you have correctly spelt the ");
          printf("model name for pin '" + currentPin.pinName + "'");
          printf(" in the [Pin] section of your input file and ");
          printf("that you have specified the model using the ");
          printf("[Model] keyword before the end of component ");
          printf(this.currentComponent.component);
          return 1;
        }
        currentPin.model = currentModel;
      }
      this.currentComponent.pList.current = currentPin;
      this.currentComponent.pList.next();
    }
    return 0;
  }




  void copyGlobalDataToComponents(ibisGlobal global) {
    this.ibis.cList.gototop();

    for (int i = 0; i < this.ibis.cList.count; i++) {

      ibisComponent currentComponent = this.ibis.cList.current;
      if (goodies.IS_USE_NA(currentComponent.c_comp.typ))
        currentComponent.c_comp = global.c_comp;
      if (goodies.IS_USE_NA(currentComponent.pinParasitics.R_pkg.typ))
        currentComponent.pinParasitics.R_pkg = global.pinParasitics.R_pkg;
      if (goodies.IS_USE_NA(currentComponent.pinParasitics.L_pkg.typ))
        currentComponent.pinParasitics.L_pkg = global.pinParasitics.L_pkg;
      if (goodies.IS_USE_NA(currentComponent.pinParasitics.C_pkg.typ))
        currentComponent.pinParasitics.C_pkg = global.pinParasitics.C_pkg;
      if (goodies.IS_USE_NA(currentComponent.tempRange.typ)) {
        currentComponent.tempRange = global.tempRange;
      }
      if (goodies.IS_USE_NA(currentComponent.voltageRange.typ) &&
        goodies.IS_USE_NA(currentComponent.pullupRef.typ)) {
        currentComponent.voltageRange = global.voltageRange;
      }
      if (goodies.IS_USE_NA(currentComponent.pullupRef.typ) &&
        goodies.IS_USE_NA(currentComponent.voltageRange.typ)) {
        currentComponent.pullupRef = global.pullupRef;
      }
      if (goodies.IS_USE_NA(currentComponent.pulldownRef.typ) &&
        goodies.IS_USE_NA(currentComponent.voltageRange.typ)) {
        currentComponent.pulldownRef = global.pulldownRef;
      }
      if (goodies.IS_USE_NA(currentComponent.powerClampRef.typ) &&
        goodies.IS_USE_NA(currentComponent.voltageRange.typ)) {
        currentComponent.powerClampRef = global.powerClampRef;
      }
      if (goodies.IS_USE_NA(currentComponent.gndClampRef.typ) &&
        goodies.IS_USE_NA(currentComponent.voltageRange.typ)) {
        currentComponent.gndClampRef = global.gndClampRef;
      }

      if (goodies.IS_USE_NA(currentComponent.Rload))
        currentComponent.Rload = global.Rload;
      if (goodies.IS_USE_NA(currentComponent.derateVIPct))
        currentComponent.derateVIPct = global.derateVIPct;
      if (goodies.IS_USE_NA(currentComponent.derateRampPct))
        currentComponent.derateRampPct = global.derateRampPct;
      if (goodies.IS_USE_NA(currentComponent.clampTol))
        currentComponent.clampTol = global.clampTol;
      if (goodies.IS_USE_NA(currentComponent.simTime))
        currentComponent.simTime = global.simTime;
      if (goodies.IS_USE_NA(currentComponent.vil.typ) &&
        !goodies.IS_USE_NA(global.vil.typ))
        currentComponent.vil = global.vil;
      if (goodies.IS_USE_NA(currentComponent.vih.typ) &&
        !goodies.IS_USE_NA(global.vih.typ))
      {
        currentComponent.vih = global.vih;
      }
      if (goodies.IS_USE_NA(currentComponent.tr.typ) &&
        !goodies.IS_USE_NA(global.tr.typ))
        currentComponent.tr = global.tr;
      if (goodies.IS_USE_NA(currentComponent.tf.typ) &&
        !goodies.IS_USE_NA(global.tf.typ)) {
        currentComponent.tf = global.tf;
      }
      this.ibis.cList.current = currentComponent;
      this.ibis.cList.next();
    }
  }





  void copyComponentDataToModels() {
    this.ibis.cList.gototop();
    for (int i = 0; i < this.ibis.cList.count; i++) {

      ibisComponent currentComponent = this.ibis.cList.current;
      currentComponent.mList.gototop();
      for (int i1 = 0; i1 < currentComponent.mList.count; i1++) {

        ibisModel currentModel = currentComponent.mList.current;

        if (goodies.IS_USE_NA(currentModel.c_comp.typ))
          currentModel.c_comp = currentComponent.c_comp;
        if (goodies.IS_USE_NA(currentModel.tempRange.typ)) {
          currentModel.tempRange = currentComponent.tempRange;
        }
        if (goodies.IS_USE_NA(currentModel.voltageRange.typ) &&
          goodies.IS_USE_NA(currentModel.pullupRef.typ))
          currentModel.voltageRange = currentComponent.voltageRange;
        if (goodies.IS_USE_NA(currentModel.pullupRef.typ) &&
          goodies.IS_USE_NA(currentModel.voltageRange.typ))
          currentModel.pullupRef = currentComponent.pullupRef;
        if (goodies.IS_USE_NA(currentModel.pulldownRef.typ) &&
          goodies.IS_USE_NA(currentModel.voltageRange.typ))
          currentModel.pulldownRef = currentComponent.pulldownRef;
        if (goodies.IS_USE_NA(currentModel.powerClampRef.typ) &&
          goodies.IS_USE_NA(currentModel.voltageRange.typ))
          currentModel.powerClampRef = currentComponent.powerClampRef;
        if (goodies.IS_USE_NA(currentModel.gndClampRef.typ) &&
          goodies.IS_USE_NA(currentModel.voltageRange.typ)) {
          currentModel.gndClampRef = currentComponent.gndClampRef;
        }
        if (goodies.IS_USE_NA(currentModel.Rload))
          currentModel.Rload = currentComponent.Rload;
        if (goodies.IS_USE_NA(currentModel.derateVIPct))
          currentModel.derateVIPct = currentComponent.derateVIPct;
        if (goodies.IS_USE_NA(currentModel.derateRampPct))
          currentModel.derateRampPct = currentComponent.derateRampPct;
        if (goodies.IS_USE_NA(currentModel.clampTol))
          currentModel.clampTol = currentComponent.clampTol;
        if (goodies.IS_USE_NA(currentModel.simTime))
          currentModel.simTime = currentComponent.simTime;
        if (goodies.IS_USE_NA(currentModel.vil.typ))
          currentModel.vil = currentComponent.vil;
        if (goodies.IS_USE_NA(currentModel.vih.typ))
          currentModel.vih = currentComponent.vih;
        if (goodies.IS_USE_NA(currentModel.tr.typ))
          currentModel.tr = currentComponent.tr;
        if (goodies.IS_USE_NA(currentModel.tf.typ)) {
          currentModel.tf = currentComponent.tf;
        }
        currentComponent.mList.current = currentModel;
        currentComponent.mList.next();
      }
      this.ibis.cList.current = currentComponent;
      this.ibis.cList.next();
    }
  }




  int setModelDefaults() {
    this.ibis.cList.gototop();
    for (int i = 0; i < this.ibis.cList.count; i++) {

      ibisComponent currentComponent = this.ibis.cList.current;

      if (currentComponent.manufacturer.equalsIgnoreCase(""))
        currentComponent.manufacturer = "Manufacturer name";
      if (currentComponent.pinParasitics.R_pkg.typ == -1.33287736222333E20D) {

        currentComponent.pinParasitics.R_pkg.typ = 0.0D;
        currentComponent.pinParasitics.R_pkg.min = 0.0D;
        currentComponent.pinParasitics.R_pkg.max = 0.0D;
      }
      if (currentComponent.pinParasitics.L_pkg.typ == -1.33287736222333E20D) {

        currentComponent.pinParasitics.L_pkg.typ = 0.0D;
        currentComponent.pinParasitics.L_pkg.min = 0.0D;
        currentComponent.pinParasitics.L_pkg.max = 0.0D;
      }
      if (currentComponent.pinParasitics.C_pkg.typ == -1.33287736222333E20D) {

        currentComponent.pinParasitics.C_pkg.typ = 0.0D;
        currentComponent.pinParasitics.C_pkg.min = 0.0D;
        currentComponent.pinParasitics.C_pkg.max = 0.0D;
      }
      currentComponent.mList.gototop();

      for (int i1 = 0; i1 < currentComponent.mList.count; i1++) {

        ibisModel currentModel = currentComponent.mList.current;

        if (goodies.IS_USE_NA(currentModel.c_comp.typ)) {

          currentModel.c_comp.typ = 5.0E-12D;
          currentModel.c_comp.min = 5.0E-12D;
          currentModel.c_comp.max = 5.0E-12D;
        }
        if (goodies.IS_USE_NA(currentModel.tempRange.typ)) {

          currentModel.tempRange.typ = 27.0D;
          currentModel.tempRange.min = 100.0D;
          currentModel.tempRange.max = 0.0D;
        }
        if (goodies.IS_USE_NA(currentModel.voltageRange.typ) &&
          goodies.IS_USE_NA(currentModel.pullupRef.typ) &&
          goodies.IS_USE_NA(currentModel.powerClampRef.typ)) {

          currentModel.voltageRange.typ = 5.0D;
          currentModel.voltageRange.min = 4.5D;
          currentModel.voltageRange.max = 5.5D;
        }
        if (goodies.IS_USE_NA(currentModel.Rload))
          currentModel.Rload = 50.0D;
        if (goodies.IS_USE_NA(currentModel.derateVIPct))
          currentModel.derateVIPct = 0.0D;
        if (goodies.IS_USE_NA(currentModel.derateRampPct))
          currentModel.derateVIPct = 0.0D;
        if (goodies.IS_USE_NA(currentModel.clampTol))
          currentModel.clampTol = 0.0D;
        if (goodies.IS_USE_NA(currentModel.simTime)) {
          currentModel.simTime = 1.0E-8D;
        }
        if (goodies.IS_USE_NA(currentModel.vil.typ))
        {
          if (goodies.IS_USE_NA(currentModel.pulldownRef.typ)) {

            currentModel.vil.typ = 0.0D;
            currentModel.vil.min = 0.0D;
            currentModel.vil.max = 0.0D;
          } else {

            currentModel.vil = currentModel.pulldownRef;
          }  }
        if (goodies.IS_USE_NA(currentModel.vih.typ))
        {
          if (goodies.IS_USE_NA(currentModel.pullupRef.typ)) {
            currentModel.vih = currentModel.voltageRange;
          } else {
            currentModel.vih = currentModel.pullupRef;
          }  }
        if (goodies.IS_USE_NA(currentModel.tr.typ))
          currentModel.tr.typ = currentModel.simTime / 100.0D;
        if (goodies.IS_USE_NA(currentModel.tf.typ)) {
          currentModel.tf.typ = currentModel.simTime / 100.0D;
        }
        currentComponent.mList.current = currentModel;
        currentComponent.mList.next();
      }
      this.ibis.cList.current = currentComponent;
      this.ibis.cList.next();
    }
    return 0;
  }





  int copyPinMapToPins() {
    this.currentComponent.pList.gototop();
    for (int i = 0; i < this.currentComponent.pList.count; i++) {

      ibisPin currentPin = this.currentComponent.pList.current;

      ibisPinMap currentPinMap = getMatchingPinMap(currentPin.pinName,
          this.currentComponent.pmList);
      if (currentPinMap == null)
        return 1;
      currentPin.pullupRef = currentPinMap.pullupRef;
      currentPin.pulldownRef = currentPinMap.pulldownRef;
      currentPin.powerClampRef = currentPinMap.powerClampRef;
      currentPin.gndClampRef = currentPinMap.gndClampRef;

      this.currentComponent.pList.current = currentPin;
      this.currentComponent.pList.next();
    }
    return 0;
  }


  ibisPinMap getMatchingPinMap(String searchName, pinMapList pinMapList1) {
    pinMapList1.gototop();
    ibisPinMap tempPinMap = new ibisPinMap();
    tempPinMap = pinMapList1.current;

    if (searchName.equalsIgnoreCase(""))
      return null;
    while (tempPinMap != null &&
      !searchName.equalsIgnoreCase(tempPinMap.pinName)) {

      tempPinMap = pinMapList1.current;
      pinMapList1.next();
    }
    if (tempPinMap == null) {

      printf("Pin " + searchName + " not in pin map");
      printf("Please include the pin in the [Pin Mapping] section ");
      printf("of your  input file or make sure the pin name is not ");
      printf("misspelled");
    }

    return tempPinMap;
  }





  int copySeriesPinToPins() {
    this.currentComponent.pList.gototop();
    for (int i = 0; i < this.currentComponent.pList.count; i++) {

      ibisPin currentPin = this.currentComponent.pList.current;

      ibisSeriesPin currentSeriesPin = getMatchingSeriesPin(currentPin.pinName,
          this.currentComponent.spList);
      if (currentSeriesPin != null) {

        currentPin.seriesPin2name = currentSeriesPin.seriesPin2name;
        currentPin.seriesModel = currentSeriesPin.seriesModel;
        currentPin.fnTableGp = currentSeriesPin.fnTableGp;
      }
      this.currentComponent.pList.current = currentPin;
      this.currentComponent.pList.next();
    }
    return 0;
  }


  ibisSeriesPin getMatchingSeriesPin(String searchName, seriesPinsList spList) {
    ibisSeriesPin tempSeriesPin = new ibisSeriesPin();
    if (spList != null) {

      tempSeriesPin = spList.current;
      spList.gototop();

      if (searchName.equalsIgnoreCase(""))
        return null;
      while (tempSeriesPin != null &&
        !searchName.equalsIgnoreCase(tempSeriesPin.seriesPinName)) {

        tempSeriesPin = spList.current;
        spList.next();
      }
      if (tempSeriesPin == null)
        printf("Pin " + searchName + " not in Series Pin Map");
    }
    return tempSeriesPin;
  }
};

#endif

