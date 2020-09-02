#ifndef _GENERATEVICURVE
#define _GENERATEVICURVE

#include <iostream>
using namespace  std;
#include "ibisPin.h"
#include "ibisTypMinMax.h"
#include "ibisVItable.h"

class generateVICurve
{
public:
  ibisVItable VIData;

  generateVICurve(ibisPin currentPin, ibisPin enablePin, ibisPin inputPin, ibisPin powerPin, ibisPin gndPin, ibisPin powerClampPin, ibisPin gndClampPin, ibisTypMinMax Vcc, ibisTypMinMax Gnd, ibisTypMinMax VccClamp, ibisTypMinMax GndClamp, ibisTypMinMax sweepStart, double sweepRange, double sweepStep, int curveType, int spiceType, String spiceFile, String spiceCommand, int enableOutput, int outputHigh, int iterate, int cleanup, double Vds, int index) throws IOException {
    double sweepEnd = 0.0D;
    int numTablePoints = 0;
    String loadBuffer = null;
    String headerLine = null;
    String inputBuffer = null;
    String powerBuffer = null;
    String dummyBuffer = null;
    String temperatureBuffer = null;
    String analysisBuffer = null;

    String spiceInFile = null;
    String spiceOutFile = null;
    String spiceMsgFile = null;
    String namePrefixBuffer = null;
    ibisModel model = currentPin.model;
    numTablePoints = goodies.ROUND(sweepRange / sweepStep) + 2;
    printf("CurrentPin is .. " + currentPin.pinName);

    VIDataContainer VICont = new VIDataContainer();
    VICont.VIData2.VIs = new ibisVItableEntry[numTablePoints];

    for (int m = 0; m < numTablePoints; m++) {

      VICont.VIData2.VIs[m] = new ibisVItableEntry();
      (VICont.VIData2.VIs[m]).v = -1.33287736222333E20D;
      (VICont.VIData2.VIs[m]).i.typ = -1.33287736222333E20D;
      (VICont.VIData2.VIs[m]).i.min = -1.33287736222333E20D;
      (VICont.VIData2.VIs[m]).i.max = -1.33287736222333E20D;
    }

    create_VItable VITable = new create_VItable();


    if (curveType == 10) {
      loadBuffer = s2iString.DCSrcString(spiceType, "VOUTS2I",
          currentPin.seriesPin2name, "0", 0.0D);
    } else {
      loadBuffer = s2iString.DCSrcString(spiceType, "VOUTS2I",
          currentPin.spiceNodeName, "0", 0.0D);
    }



    printf("Do the TYP run in GenerateVITable ");
    sweepEnd = sweepStart.typ + sweepRange;
    headerLine = "*Typ " + s2iString.curveNameString[curveType] +
      " curve for model " + model.modelName + "\n";

    setPinDC setPinDC1 = new setPinDC();

    if (curveType == 10) {

      inputBuffer = setPinDC1.setPinDC(inputPin, model.polarity, outputHigh,
          "gate", 0, spiceType);
      if (spiceType == 4) {
        inputBuffer = String.valueOf(inputBuffer) + "\nVDS " + currentPin.pinName + " " + currentPin.seriesPin2name +
          " vsource type=dc dc= " + Vds + "\n";
      } else {
        inputBuffer = String.valueOf(inputBuffer) + "\nVDS " + currentPin.pinName + " " + currentPin.seriesPin2name +
          " DC " + Vds + "\n";
      }
    } else {

      if (enablePin != null) {
        inputBuffer = setPinDC1.setPinDC(enablePin, model.enable,
            enableOutput,
            "ENA", 0, spiceType);
      } else {
        inputBuffer = "";
      }
      if (inputPin != null) {

        dummyBuffer = setPinDC1.setPinDC(inputPin, model.polarity, outputHigh, "IN",
            0, spiceType);
        inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
      }
    }

    setupPwrAndTempCmds setupPwrTmpCmd = new setupPwrAndTempCmds();
    setupPwrTmpCmd.setupPwrAndTempCmds(curveType, spiceType, powerPin,
        gndPin, powerClampPin, gndClampPin,
        Vcc.typ, Gnd.typ, VccClamp.typ,
        GndClamp.typ, model.tempRange.typ);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    setupDCSweepCommands setupDCSweepCmd = new setupDCSweepCommands();
    analysisBuffer = setupDCSweepCmd.setupDCSweepCommands(curveType, spiceType, sweepStart.typ,
        sweepEnd, sweepStep);


    setupSpiceFileNames setSpFlNames1 = new setupSpiceFileNames();


    if (curveType == 10) {

      if (index < 10) {
        namePrefixBuffer = String.valueOf(s2iString.spiceFileTypPrefix[curveType]) + "0" + index;
      } else {
        namePrefixBuffer = String.valueOf(s2iString.spiceFileTypPrefix[curveType]) + index;
      }
      setSpFlNames1.setupSpiceFileNames(namePrefixBuffer, currentPin.pinName);
    } else {

      setSpFlNames1.setupSpiceFileNames(s2iString.spiceFileTypPrefix[curveType],
          currentPin.pinName);
    }  spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    setupSpiceInputFile setSpInFile = new setupSpiceInputFile();
    if (setSpInFile.setupSpiceInputFile(iterate, spiceType, spiceInFile, headerLine,
        spiceFile, model.modelFileTyp, model.extSpiceCmdFile, loadBuffer, inputBuffer, powerBuffer,
        temperatureBuffer, analysisBuffer) == 1) {

      printf("Couldn't set up Spice File for " +
          s2iString.curveNameString[curveType] + " curve");
      return 1;
    }

    callSpice callSpice1 = new callSpice();
    getSpiceVIData VIData1 = new getSpiceVIData();
    checkForAbort checkAbort = new checkForAbort();
    runSpiceAgain runSpiceAgain = new runSpiceAgain();
    checkForConvergence chkConvergence = new checkForConvergence();

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
        spiceOutFile, spiceMsgFile) == 1) {


      int returnFromAbort = checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);

      if (returnFromAbort == 1) {

        printf("Spice run (TYP) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] + " not generated.");
        if (chkConvergence.checkForConvergence(spiceType, spiceOutFile) == 1) {

          printf("Spice run aborted NON CONVERENCE detected.  ");
          runSpiceAgain.sweepStart = sweepStart.typ;
          runSpiceAgain.sweepEnd = sweepEnd;
          while (runSpiceAgain.runSpiceAgain(curveType, spiceType, sweepStep,
              spiceInFile, spiceOutFile, spiceMsgFile,
              iterate, headerLine, spiceCommand, spiceFile,
              model.modelFileTyp, model.extSpiceCmdFile, loadBuffer, inputBuffer,
              powerBuffer, temperatureBuffer) != 0) {
            printf("Rerun simulations.. ");
          }
        } else {

          printf("--- ");
          return 1;
        }
      }
    }

    if (VIData1.getSpiceVIData(VICont, numTablePoints, spiceType, spiceOutFile, "typ") == 1) {

      printf("Curve " + s2iString.curveNameString[curveType] +
          " not generated.\n");
      return 1;
    }
    if (cleanup == 1) {

      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        printf("Can't remove file " + spiceInFile);
      if (!outFile.delete()) {
        printf("Can't remove file " + spiceOutFile);
      }
      if (spiceType != 5 && spiceType != 0 &&
        !msgFile.delete()) {
        printf("Can't remove file " + spiceMsgFile);
      }
      if (spiceType == 0) {

        spiceOutFile = String.valueOf(s2iString.spiceFileTypPrefix[curveType]) + currentPin.pinName +
          ".st0";
        File outFile2 = new File(spiceOutFile);
        if (!outFile2.delete()) {
          printf("Can't remove .st0 file " + spiceOutFile);
        }
      }
    }


    printf("Do the min run in GenerateVITable ");
    sweepEnd = sweepStart.min + sweepRange;
    headerLine = "*Min " + s2iString.curveNameString[curveType] +
      " curve for model " + model.modelName + "\n";

    if (curveType == 10) {

      inputBuffer = setPinDC1.setPinDC(inputPin, model.polarity, outputHigh,
          "gate", -1, spiceType);
      if (spiceType == 4) {
        inputBuffer = String.valueOf(inputBuffer) + "\nVDS " + currentPin.pinName + " " + currentPin.seriesPin2name +
          " vsource type=dc dc= " + Vds + "\n";
      } else {
        inputBuffer = String.valueOf(inputBuffer) + "\nVDS " + currentPin.pinName + " " + currentPin.seriesPin2name +
          " DC " + Vds + "\n";
      }
    } else {

      if (enablePin != null) {
        inputBuffer = setPinDC1.setPinDC(enablePin, model.enable,
            enableOutput, "ENA",
            -1, spiceType);
      } else {
        inputBuffer = "";
      }
      if (inputPin != null) {

        dummyBuffer = setPinDC1.setPinDC(inputPin, model.polarity, outputHigh, "IN",
            -1, spiceType);
        inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
      }
    }

    setupPwrTmpCmd.setupPwrAndTempCmds(curveType, spiceType, powerPin, gndPin,
        powerClampPin, gndClampPin, Vcc.min,
        Gnd.min, VccClamp.min, GndClamp.min,
        model.tempRange.min);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    analysisBuffer = setupDCSweepCmd.setupDCSweepCommands(curveType, spiceType, sweepStart.min,
        sweepEnd, sweepStep);
    if (curveType == 10) {

      if (index < 10) {
        namePrefixBuffer = String.valueOf(s2iString.spiceFileMinPrefix[curveType]) + "0" + index;
      } else {
        namePrefixBuffer = String.valueOf(s2iString.spiceFileMinPrefix[curveType]) + index;
      }
      setSpFlNames1.setupSpiceFileNames(namePrefixBuffer, currentPin.pinName);
    } else {

      setSpFlNames1.setupSpiceFileNames(s2iString.spiceFileMinPrefix[curveType],
          currentPin.pinName);
    }  spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    if (setSpInFile.setupSpiceInputFile(iterate, spiceType, spiceInFile, headerLine,
        spiceFile, model.modelFileMin, model.extSpiceCmdFile,
        loadBuffer, inputBuffer, powerBuffer, temperatureBuffer,
        analysisBuffer) == 1) {

      printf("Couldn't set up Spice File for " +
          s2iString.curveNameString[curveType]);
      return 1;
    }

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
        spiceOutFile, spiceMsgFile) == 1) {


      int returnFromAbort = checkAbort.checkForAbort(spiceType,
          spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {

        printf("Spice run (MIN) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] +
            " not generated.");
        if (chkConvergence.checkForConvergence(spiceType, spiceOutFile) == 1) {

          printf("Spice run aborted NON CONVERENCE detected.  ");
          runSpiceAgain.sweepStart = sweepStart.min;
          runSpiceAgain.sweepEnd = sweepEnd;
          while (runSpiceAgain.runSpiceAgain(curveType, spiceType, sweepStep,
              spiceInFile, spiceOutFile, spiceMsgFile,
              iterate, headerLine, spiceCommand, spiceFile,
              model.modelFileTyp, model.extSpiceCmdFile, loadBuffer,
              inputBuffer, powerBuffer, temperatureBuffer) != 0)
            printf("Rerun simulations.. ");
        }
      }
    }
    if (VIData1.getSpiceVIData(VICont, numTablePoints, spiceType, spiceOutFile,
        "min") == 1) {

      printf("Curve " + s2iString.curveNameString[curveType] +
          " not generated.\n");
      return 1;
    }
    if (cleanup == 1) {

      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        printf("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        printf("Can't remove file " + spiceOutFile);
      if (spiceType != 5 && spiceType != 0 &&
        !msgFile.delete()) {
        printf("Can't remove file " + spiceMsgFile);
      }
      if (spiceType == 0) {

        spiceOutFile = String.valueOf(s2iString.spiceFileMinPrefix[curveType]) + currentPin.pinName +
          ".st0";
        File outFile2 = new File(spiceOutFile);
        outFile2.delete();
      }
    }



    printf("Do the max run in GenerateVITable ");
    sweepEnd = sweepStart.max + sweepRange;
    headerLine = "*Max " + s2iString.curveNameString[curveType] +
      " curve for model " + model.modelName + "\n";
    if (curveType == 10) {

      inputBuffer = setPinDC1.setPinDC(inputPin, model.polarity, outputHigh,
          "gate", 1, spiceType);
      if (spiceType == 4) {
        inputBuffer = String.valueOf(inputBuffer) + "\nVDS " + currentPin.pinName + " " + currentPin.seriesPin2name +
          " vsource type=dc dc= " + Vds + "\n";
      } else {
        inputBuffer = String.valueOf(inputBuffer) + "\nVDS " + currentPin.pinName + " " + currentPin.seriesPin2name +
          " DC " + Vds + "\n";
      }
    } else {

      if (enablePin != null) {
        inputBuffer = setPinDC1.setPinDC(enablePin, model.enable,
            enableOutput, "ENA",
            1, spiceType);
      } else {
        inputBuffer = "";
      }
      if (inputPin != null) {

        dummyBuffer = setPinDC1.setPinDC(inputPin, model.polarity, outputHigh, "IN",
            1, spiceType);
        inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
      }
    }

    setupPwrTmpCmd.setupPwrAndTempCmds(curveType, spiceType, powerPin, gndPin,
        powerClampPin, gndClampPin, Vcc.max, Gnd.max,
        VccClamp.max, GndClamp.max, model.tempRange.max);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    analysisBuffer = setupDCSweepCmd.setupDCSweepCommands(curveType, spiceType, sweepStart.max,
        sweepEnd, sweepStep);

    if (curveType == 10) {

      if (index < 10) {
        namePrefixBuffer = String.valueOf(s2iString.spiceFileMaxPrefix[curveType]) + "0" + index;
      } else {
        namePrefixBuffer = String.valueOf(s2iString.spiceFileMaxPrefix[curveType]) + index;
      }
      setSpFlNames1.setupSpiceFileNames(namePrefixBuffer, currentPin.pinName);
    } else {

      setSpFlNames1.setupSpiceFileNames(s2iString.spiceFileMaxPrefix[curveType],
          currentPin.pinName);
    }  spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    if (setSpInFile.setupSpiceInputFile(iterate, spiceType, spiceInFile, headerLine,
        spiceFile, model.modelFileMax, model.extSpiceCmdFile, loadBuffer, inputBuffer, powerBuffer,
        temperatureBuffer, analysisBuffer) == 1) {

      printf("Couldn't set up Spice File for " +
          s2iString.curveNameString[curveType]);
      return 1;
    }

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
        spiceOutFile, spiceMsgFile) == 1) {


      int returnFromAbort = checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {

        printf("Spice run (MAX) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] + " not generated.");
        if (chkConvergence.checkForConvergence(spiceType, spiceOutFile) == 1) {

          printf("Spice run aborted NON CONVERENCE detected.  ");

          runSpiceAgain.sweepStart = sweepStart.max;
          runSpiceAgain.sweepEnd = sweepEnd;
          while (runSpiceAgain.runSpiceAgain(curveType, spiceType, sweepStep,
              spiceInFile, spiceOutFile, spiceMsgFile,
              iterate, headerLine, spiceCommand, spiceFile,
              model.modelFileTyp, model.extSpiceCmdFile, loadBuffer,
              inputBuffer, powerBuffer, temperatureBuffer) != 0)
            printf("Rerun simulations.. ");
        }
      }
    }
    if (VIData1.getSpiceVIData(VICont, numTablePoints, spiceType, spiceOutFile, "max") == 1) {

      printf("Curve " + s2iString.curveNameString[curveType] +
          " not generated.\n");
      return 1;
    }
    if (cleanup == 1) {

      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        printf("Can't remove file " + spiceInFile);
      if (!outFile.delete()) {
        printf("Can't remove file " + spiceOutFile);
      }
      if (spiceType != 5 && spiceType != 0 &&
        !msgFile.delete()) {
        printf("Can't remove file " + spiceMsgFile);
      }
      if (spiceType == 0) {

        spiceOutFile = String.valueOf(s2iString.spiceFileMaxPrefix[curveType]) + currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        outFile2.delete();
      }
    }


    this.VIData = VICont.VIData2;
    return 0;
  }
};

#endif
