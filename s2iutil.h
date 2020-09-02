/********************************************************************************
*FileName	: s2iutil.java
*Description	: This file contains the utility routines for creating,
*		: manipulating, printing and destroying various data
*		: structures used by s2ibis3.
*		: North Carolina State University
*		: Electronics Research Laboratory
********************************************************************************
Classes:
-------------------------------------------------
getMatchingPin
getMatchingModel
CompleteDataStructures
s2ibisPrint

$Log: s2iutil.java,v $
Revision 1.7  2006/03/27 18:08:56  akvarma
1. Removed '/t' from ibisWriter.println
2. Corrected the case for VinL and VinH
3. Corrected I/O_Open_Drain from I_O_Open_Drain
4. Changed to 2006 from 2005.

Revision 1.6  2005/02/24 22:47:36  akvarma
1. Changed to 2005 from 2003.
2. Cleanup code.

Revision 1.5  2003/11/24 05:42:15  akvarma
Removed test 'printf' code

Revision 1.4  2003/11/24 05:21:05  akvarma
Added series MOSFET functionality. Fixed 80 char limit per line. fixed other
minor errors. Cleaned up code

Revision 1.3  2003/08/04 16:55:40  akvarma
cleaned up code.
fixed BigDecimal to be able to show 4 decimal places instead of 2 in the tables.

Revision 1.2  2003/07/31 23:50:36  akvarma
Revised to make RisingWave and FallingWave tables as list so that multiple
tables can be generated.

Revision 1.1  2003/07/31 23:12:34  akvarma
Initial revision


* Copyright 2003, North Carolina State University.
*
* North Carolina State University (NCSU) and the author hereby disclaim
* all implied warranties, including the implied warranties of merchant-
* ability and fitness for a particular purpose. NCSU is not liable for
* any damages incurred by the use of this software and/or documentation,
* including direct, indirect, special, incidental, or consequential
* damages.
*
* NCSU grants the bearer the right to modify, copy, and redistribute
* this software and documentation, but requests that NCSU be acknowledged
* for its contribution in the resulting product.
*
**/

// import java.io.*;
// import java.util.*;
// import java.lang.string.* ;
// import java.awt.List;
// import java.math.*;

#include "s2iHeader.h"
/******************************************************************************
CLASS: getMatchingPin
******************************************************************************/

class getMatchingPin {
public:
  ibisPin getMatchingPin(string searchName, pinsList pinList) {
    pinList.gototop();
    ibisPin tempPin = new ibisPin();
    tempPin = pinList.current;

    if (searchName.equalsIgnoreCase(""))
      return (null);
    while ((tempPin != null) &&
           !(searchName.equalsIgnoreCase(tempPin.pinName))) {
      tempPin = pinList.current;
      pinList.next();
    }
    if (tempPin == null) {
      printf("Pin " + searchName + " Not Found in pin list");
    }
    return (tempPin);
  } // getMatchingPin method
};  // class getMatchingPin

/******************************************************************************
CLASS: getMatchingModel
******************************************************************************/

class getMatchingModel {
public:
  ibisModel getMatchingModel(string searchName, modelsList modelList) {
    modelList.gototop();
    ibisModel tempModel = new ibisModel();
    ;
    tempModel = modelList.current;

    if (searchName.equalsIgnoreCase(""))
      return (null);

    while ((tempModel != null) &&
           !(searchName.equalsIgnoreCase(tempModel.modelName))) {
      tempModel = modelList.current;
      modelList.next();
    }

    if (tempModel == null) {
      printf("Model " + searchName + " Not Found in model list");
    }
    return (tempModel);

  } // getMatchingModel method
};  // class getMatchingModel

/***********************************************************************
CLASS: CompleteDataStructures
Propogates global data values down to the component and model level
Methods for this class.
:linkPinsToModels
:linkSeriesPinsToSeriesModels
:copyPinMapToPins
:copyGlobalDataToComponents
:copyComponentDataToModels
:setModelDefaults
:getMatchingPinMap
:getMatchingSeriesPin
:copySeriesPinToPins
***********************************************************************/
class completeDataStructures {
  ibisTOP ibis;
  ibisComponent currentComponent;

public:
  int completeDataStructures(ibisGlobal global)

  {

    copyGlobalDataToComponents(global);
    copyComponentDataToModels();

    ibis.cList.gototop();
    for (int i = 0; i < ibis.cList.count; i++) {
      currentComponent = ibis.cList.current;
      if (currentComponent.hasPinMapping)
        if (copyPinMapToPins() == 1)
          return 1;
      if (linkPinsToModels() == 1)
        return 1;

      /**Comments on link methods
       */
      if (linkSeriesPinsToSeriesModels() == 1)
        return 1;
      if (copySeriesPinToPins() == 1)
        return 1;
      ibis.cList.current = currentComponent;
      ibis.cList.next();
    }
    ibis.cList.gototop();
    if (setModelDefaults() == 1)
      return 1;

    return 0;
  } // method completeDataStructures

public:
  int linkSeriesPinsToSeriesModels() {
    ibisModel currentSeriesModel = new ibisModel();
    ibisSeriesPin currentSeriesPin;
    getMatchingModel getMModel = new getMatchingModel();
    if (currentComponent.spList != null) {
      currentComponent.spList.gototop();
      for (int i = 0; i < currentComponent.spList.count; i++) {
        currentSeriesPin = currentComponent.spList.current;

        // series models are also part of the models - also the series models
        // name would be stored in the modelname field

        currentSeriesModel = getMModel.getMatchingModel(
            currentSeriesPin.modelName, currentComponent.mList);
        currentSeriesPin.seriesModel = currentSeriesModel;
        currentComponent.spList.current = currentSeriesPin;

        currentComponent.spList.next();
      }
    }
    return 0;
  }

public:
  int linkPinsToModels() {
    ibisModel currentModel = new ibisModel();
    ibisPin currentPin;
    getMatchingModel getMModel = new getMatchingModel();

    currentComponent.pList.gototop();
    for (int i = 0; i < currentComponent.pList.count; i++) {
      currentPin = currentComponent.pList.current;
      if (!(currentPin.modelName.equalsIgnoreCase("POWER") ||
            currentPin.modelName.equalsIgnoreCase("GND") ||
            currentPin.modelName.equalsIgnoreCase("NC"))) {
        currentModel = getMModel.getMatchingModel(currentPin.modelName,
                                                  currentComponent.mList);

        if (currentModel == null) {
          printf("Please check that you have correctly spelt the ");
          printf("model name for pin '" + currentPin.pinName + "'");
          printf(" in the [Pin] section of your input file and ");
          printf("that you have specified the model using the ");
          printf("[Model] keyword before the end of component ");
          printf(currentComponent.component);
          return 1;
        }
        currentPin.model = currentModel;
      }
      currentComponent.pList.current = currentPin;
      currentComponent.pList.next();
    }
    return 0;
  } // linkPinsToModels method

public:
  void copyGlobalDataToComponents(ibisGlobal global) {
    ibisComponent currentComponent;

    ibis.cList.gototop();

    for (int i = 0; i < ibis.cList.count; i++) {
      currentComponent = ibis.cList.current;
      if (goodies.IS_USE_NA(currentComponent.c_comp.typ))
        currentComponent.c_comp = global.c_comp;
      if (goodies.IS_USE_NA(currentComponent.pinParasitics.R_pkg.typ))
        currentComponent.pinParasitics.R_pkg = global.pinParasitics.R_pkg;
      if (goodies.IS_USE_NA(currentComponent.pinParasitics.L_pkg.typ))
        currentComponent.pinParasitics.L_pkg = global.pinParasitics.L_pkg;
      if (goodies.IS_USE_NA(currentComponent.pinParasitics.C_pkg.typ))
        currentComponent.pinParasitics.C_pkg = global.pinParasitics.C_pkg;
      if (goodies.IS_USE_NA(currentComponent.tempRange.typ))
        currentComponent.tempRange = global.tempRange;

      if (goodies.IS_USE_NA(currentComponent.voltageRange.typ) &&
          (goodies.IS_USE_NA(currentComponent.pullupRef.typ)))
        currentComponent.voltageRange = global.voltageRange;

      if (goodies.IS_USE_NA(currentComponent.pullupRef.typ) &&
          (goodies.IS_USE_NA(currentComponent.voltageRange.typ)))
        currentComponent.pullupRef = global.pullupRef;

      if (goodies.IS_USE_NA(currentComponent.pulldownRef.typ) &&
          (goodies.IS_USE_NA(currentComponent.voltageRange.typ)))
        currentComponent.pulldownRef = global.pulldownRef;

      if (goodies.IS_USE_NA(currentComponent.powerClampRef.typ) &&
          (goodies.IS_USE_NA(currentComponent.voltageRange.typ)))
        currentComponent.powerClampRef = global.powerClampRef;

      if (goodies.IS_USE_NA(currentComponent.gndClampRef.typ) &&
          (goodies.IS_USE_NA(currentComponent.voltageRange.typ)))
        currentComponent.gndClampRef = global.gndClampRef;

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
      if ((goodies.IS_USE_NA(currentComponent.vil.typ)) &&
          !(goodies.IS_USE_NA(global.vil.typ)))
        currentComponent.vil = global.vil;
      if ((goodies.IS_USE_NA(currentComponent.vih.typ)) &&
          !(goodies.IS_USE_NA(global.vih.typ))) {
        currentComponent.vih = global.vih;
      }
      if ((goodies.IS_USE_NA(currentComponent.tr.typ)) &&
          !(goodies.IS_USE_NA(global.tr.typ)))
        currentComponent.tr = global.tr;
      if ((goodies.IS_USE_NA(currentComponent.tf.typ)) &&
          !(goodies.IS_USE_NA(global.tf.typ)))
        currentComponent.tf = global.tf;

      ibis.cList.current = currentComponent;
      ibis.cList.next();
    }
  } // method copyGlobalDataToComponents

public:
  void copyComponentDataToModels() {
    ibisComponent currentComponent;
    ibisModel currentModel;

    ibis.cList.gototop();
    for (int i = 0; i < ibis.cList.count; i++) {
      currentComponent = ibis.cList.current;
      currentComponent.mList.gototop();
      for (int i1 = 0; i1 < currentComponent.mList.count; i1++) {
        currentModel = currentComponent.mList.current;

        if (goodies.IS_USE_NA(currentModel.c_comp.typ))
          currentModel.c_comp = currentComponent.c_comp;
        if (goodies.IS_USE_NA(currentModel.tempRange.typ))
          currentModel.tempRange = currentComponent.tempRange;

        if (goodies.IS_USE_NA(currentModel.voltageRange.typ) &&
            (goodies.IS_USE_NA(currentModel.pullupRef.typ)))
          currentModel.voltageRange = currentComponent.voltageRange;
        if (goodies.IS_USE_NA(currentModel.pullupRef.typ) &&
            (goodies.IS_USE_NA(currentModel.voltageRange.typ)))
          currentModel.pullupRef = currentComponent.pullupRef;
        if (goodies.IS_USE_NA(currentModel.pulldownRef.typ) &&
            (goodies.IS_USE_NA(currentModel.voltageRange.typ)))
          currentModel.pulldownRef = currentComponent.pulldownRef;
        if (goodies.IS_USE_NA(currentModel.powerClampRef.typ) &&
            (goodies.IS_USE_NA(currentModel.voltageRange.typ)))
          currentModel.powerClampRef = currentComponent.powerClampRef;
        if (goodies.IS_USE_NA(currentModel.gndClampRef.typ) &&
            (goodies.IS_USE_NA(currentModel.voltageRange.typ)))
          currentModel.gndClampRef = currentComponent.gndClampRef;

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
        if (goodies.IS_USE_NA(currentModel.tf.typ))
          currentModel.tf = currentComponent.tf;

        currentComponent.mList.current = currentModel;
        currentComponent.mList.next();
      }
      ibis.cList.current = currentComponent;
      ibis.cList.next();
    }
  } // method copyComponentDataToModels

public:
  int setModelDefaults() {
    ibisComponent currentComponent;
    ibisModel currentModel;
    ibis.cList.gototop();
    for (int i = 0; i < ibis.cList.count; i++) {
      currentComponent = ibis.cList.current;

      if (currentComponent.manufacturer.equalsIgnoreCase(""))
        currentComponent.manufacturer =
            ConstantStuff.MANUFACTURERS_NAME_DEFAULT;
      if (currentComponent.pinParasitics.R_pkg.typ == ConstantStuff.USE_NA) {
        currentComponent.pinParasitics.R_pkg.typ = ConstantStuff.R_PKG_DEFAULT;
        currentComponent.pinParasitics.R_pkg.min = ConstantStuff.R_PKG_DEFAULT;
        currentComponent.pinParasitics.R_pkg.max = ConstantStuff.R_PKG_DEFAULT;
      }
      if (currentComponent.pinParasitics.L_pkg.typ == ConstantStuff.USE_NA) {
        currentComponent.pinParasitics.L_pkg.typ = ConstantStuff.L_PKG_DEFAULT;
        currentComponent.pinParasitics.L_pkg.min = ConstantStuff.L_PKG_DEFAULT;
        currentComponent.pinParasitics.L_pkg.max = ConstantStuff.L_PKG_DEFAULT;
      }
      if (currentComponent.pinParasitics.C_pkg.typ == ConstantStuff.USE_NA) {
        currentComponent.pinParasitics.C_pkg.typ = ConstantStuff.C_PKG_DEFAULT;
        currentComponent.pinParasitics.C_pkg.min = ConstantStuff.C_PKG_DEFAULT;
        currentComponent.pinParasitics.C_pkg.max = ConstantStuff.C_PKG_DEFAULT;
      }
      currentComponent.mList.gototop();

      for (int i1 = 0; i1 < currentComponent.mList.count; i1++) {
        currentModel = currentComponent.mList.current;

        if (goodies.IS_USE_NA(currentModel.c_comp.typ)) {
          currentModel.c_comp.typ = ConstantStuff.C_COMP_DEFAULT;
          currentModel.c_comp.min = ConstantStuff.C_COMP_DEFAULT;
          currentModel.c_comp.max = ConstantStuff.C_COMP_DEFAULT;
        }
        if (goodies.IS_USE_NA(currentModel.tempRange.typ)) {
          currentModel.tempRange.typ = ConstantStuff.TEMP_TYP_DEFAULT;
          currentModel.tempRange.min = ConstantStuff.TEMP_MIN_DEFAULT;
          currentModel.tempRange.max = ConstantStuff.TEMP_MAX_DEFAULT;
        }
        if (goodies.IS_USE_NA(currentModel.voltageRange.typ) &&
            goodies.IS_USE_NA(currentModel.pullupRef.typ) &&
            goodies.IS_USE_NA(currentModel.powerClampRef.typ)) {
          currentModel.voltageRange.typ =
              ConstantStuff.VOLTAGE_RANGE_TYP_DEFAULT;
          currentModel.voltageRange.min =
              ConstantStuff.VOLTAGE_RANGE_MIN_DEFAULT;
          currentModel.voltageRange.max =
              ConstantStuff.VOLTAGE_RANGE_MAX_DEFAULT;
        }
        if (goodies.IS_USE_NA(currentModel.Rload))
          currentModel.Rload = ConstantStuff.RLOAD_DEFAULT;
        if (goodies.IS_USE_NA(currentModel.derateVIPct))
          currentModel.derateVIPct = ConstantStuff.DERATE_VI_PCT_DEFAULT;
        if (goodies.IS_USE_NA(currentModel.derateRampPct))
          currentModel.derateVIPct = ConstantStuff.DERATE_RAMP_PCT_DEFAULT;
        if (goodies.IS_USE_NA(currentModel.clampTol))
          currentModel.clampTol = ConstantStuff.CLAMP_TOLERANCE_DEFAULT;
        if (goodies.IS_USE_NA(currentModel.simTime))
          currentModel.simTime = ConstantStuff.SIM_TIME_DEFAULT;

        if (goodies.IS_USE_NA(currentModel.vil.typ)) {
          if (goodies.IS_USE_NA(currentModel.pulldownRef.typ)) {
            currentModel.vil.typ = 0;
            currentModel.vil.min = 0;
            currentModel.vil.max = 0;
          } else
            currentModel.vil = currentModel.pulldownRef;
        }
        if (goodies.IS_USE_NA(currentModel.vih.typ)) {
          if (goodies.IS_USE_NA(currentModel.pullupRef.typ))
            currentModel.vih = currentModel.voltageRange;
          else
            currentModel.vih = currentModel.pullupRef;
        }
        if (goodies.IS_USE_NA(currentModel.tr.typ))
          currentModel.tr.typ = currentModel.simTime / 100;
        if (goodies.IS_USE_NA(currentModel.tf.typ))
          currentModel.tf.typ = currentModel.simTime / 100;

        currentComponent.mList.current = currentModel;
        currentComponent.mList.next();
      }
      ibis.cList.current = currentComponent;
      ibis.cList.next();
    }
    return 0;
  } // method setModelDefaults

public:
  int copyPinMapToPins() {
    ibisPinMap currentPinMap;
    ibisPin currentPin;

    currentComponent.pList.gototop();
    for (int i = 0; i < currentComponent.pList.count; i++) {
      currentPin = currentComponent.pList.current;

      currentPinMap =
          getMatchingPinMap(currentPin.pinName, currentComponent.pmList);
      if (currentPinMap == null)
        return 1;
      currentPin.pullupRef = currentPinMap.pullupRef;
      currentPin.pulldownRef = currentPinMap.pulldownRef;
      currentPin.powerClampRef = currentPinMap.powerClampRef;
      currentPin.gndClampRef = currentPinMap.gndClampRef;

      currentComponent.pList.current = currentPin;
      currentComponent.pList.next();
    }
    return 0;
  } // method copyPinMapToPins

public:
  ibisPinMap getMatchingPinMap(string searchName, pinMapList pinMapList) {
    pinMapList.gototop();
    ibisPinMap tempPinMap = new ibisPinMap();
    tempPinMap = pinMapList.current;

    if (searchName.equalsIgnoreCase(""))
      return (null);
    while ((tempPinMap != null) &&
           !(searchName.equalsIgnoreCase(tempPinMap.pinName))) {
      tempPinMap = pinMapList.current;
      pinMapList.next();
    }
    if (tempPinMap == null) {
      printf("Pin " + searchName + " not in pin map");
      printf("Please include the pin in the [Pin Mapping] section ");
      printf("of your  input file or make sure the pin name is not ");
      printf("misspelled");
    }

    return (tempPinMap);
  } // method getMatchingPinMap

public:
  int copySeriesPinToPins() {
    ibisSeriesPin currentSeriesPin;
    ibisPin currentPin;

    currentComponent.pList.gototop();
    for (int i = 0; i < currentComponent.pList.count; i++) {
      currentPin = currentComponent.pList.current;

      currentSeriesPin =
          getMatchingSeriesPin(currentPin.pinName, currentComponent.spList);
      if (currentSeriesPin != null) {
        currentPin.seriesPin2name = currentSeriesPin.seriesPin2name;
        currentPin.seriesModel = currentSeriesPin.seriesModel;
        currentPin.fnTableGp = currentSeriesPin.fnTableGp;
      }
      currentComponent.pList.current = currentPin;
      currentComponent.pList.next();
    }
    return 0;
  } // method copySeriesPinToPins

public:
  ibisSeriesPin getMatchingSeriesPin(string searchName, seriesPinsList spList) {
    ibisSeriesPin tempSeriesPin = new ibisSeriesPin();
    if (spList != null) {
      tempSeriesPin = spList.current;
      spList.gototop();

      if (searchName.equalsIgnoreCase(""))
        return (null);
      while ((tempSeriesPin != null) &&
             !(searchName.equalsIgnoreCase(tempSeriesPin.seriesPinName))) {
        tempSeriesPin = spList.current;
        spList.next();
      }
      if (tempSeriesPin == null)
        printf("Pin " + searchName + " not in Series Pin Map");
    }
    return (tempSeriesPin);
  } // method getMatchingSeriesPin

}; // class completeDataStructures

/******************************************************************************
CLASS: s2ibisPrint

printMain			   printWaveTable
print_TOP			   printRamp
printComponent			   spaceFill
getModelTypeAsString 		   Get_TypMinMax_as_string
printModel 			   Get_Double_as_string
printPin 			   isExponent
printDiffPin 			   printTypMinMaxHeader
print_VItable 			   printHeader
printClampTable 		   printString
******************************************************************************/

class s2ibisPrint {
  ibisTOP ibisHead;

public:
  void printMain() {
    File outFile = new File(ibisHead.thisFileName);

    try {
      PrintWriter ibisWriter =
          new PrintWriter(new BufferedWriter(new FileWriter(outFile)));

      printf("Opening file " + ibisHead.thisFileName + " for writing ...");

      /*-------------------------------------------------------------------------
       *	Check to make sure we can open the file for writing.  If not,
       *	return an error.  If so, begin creating the ibis file.
       *--------------------------------------------------------------------*/
      if (!(outFile.canWrite())) {
        printf("Unable to open " + outFile + "for writing");
        return;
      }

      print_TOP(ibisWriter);
      ibisWriter.close();
      printf("done.");
    } catch (Exception ex) {
      printf("Exception while writing ibis output file (printMain): " +
             ex.toString() + ": ");
      ex.printStackTrace();
    }
  } // method printMain
public:
  void print_TOP(PrintWriter ibisWriter) {
    ibisComponent tempComponent = new ibisComponent();
    ibisComponent tempComponent2 = new ibisComponent();
    string headerString;
    string version;
    ibisWriter.println("|******************************************************"
                       "******************");
    ibisWriter.println("| IBIS file " + ibisHead.thisFileName +
                       " created by s2ibis3 verion " +
                       ConstantStuff.VERSION_STRING);
    ibisWriter.println("| North Carolina State University, ERL, 2006");
    ibisWriter.println("|******************************************************"
                       "******************");
    version = print_IBIS_Version(ibisWriter, ibisHead.ibisVersion);
    printString(ibisWriter, "[IBIS ver]", ConstantStuff.MAX_LINE_LENGTH,
                version);
    ibisWriter.println("[File name] " + ibisHead.thisFileName);
    ibisWriter.println("[File Rev] " + ibisHead.fileRev);
    ibisWriter.println("[Date]  " + ibisHead.date);
    if (!(ibisHead.source.equals("")))
      printString(ibisWriter, "[Source]", ConstantStuff.MAX_LINE_LENGTH,
                  ibisHead.source);
    if (!(ibisHead.notes.equals("")))
      printString(ibisWriter, "[Notes]", ConstantStuff.MAX_LINE_LENGTH,
                  ibisHead.notes);
    if (!(ibisHead.disclaimer.equals("")))
      printString(ibisWriter, "[Disclaimer]", ConstantStuff.MAX_LINE_LENGTH,
                  ibisHead.disclaimer);
    if ((ibisHead.ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(ibisHead.copyright.equals(""))))
      printString(ibisWriter, "[Copyright]", ConstantStuff.MAX_LINE_LENGTH,
                  ibisHead.copyright);

    // Because the Linked List gives out first the components that went in last,
    // a second Component List is made to reverse the order.

    componentList compListForPrint = new componentList();
    ibisHead.cList.gototop();
    for (int i1 = 0; i1 < ibisHead.cList.count; i1++) {
      tempComponent2 = ibisHead.cList.current;
      ibisHead.cList.next();
      compListForPrint.add(tempComponent2);
    }

    // PRINT COMPONENTS (this one prints in correct order)
    compListForPrint.gototop();
    for (int i1 = 0; i1 < compListForPrint.count; i1++) {
      tempComponent2 = compListForPrint.current;
      printComponent(ibisWriter, tempComponent2, ibisHead.ibisVersion);
      compListForPrint.next();
    }
    ibisWriter.println("[End]");
  } // method print_TOP

  /****************************************************************
  **************Print IBIS Version Routine
  ****************************************************************/
  string print_IBIS_Version(PrintWriter ibisWriter, int ibisVersion) {
    string s = "";
    if (ibisVersion == ConstantStuff.VERSION_ONE_ZERO)
      s = "1.0";
    else if (ibisVersion == ConstantStuff.VERSION_ONE_ONE)
      s = "1.1";
    if (ibisVersion == ConstantStuff.VERSION_TWO_ZERO)
      s = "2.0";
    else if (ibisVersion == ConstantStuff.VERSION_TWO_ONE)
      s = "2.1";
    else if (ibisVersion == ConstantStuff.VERSION_THREE_TWO)
      s = "3.2";
    else
      s = "unknown";
    return s;
  }

  /****************************************************************
  **************Print Component Routine
  ****************************************************************/
  void printComponent(PrintWriter ibisWriter, ibisComponent component,
                      int ibisVersion) {
    ibisModel tempModel = null;
    ibisPin tempPin = null;
    ibisSeriesPin tempSeriesPin = null;
    seriesSwitchGroup tempSeriesSwitchGp = null;
    ibisPinMap tempPinMap = null;
    ibisDiffPin tempDiffPin = null;
    string s;
    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");

    // Print component Header
    printHeader(ibisWriter, component.component, "Component");
    printString(ibisWriter, "[Component]", ConstantStuff.MAX_LINE_LENGTH,
                component.component);
    printString(ibisWriter, "[Manufacturer]", ConstantStuff.MAX_LINE_LENGTH,
                component.manufacturer);

    /*Package*/

    printString(ibisWriter, "[Package]", ConstantStuff.MAX_LINE_LENGTH, "");
    printTypMinMaxHeader(ibisWriter);

    s = Get_TypMinMax_as_string(component.pinParasitics.R_pkg, "");
    printString(ibisWriter, "R_pkg", ConstantStuff.MAX_LINE_LENGTH, s);
    s = Get_TypMinMax_as_string(component.pinParasitics.L_pkg, "H");
    printString(ibisWriter, "L_pkg", ConstantStuff.MAX_LINE_LENGTH, s);

    s = Get_TypMinMax_as_string(component.pinParasitics.C_pkg, "F");
    printString(ibisWriter, "C_pkg", ConstantStuff.MAX_LINE_LENGTH, s);

    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");

    /*
     *Print the pin List
     */
    component.pList.gototop();
    if (component.pList != null) {
      ibisWriter.println("[Pin]  signal_name          model_name           "
                         "R_pin     L_pin     C_pin");
      for (int i = 0; i < component.pList.count; i++) {
        tempPin = component.pList.current;
        printPin(ibisWriter, tempPin);
        component.pList.next();
      }
      printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");
    }

    /*
     *If there is a pin map and it is not version 1.1, print it.
     */
    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (component.hasPinMapping)) {
      component.pmList.gototop();
      ibisWriter.println("[Pin Mapping]  pulldown_ref    pullup_ref      "
                         "gnd_clamp_ref   power_clamp_ref");
      printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");
      for (int i = 0; i < component.pmList.count; i++) {
        tempPinMap = component.pmList.current;
        printPinMap(ibisWriter, tempPinMap);
        component.pmList.next();
      }
      printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");
    }

    /*
     *If there is a diff pin list and it is not version 1.1, print it.
     */
    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (component.dpList != null)) {
      component.dpList.gototop();
      if (component.dpList.count != 0)
        ibisWriter.println(
            "[Diff pin]  inv_pin  vdiff  tdelay_typ  tdelay_min  tdelay_max");
      printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");
      for (int i = 0; i < component.dpList.count; i++) {
        tempDiffPin = component.dpList.current;
        printDiffPin(ibisWriter, tempDiffPin);
        component.dpList.next();
      }
      printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");
    }

    /*
     *If there is a Series Pin Map List Print it.
     */
    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (component.spList != null)) {
      component.spList.gototop();
      if (component.spList.count != 0)
        ibisWriter.println("[Series Pin Mapping]  pin_2        model_name      "
                           "  function_table_group");
      for (int i = 0; i < component.spList.count; i++) {
        tempSeriesPin = component.spList.current;
        printSeriesPin(ibisWriter, tempSeriesPin);
        component.spList.next();
      }
      printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");
    }

    /*
     *If there is a Series Switch Group List Print it.
     */
    if (component.ssgList != null) {
      seriesSwitchGpList ssgListForPrint = new seriesSwitchGpList();
      component.ssgList.gototop();
      for (int i1 = 0; i1 < component.ssgList.count; i1++) {
        tempSeriesSwitchGp = component.ssgList.current;
        component.ssgList.next();
        ssgListForPrint.add(tempSeriesSwitchGp);
      }

      tempSeriesSwitchGp = new seriesSwitchGroup();

      if (component.ssgList.count != 0)
        ibisWriter.println("[Series Switch Groups]");
      for (int i = 0; i < ssgListForPrint.count; i++) {
        tempSeriesSwitchGp = ssgListForPrint.current;
        printSeriesSwitchGp(ibisWriter, tempSeriesSwitchGp);
        ssgListForPrint.next();
      }
      printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");
    }

    /*
     *Print all the model results
     */
    component.mList.gototop();

    for (int i1 = 0; i1 < component.mList.count; i1++) {
      tempModel = component.mList.current;
      if (tempModel.noModel == 0) {
        printModel(ibisWriter, tempModel, ibisHead.ibisVersion);
      }
      component.mList.next();
    }
    printString(ibisWriter, "|End [Component]", ConstantStuff.MAX_LINE_LENGTH,
                "");
  } // method printComponent

  /****************************************************************
  **************Print Diff Pin Routine
  ****************************************************************/
  void printDiffPin(PrintWriter ibisWriter, ibisDiffPin diffPin) {
    string tempBuf;
    string numBuf;

    tempBuf = diffPin.pinName;
    tempBuf = spaceFill(tempBuf, 12 - tempBuf.length());
    tempBuf = tempBuf + diffPin.invPin;
    tempBuf = spaceFill(tempBuf, 21 - tempBuf.length());
    numBuf = Get_Double_as_string(diffPin.vdiff, "V");
    tempBuf = tempBuf + numBuf;
    tempBuf = spaceFill(tempBuf, 31 - tempBuf.length());
    numBuf = Get_Double_as_string(diffPin.tdelay_typ, "s");
    tempBuf = tempBuf + numBuf;

    if (!(goodies.IS_NOT_USED(diffPin.tdelay_min))) {
      tempBuf = spaceFill(tempBuf, 43 - tempBuf.length());
      numBuf = Get_Double_as_string(diffPin.tdelay_min, "s");
      tempBuf = tempBuf + numBuf;
      tempBuf = spaceFill(tempBuf, 55 - tempBuf.length());
      numBuf = Get_Double_as_string(diffPin.tdelay_max, "s");
      tempBuf = tempBuf + numBuf;
    }
    printString(ibisWriter, tempBuf, ConstantStuff.MAX_LINE_LENGTH, "");
  }

  /****************************************************************
  **************Print Pin Map Routine
  ****************************************************************/
  void printPinMap(PrintWriter ibisWriter, ibisPinMap pinMap) {
    string tempBuf;
    tempBuf = pinMap.pinName;
    tempBuf = spaceFill(tempBuf, 15 - tempBuf.length());
    tempBuf = tempBuf + pinMap.pulldownRef;
    tempBuf = spaceFill(tempBuf, 31 - tempBuf.length());
    tempBuf = tempBuf + pinMap.pullupRef;
    tempBuf = spaceFill(tempBuf, 47 - tempBuf.length());
    tempBuf = tempBuf + pinMap.gndClampRef;
    tempBuf = spaceFill(tempBuf, 63 - tempBuf.length());
    tempBuf = tempBuf + pinMap.powerClampRef;

    printString(ibisWriter, tempBuf, ConstantStuff.MAX_LINE_LENGTH, "");
  }
  /****************************************************************
  **************Print Pin Routine
  ****************************************************************/
  void printPin(PrintWriter ibisWriter, ibisPin pin) {
    string s;
    string tempBuf;

    /**If the model associated with this pin had a NoModel switsh set
     *print an ibis Comment Char at the beginning of the pin Line.
     **/
    if (pin.model != null)
      if (pin.model.noModel == 1)
        s = "|";
      else
        s = "";
    else
      s = "";

    /**Print the rest of the Pin*/
    s = s + pin.pinName;
    s = spaceFill(s, 7 - s.length());
    s = s + pin.signalName;
    s = spaceFill(s, 28 - s.length());
    s = s + pin.modelName;
    if (!(goodies.IS_NOT_USED(pin.R_pin))) {
      s = spaceFill(s, 49 - s.length());
      tempBuf = Get_Double_as_string(pin.R_pin, "");
      s = s + tempBuf;
      s = spaceFill(s, 59 - s.length());
      tempBuf = Get_Double_as_string(pin.L_pin, "H");
      s = s + tempBuf;
      s = spaceFill(s, 69 - s.length());
      tempBuf = Get_Double_as_string(pin.C_pin, "F");
      s = s + tempBuf;
    }
    printString(ibisWriter, s, ConstantStuff.MAX_LINE_LENGTH, "");
  }

  /****************************************************************
  **************Print Series Pin Routine
  ****************************************************************/
  void printSeriesPin(PrintWriter ibisWriter, ibisSeriesPin seriesPin) {
    string s = "";
    string tempBuf;

    /**If the model associated with this pin had a NoModel switsh set
     *print an ibis Comment Char at the beginning of the pin Line.
     **/
    /**Print the rest of the Pin*/
    s = s + seriesPin.seriesPinName;
    s = spaceFill(s, 7 - s.length());
    s = s + seriesPin.seriesPin2name;
    s = spaceFill(s, 28 - s.length());
    s = s + seriesPin.modelName;
    s = spaceFill(s, 49 - s.length());
    if (seriesPin.fnTableGp != null)
      s = s + seriesPin.fnTableGp;
    else
      s = s + ""; // changed from "NA" to ""

    printString(ibisWriter, s, ConstantStuff.MAX_LINE_LENGTH, "");
  }

  /****************************************************************
  **************Print Series Switch Group Routine
  ****************************************************************/
  void printSeriesSwitchGp(PrintWriter ibisWriter,
                           seriesSwitchGroup seriesSwitchGp) {
    string s = "";
    string tempBuf;

    s = s + seriesSwitchGp.state;
    for (int i = 0; i < seriesSwitchGp.groupNames.length; i++) {
      s = s + " " + seriesSwitchGp.groupNames[i];
    }

    printString(ibisWriter, s, ConstantStuff.MAX_LINE_LENGTH, "/");
  }
  /****************************************************************
  **************Print Model Routine
  ****************************************************************/
  void printModel(PrintWriter ibisWriter, ibisModel model, int ibisVersion) {
    waveTableList risingWaveL;
    waveTableList fallingWaveL;
    ibisWaveTable risingWave;
    ibisWaveTable fallingWave;

    // series
    //  VITableList	seriesVITableL;
    VdsList VdsList1;
    ibisVItable seriesVITable;
    // series
    string s = "";
    string numberBuffer = "";

    /**Model Header */
    printHeader(ibisWriter, model.modelName, "Model");
    printString(ibisWriter, "[Model]", ConstantStuff.MAX_LINE_LENGTH,
                model.modelName);

    /**Model type */
    s = getModelTypeAsString(model.modelType);
    printString(ibisWriter, "Model_type", ConstantStuff.MAX_LINE_LENGTH, s);

    /**Polarity */
    if (model.polarity == ConstantStuff.MODEL_POLARITY_NON_INVERTING)
      s = "Non-Inverting";
    else if (model.polarity == ConstantStuff.MODEL_POLARITY_INVERTING)
      s = "Inverting";
    else if (model.polarity == ConstantStuff.MODEL_TYPE_UNDEFINED)
      s = "";

    if (!s.equals(""))
      printString(ibisWriter, "Polarity      ", ConstantStuff.MAX_LINE_LENGTH,
                  s);

    /**Enable */
    if (model.enable == ConstantStuff.MODEL_ENABLE_ACTIVE_HIGH)
      s = "Active-High";
    else if (model.enable == ConstantStuff.MODEL_ENABLE_ACTIVE_LOW)
      s = "Active-Low";
    else if (model.enable == ConstantStuff.MODEL_TYPE_UNDEFINED)
      s = "";

    if (!s.equals(""))
      printString(ibisWriter, "Enable       ", ConstantStuff.MAX_LINE_LENGTH,
                  s);

    if (!(goodies.IS_USE_NA(model.Vinl))) {
      s = Get_Double_as_string(model.Vinl, "V");
      printString(ibisWriter, "Vinl = ", ConstantStuff.MAX_LINE_LENGTH, s);
    }

    if (!(goodies.IS_USE_NA(model.Vinh))) {
      s = Get_Double_as_string(model.Vinh, "V");
      printString(ibisWriter, "Vinh = ", ConstantStuff.MAX_LINE_LENGTH, s);
    }

    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.Vmeas)))) {
      s = Get_Double_as_string(model.Vmeas, "V");
      printString(ibisWriter, "Vmeas = ", ConstantStuff.MAX_LINE_LENGTH, s);
    }

    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.Cref)))) {
      s = Get_Double_as_string(model.Cref, "F");
      printString(ibisWriter, "Cref = ", ConstantStuff.MAX_LINE_LENGTH, s);
    }
    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.Rref)))) {
      s = Get_Double_as_string(model.Rref, "");
      printString(ibisWriter, "Rref = ", ConstantStuff.MAX_LINE_LENGTH, s);
    }
    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.Vref)))) {
      s = Get_Double_as_string(model.Vref, "V");
      printString(ibisWriter, "Vref = ", ConstantStuff.MAX_LINE_LENGTH, s);
    }

    s = Get_TypMinMax_as_string(model.c_comp, "F");
    printString(ibisWriter, "C_comp", ConstantStuff.MAX_LINE_LENGTH, s);

    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.Rgnd.typ)))) {
      s = Get_TypMinMax_as_string(model.Rgnd, "");
      printString(ibisWriter, "[Rgnd]      ", ConstantStuff.MAX_LINE_LENGTH, s);
    }
    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.Rpower.typ)))) {
      s = Get_TypMinMax_as_string(model.Rpower, "");
      printString(ibisWriter, "[Rpower]     ", ConstantStuff.MAX_LINE_LENGTH,
                  s);
    }
    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.Rac.typ)))) {
      s = Get_TypMinMax_as_string(model.Rac, "");
      printString(ibisWriter, "[Rac]     ", ConstantStuff.MAX_LINE_LENGTH, s);
    }
    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.Cac.typ)))) {
      s = Get_TypMinMax_as_string(model.Cac, "F");
      printString(ibisWriter, "[Cac]     ", ConstantStuff.MAX_LINE_LENGTH, s);
    }
    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");
    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");

    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.tempRange.typ)))) {
      s = Get_TypMinMax_as_string(model.tempRange, "");
      printString(ibisWriter, "[Temperature Range]",
                  ConstantStuff.MAX_LINE_LENGTH, s);
    }

    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.voltageRange.typ)))) {
      s = Get_TypMinMax_as_string(model.voltageRange, "V");
      printString(ibisWriter, "[Voltage Range]     ",
                  ConstantStuff.MAX_LINE_LENGTH, s);
    }

    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.pullupRef.typ)))) {
      s = Get_TypMinMax_as_string(model.pullupRef, "V");
      printString(ibisWriter, "[Pullup Reference]     ",
                  ConstantStuff.MAX_LINE_LENGTH, s);
    }

    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.pulldownRef.typ)))) {
      s = Get_TypMinMax_as_string(model.pulldownRef, "V");
      printString(ibisWriter, "[Pulldown Reference]     ",
                  ConstantStuff.MAX_LINE_LENGTH, s);
    }

    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.powerClampRef.typ)))) {
      s = Get_TypMinMax_as_string(model.powerClampRef, "V");
      printString(ibisWriter, "[POWER Clamp Reference]     ",
                  ConstantStuff.MAX_LINE_LENGTH, s);
    }

    if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
        (!(goodies.IS_USE_NA(model.gndClampRef.typ)))) {
      s = Get_TypMinMax_as_string(model.gndClampRef, "V");
      printString(ibisWriter, "[GND Clamp Reference]     ",
                  ConstantStuff.MAX_LINE_LENGTH, s);
    }

    if (model.pulldown != null) {
      printString(ibisWriter, "[Pulldown]", ConstantStuff.MAX_LINE_LENGTH, "");
      print_VItable(ibisWriter, model.pulldown);
    }

    if (model.pullup != null) {
      printString(ibisWriter, "[Pullup]", ConstantStuff.MAX_LINE_LENGTH, "");
      print_VItable(ibisWriter, model.pullup);
    }
    if (model.gnd_clamp != null) {
      printString(ibisWriter, "[GND_clamp]", ConstantStuff.MAX_LINE_LENGTH, "");
      printClampTable(ibisWriter, model.gnd_clamp, model.clampTol);
    }
    if (model.power_clamp != null) {
      printString(ibisWriter, "[POWER_clamp]", ConstantStuff.MAX_LINE_LENGTH,
                  "");
      printClampTable(ibisWriter, model.power_clamp, model.clampTol);
    }
    if (!(goodies.IS_USE_NA(model.ramp.dv_r.typ))) {
      printRamp(ibisWriter, model.ramp, model.Rload);
    }

    // series
    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE) {
      VdsList1 = model.seriesModel.series_MOSFET.vdslist;
      VdsList1.gototop();
      if (model.seriesModel.OnState) {
        printString(ibisWriter, "[On]", ConstantStuff.MAX_LINE_LENGTH, "");
      }
      for (int i = 0; i < VdsList1.count; i++) {
        seriesVITable = VdsList1.current.seriesVITable;

        printString(ibisWriter, "[series MOSFET]",
                    ConstantStuff.MAX_LINE_LENGTH, "");
        numberBuffer = Get_Double_as_string(VdsList1.current.V, "");
        printString(ibisWriter, "Vds = ", ConstantStuff.MAX_LINE_LENGTH,
                    numberBuffer);
        print_VItable(ibisWriter, VdsList1.current.seriesVITable);

        VdsList1.next();
      }
      if (model.seriesModel.OffState) {
        printString(ibisWriter, "[Off]", ConstantStuff.MAX_LINE_LENGTH, "");
      }
      if ((ibisVersion != ConstantStuff.VERSION_ONE_ONE) &&
          (!(goodies.IS_USE_NA(model.seriesModel.RSeriesOff.typ)))) {
        s = Get_TypMinMax_as_string(model.seriesModel.RSeriesOff, "");
        printString(ibisWriter, "[R Series]     ",
                    ConstantStuff.MAX_LINE_LENGTH, s);
      }
    }
    // series

    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE) {
      risingWaveL = model.risingWaveList;
      fallingWaveL = model.fallingWaveList;

      risingWaveL.gototop();
      fallingWaveL.gototop();

      for (int i = 0; i < risingWaveL.count; i++) {
        risingWave = risingWaveL.current;
        printString(ibisWriter, "[Rising Waveform]",
                    ConstantStuff.MAX_LINE_LENGTH, "");
        numberBuffer = Get_Double_as_string(risingWave.R_fixture, "");
        printString(ibisWriter, "R_fixture=", ConstantStuff.MAX_LINE_LENGTH,
                    numberBuffer);
        numberBuffer = Get_Double_as_string(risingWave.V_fixture, "");
        printString(ibisWriter, "V_fixture=", ConstantStuff.MAX_LINE_LENGTH,
                    numberBuffer);

        if (!(goodies.IS_USE_NA(risingWave.V_fixture_min))) {
          numberBuffer = Get_Double_as_string(risingWave.V_fixture_min, "");
          printString(ibisWriter,
                      "V_fixture_min=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }
        if (!(goodies.IS_USE_NA(risingWave.V_fixture_max))) {
          numberBuffer = Get_Double_as_string(risingWave.V_fixture_max, "");
          printString(ibisWriter,
                      "V_fixture_max=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }
        if (!(goodies.IS_USE_NA(risingWave.L_fixture))) {
          numberBuffer = Get_Double_as_string(risingWave.L_fixture, "H");
          printString(ibisWriter, "L_fixture=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }
        if (!(goodies.IS_USE_NA(risingWave.C_fixture))) {
          numberBuffer = Get_Double_as_string(risingWave.C_fixture, "F");
          printString(ibisWriter, "C_fixture=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }
        if (!(goodies.IS_USE_NA(risingWave.R_dut))) {
          numberBuffer = Get_Double_as_string(risingWave.R_dut, "");
          printString(ibisWriter, "R_dut=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }
        if (!(goodies.IS_USE_NA(risingWave.L_dut))) {
          numberBuffer = Get_Double_as_string(risingWave.L_dut, "L");
          printString(ibisWriter, "L_dut=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }
        if (!(goodies.IS_USE_NA(risingWave.C_dut))) {
          numberBuffer = Get_Double_as_string(risingWave.L_dut, "F");
          printString(ibisWriter, "C_dut=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }

        printWaveTable(ibisWriter, risingWave);
        risingWaveL.next();
      }
      for (int i = 0; i < fallingWaveL.count; i++) {
        fallingWave = fallingWaveL.current;
        printString(ibisWriter, "[Falling Waveform]",
                    ConstantStuff.MAX_LINE_LENGTH, "");
        numberBuffer = Get_Double_as_string(fallingWave.R_fixture, "");
        printString(ibisWriter, "R_fixture=", ConstantStuff.MAX_LINE_LENGTH,
                    numberBuffer);
        numberBuffer = Get_Double_as_string(fallingWave.V_fixture, "");
        printString(ibisWriter, "V_fixture=", ConstantStuff.MAX_LINE_LENGTH,
                    numberBuffer);

        if (!(goodies.IS_USE_NA(fallingWave.V_fixture_min))) {
          numberBuffer = Get_Double_as_string(fallingWave.V_fixture_min, "");
          printString(ibisWriter,
                      "V_fixture_min=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }
        if (!(goodies.IS_USE_NA(fallingWave.V_fixture_max))) {
          numberBuffer = Get_Double_as_string(fallingWave.V_fixture_max, "");
          printString(ibisWriter,
                      "V_fixture_max=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }
        if (!(goodies.IS_USE_NA(fallingWave.L_fixture))) {
          numberBuffer = Get_Double_as_string(fallingWave.L_fixture, "H");
          printString(ibisWriter, "L_fixture=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }
        if (!(goodies.IS_USE_NA(fallingWave.C_fixture))) {
          numberBuffer = Get_Double_as_string(fallingWave.C_fixture, "F");
          printString(ibisWriter, "C_fixture=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }
        if (!(goodies.IS_USE_NA(fallingWave.R_dut))) {
          numberBuffer = Get_Double_as_string(fallingWave.R_dut, "");
          printString(ibisWriter, "R_dut=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }
        if (!(goodies.IS_USE_NA(fallingWave.L_dut))) {
          numberBuffer = Get_Double_as_string(fallingWave.L_dut, "L");
          printString(ibisWriter, "L_dut=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }
        if (!(goodies.IS_USE_NA(fallingWave.C_dut))) {
          numberBuffer = Get_Double_as_string(fallingWave.L_dut, "F");
          printString(ibisWriter, "C_dut=", ConstantStuff.MAX_LINE_LENGTH,
                      numberBuffer);
        }

        printWaveTable(ibisWriter, fallingWave);
        fallingWaveL.next();
      }
    }
    s = "|End [Model] " + model.modelName;
    printString(ibisWriter, s, ConstantStuff.MAX_LINE_LENGTH, "");

  } // method printModel

  /****************************************************************
  ************** getModelTypeAsString Routine
  ****************************************************************/
  string getModelTypeAsString(int modelType) {
    string s = "";
    if (modelType == ConstantStuff.MODEL_TYPE_INPUT)
      s = "Input";
    else if (modelType == ConstantStuff.MODEL_TYPE_OUTPUT)
      s = "Output";
    else if (modelType == ConstantStuff.MODEL_TYPE_3_STATE)
      s = "3-state";
    else if (modelType == ConstantStuff.MODEL_TYPE_OPEN_DRAIN)
      s = "Open_drain";
    else if (modelType == ConstantStuff.MODEL_TYPE_I_O)
      s = "I/O";
    else if (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN)
      s = "I/O_Open_Drain";
    else if (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK)
      s = "I/O_open_sink";
    else if (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE)
      s = "I/O_open_source";
    else if (modelType == ConstantStuff.MODEL_TYPE_INPUT_ECL)
      s = "Input_ECL";
    else if (modelType == ConstantStuff.MODEL_TYPE_I_O_ECL)
      s = "I/O_ECL";
    else if (modelType == ConstantStuff.MODEL_TYPE_TERMINATOR)
      s = "Terminator";
    else if (modelType == ConstantStuff.MODEL_TYPE_OPEN_SINK)
      s = "Open_sink";
    else if (modelType == ConstantStuff.MODEL_TYPE_OPEN_SOURCE)
      s = "Open_Source";
    else if (modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL)
      s = "Output_ECL";

    else if (modelType == ConstantStuff.MODEL_TYPE_SERIES)
      s = "Series";
    else if (modelType == ConstantStuff.MODEL_TYPE_SERIES_SWITCH)
      s = "Series_switch";

    else if (modelType == ConstantStuff.MODEL_TYPE_UNDEFINED)
      s = "??undefined??";
    else
      s = "??undefined??";

    return s;
  }
  /****************************************************************
  **************Print VI Table Routine
  ****************************************************************/
  int print_VItable(PrintWriter ibisWriter, ibisVItable VItable) {
    int size = VItable.size, i;
    string s = "";
    string s1 = "";
    if (VItable == null)
      return 1;
    if (VItable.VIs == null)
      return 1;

    BigDecimal bd;

    printString(ibisWriter, "|Voltage", ConstantStuff.MAX_LINE_LENGTH,
                "  I(typ)              I(min)              I(max)");
    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");

    for (i = 0; i < size; i++) {
      s = Get_TypMinMax_as_string(VItable.VIs[i].i, "A");
      bd = new BigDecimal(VItable.VIs[i].v);
      s1 = "  " + bd.setScale(2, BigDecimal.ROUND_HALF_UP);

      printString(ibisWriter, s1, ConstantStuff.IBIS_PRINT_WIDTH, s);
    }

    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");

    return 0;
  }

  /****************************************************************
  **************Print Clamp Table Routine
  ****************************************************************/
  int printClampTable(PrintWriter ibisWriter, ibisVItable clampTable,
                      double clampTol) {
    int size = clampTable.size, i;
    string s1 = "";
    string s = "";
    ibisTypMinMax tempCurrent;
    int lastPrinted = 0;
    BigDecimal bd;

    if (clampTable == null)
      return 1;
    if (clampTable.VIs == null)
      return 1;

    printString(ibisWriter, "|Voltage", ConstantStuff.MAX_LINE_LENGTH,
                "  I(typ)              I(min)              I(max)");
    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");
    /***Always Print the first Line ***/
    bd = new BigDecimal(clampTable.VIs[0].v);
    s1 = "  " + bd.setScale(2, BigDecimal.ROUND_HALF_UP);
    tempCurrent = clampTable.VIs[0].i;
    if (goodies.fabs(tempCurrent.typ) < clampTol)
      tempCurrent.typ = 0;
    if (goodies.fabs(tempCurrent.min) < clampTol)
      tempCurrent.min = 0;
    if (goodies.fabs(tempCurrent.max) < clampTol)
      tempCurrent.max = 0;

    s = Get_TypMinMax_as_string(tempCurrent, "A");
    printString(ibisWriter, s1, ConstantStuff.IBIS_PRINT_WIDTH, s);

    /***Now do lines 2 through to (size - 1). For each line - check to see if
     * it's above the clamp tolerance. If not, just advance to the next line,
     * and print zeroes if the line before this was printed. If it is above the
     * clamp tolerance, check which line was printed last. If it wasn't the line
     * directly before the one we're on now, print zeroes for that line, then
     * print the current line.**/
    for (i = 1; i < size - 1; i++) {
      tempCurrent = clampTable.VIs[i].i;
      if ((goodies.fabs(tempCurrent.typ) > clampTol) ||
          (goodies.fabs(tempCurrent.min) > clampTol) ||
          (goodies.fabs(tempCurrent.max) > clampTol)) {
        if (i > lastPrinted + 1) // check if the last line was printed?
        {
          bd = new BigDecimal(clampTable.VIs[i - 1].v);
          s1 = "  " + bd.setScale(2, BigDecimal.ROUND_HALF_UP);
          tempCurrent.typ = 0;
          tempCurrent.min = 0;
          tempCurrent.max = 0;
          s = Get_TypMinMax_as_string(tempCurrent, "A");
          printString(ibisWriter, s1, ConstantStuff.IBIS_PRINT_WIDTH, s);
          tempCurrent = clampTable.VIs[i].i;
        }
        bd = new BigDecimal(clampTable.VIs[i].v);
        s1 = "  " + bd.setScale(2, BigDecimal.ROUND_HALF_UP);

        if (goodies.fabs(tempCurrent.typ) < clampTol)
          tempCurrent.typ = 0;
        if (goodies.fabs(tempCurrent.min) < clampTol)
          tempCurrent.min = 0;
        if (goodies.fabs(tempCurrent.max) < clampTol)
          tempCurrent.max = 0;

        s = Get_TypMinMax_as_string(tempCurrent, "A");
        printString(ibisWriter, s1, ConstantStuff.IBIS_PRINT_WIDTH, s);
        lastPrinted = i;
      } else if ((i != 1) && (i == lastPrinted + 1)) {
        bd = new BigDecimal(clampTable.VIs[i].v);
        s1 = "  " + bd.setScale(2, BigDecimal.ROUND_HALF_UP);
        tempCurrent.typ = 0;
        tempCurrent.min = 0;
        tempCurrent.max = 0;
        s = Get_TypMinMax_as_string(tempCurrent, "A");
        printString(ibisWriter, s1, ConstantStuff.IBIS_PRINT_WIDTH, s);
      }
    }
    /***Always print the last Line ***/
    bd = new BigDecimal(clampTable.VIs[size - 1].v);
    s1 = "  " + bd.setScale(2, BigDecimal.ROUND_HALF_UP);
    tempCurrent = clampTable.VIs[size - 1].i;
    if (goodies.fabs(tempCurrent.typ) < clampTol)
      tempCurrent.typ = 0;
    if (goodies.fabs(tempCurrent.min) < clampTol)
      tempCurrent.min = 0;
    if (goodies.fabs(tempCurrent.max) < clampTol)
      tempCurrent.max = 0;

    s = Get_TypMinMax_as_string(tempCurrent, "A");
    printString(ibisWriter, s1, ConstantStuff.IBIS_PRINT_WIDTH, s);
    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");
    return 0;
  }

  /****************************************************************
  **************Print Wave Table Routine
  ****************************************************************/
  int printWaveTable(PrintWriter ibisWriter, ibisWaveTable waveTable) {
    int size = waveTable.size;
    int i;
    string s1;
    string s;

    if (waveTable == null)
      return 1;
    if (waveTable.waveData == null)
      return 1;

    printString(ibisWriter, "|time ", ConstantStuff.MAX_LINE_LENGTH,
                "  V(typ)              V(min)              V(max)");
    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");

    for (i = 0; i < size; i++) {
      s1 = Get_Double_as_string_for_time(waveTable.waveData[i].t, "S");
      s1 = spaceFill(s1, 15 - s1.length());
      s = Get_TypMinMax_as_string(waveTable.waveData[i].v, "V");
      printString(ibisWriter, s1, ConstantStuff.MAX_LINE_LENGTH, s);
    }
    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");
    return 0;
  }

  /****************************************************************
  **************Print Ramp Routine
  ****************************************************************/
  void printRamp(PrintWriter ibisWriter, ibisRamp ramp, double rload) {
    string s;
    string dummyBuffer;
    string numberBuffer;

    printString(ibisWriter, "[Ramp]", ConstantStuff.MAX_LINE_LENGTH, "");
    printString(ibisWriter,
                "| variable       typ                 min                 max",
                ConstantStuff.MAX_LINE_LENGTH, "");

    /**For the rising case first*/
    if (!(goodies.IS_USE_NA(ramp.dv_r.typ))) {
      s = Get_Double_as_string(ramp.dv_r.typ, "");
      numberBuffer = Get_Double_as_string(ramp.dt_r.typ, "");
      dummyBuffer = "/" + numberBuffer;
      s = s + dummyBuffer;
    } else
      s = "NA";
    s = spaceFill(s, 20 - s.length());

    if (!(goodies.IS_USE_NA(ramp.dv_r.min))) {
      numberBuffer = Get_Double_as_string(ramp.dv_r.min, "");
      s = s + numberBuffer;
      numberBuffer = Get_Double_as_string(ramp.dt_r.min, "");
      dummyBuffer = "/" + numberBuffer;
      s = s + dummyBuffer;
    } else {
      dummyBuffer = "NA";
      s = s + dummyBuffer;
    }
    s = spaceFill(s, 40 - s.length());

    if (!(goodies.IS_USE_NA(ramp.dv_r.max))) {
      numberBuffer = Get_Double_as_string(ramp.dv_r.max, "");
      s = s + numberBuffer;
      numberBuffer = Get_Double_as_string(ramp.dt_r.max, "");
      dummyBuffer = "/" + numberBuffer;
      s = s + dummyBuffer;
    } else {
      dummyBuffer = "NA";
      s = s + dummyBuffer;
    }
    printString(ibisWriter, "dV/dt_r", ConstantStuff.MAX_LINE_LENGTH, s);

    /**Now for the falling case*/
    if (!(goodies.IS_USE_NA(ramp.dv_f.typ))) {
      s = Get_Double_as_string(ramp.dv_f.typ, "");
      numberBuffer = Get_Double_as_string(ramp.dt_f.typ, "");
      dummyBuffer = "/" + numberBuffer;
      s = s + dummyBuffer;
    } else
      s = "NA";
    s = spaceFill(s, 20 - s.length());

    if (!(goodies.IS_USE_NA(ramp.dv_f.min))) {
      numberBuffer = Get_Double_as_string(ramp.dv_f.min, "");
      s = s + numberBuffer;
      numberBuffer = Get_Double_as_string(ramp.dt_f.min, "");
      dummyBuffer = "/" + numberBuffer;
      s = s + dummyBuffer;
    } else {
      dummyBuffer = "NA";
      s = s + dummyBuffer;
    }
    s = spaceFill(s, 40 - s.length());

    if (!(goodies.IS_USE_NA(ramp.dv_f.max))) {
      numberBuffer = Get_Double_as_string(ramp.dv_f.max, "");
      s = s + numberBuffer;
      numberBuffer = Get_Double_as_string(ramp.dt_f.max, "");
      dummyBuffer = "/" + numberBuffer;
      s = s + dummyBuffer;
    } else {
      dummyBuffer = "NA";
      s = s + dummyBuffer;
    }

    printString(ibisWriter, "dV/dt_f", ConstantStuff.MAX_LINE_LENGTH, s);
    numberBuffer = Get_Double_as_string(rload, "");
    printString(ibisWriter, "R_load =", ConstantStuff.MAX_LINE_LENGTH,
                numberBuffer);
    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");
  }

  /****************************************************************
  **************Print Utility Routines
  ****************************************************************/
  string spaceFill(string str, int numSpaces) {
    int i;
    for (i = 0; i < numSpaces; i++)
      str = str + " ";
    return str;
  }

  string Get_TypMinMax_as_string(ibisTypMinMax TypMinMax, string trailStr) {
    string dummyStr = "";
    string s = "";
    int position;

    s = "  " + Get_Double_as_string(TypMinMax.typ, trailStr);
    position = s.length();
    s = spaceFill(s, 20 - position);
    dummyStr = Get_Double_as_string(TypMinMax.min, trailStr);
    s = s + dummyStr;
    position = s.length();
    s = spaceFill(s, 40 - position);
    dummyStr = Get_Double_as_string(TypMinMax.max, trailStr);
    s = s + dummyStr;
    return s;
  }

  /**Get_Double_as_string
  **Prints a number as an engineering value or NA if number == USE_NA
  */
  string Get_Double_as_string(double number, string trailStr) {
    string s = "";
    double exponent = 1e-15;
    int i, expFound = 0;
    BigDecimal bd;
    if (goodies.IS_USE_NA(number))
      s = "NA";
    else {
      for (i = 0; i < 9; i++) {
        if (isExponent(number, exponent)) {
          bd = new BigDecimal(number / exponent);

          s = bd.setScale(4, BigDecimal.ROUND_HALF_UP) +
              s2iString.SIsuffixString[i] + trailStr;
          expFound = 1;
          break;
        } else
          exponent = exponent * 1000;
      }
      if (expFound == 0)
        s = number + trailStr;
    }
    return s;
  }
  string Get_Double_as_string_for_time(double number, string trailStr) {
    string s = "";
    double exponent = 1e-15;
    int i, expFound = 0;
    BigDecimal bd;
    if (goodies.IS_USE_NA(number))
      s = "NA";
    else {
      for (i = 0; i < 9; i++) {
        if (isExponent(number, exponent)) {
          bd = new BigDecimal(number / exponent);
          s = bd.setScale(2, BigDecimal.ROUND_HALF_UP) +
              s2iString.SIsuffixString[i] + trailStr;
          expFound = 1;
          break;
        } else
          exponent = exponent * 1000;
      }
      if (expFound == 0)
        s = number + trailStr;
    }
    return s;
  }

  bool isExponent(double number, double expon) {
    if ((goodies.fabs(number / expon) >= 0.1) &&
        (goodies.fabs(number / expon) < 100))
      return true;
    else
      return false;
  }

  void printTypMinMaxHeader(PrintWriter ibisWriter) {
    printString(ibisWriter,
                "| variable       typ                 min                 max",
                ConstantStuff.MAX_LINE_LENGTH, "");
  }

  void printHeader(PrintWriter ibisWriter, string name, string heading) {
    int spacing;
    string spaceFill = " ";
    spacing = (ConstantStuff.MAX_LINE_LENGTH - 18 -
               (heading.length() + name.length())) /
              2;
    for (int i2 = 0; i2 < spacing; i2++)
      spaceFill = spaceFill + " ";

    ibisWriter.println("|******************************************************"
                       "******************");
    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH,
                spaceFill + heading + " " + name);
    ibisWriter.println("|******************************************************"
                       "******************");
    printString(ibisWriter, "|", ConstantStuff.MAX_LINE_LENGTH, "");

  } // method printHeader

  void printString(PrintWriter ibisWriter, string indent, int width,
                   string string) {
    string newString;
    int j = 1;
    StringTokenizer st = new StringTokenizer(string);

    int cnt = st.countTokens();
    int totalLength = 0;
    string nextTok = "";

    newString = indent; //"[Disclaimer]";
    if (indent.length() < 8) {
      newString = newString + " " + " ";
      if (string.length() > width)    // if the arg string
      {                               // is bigger than the
        for (int i = 0; i < cnt; i++) // line width...
        {
          nextTok = st.nextToken();
          newString = newString + " " + nextTok;

          if (totalLength > ConstantStuff.MAX_IBIS_STRING_LENGTH)
            break;

          totalLength += nextTok.length();

          if (newString.length() >= j * width) {
            newString = newString + "\n  "; //+st.nextToken();
            j++;
          }
        }
      } else
        newString = newString + string;
    } else {
      newString = newString + " ";
      if (string.length() > width) {
        for (int i = 0; i < cnt; i++) {
          nextTok = st.nextToken();
          newString = newString + " " + nextTok;
          totalLength += nextTok.length();
          if (totalLength > ConstantStuff.MAX_IBIS_STRING_LENGTH)
            break;

          if (newString.length() + 2 * j * 8 >=
              j * width) // added 2*j*8 to fix 80 char error
          {
            newString = newString + "\n  "; //+" "+st.nextToken();
            j++;
          }
        }
      } else
        newString = newString + string;
    }
    ibisWriter.println(newString);

  } // method printString
};  // class s2ibisPrint
