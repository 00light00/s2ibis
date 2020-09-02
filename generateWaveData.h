#ifndef _GENERATEWAVEDATA
#define _GENERATEWAVEDATA

#include <string>
using String = std::string

#include "ibisWaveTable.h"
#include "ibisPin.h"
#include "ibisTypMinMax.h"
#include "ibisModel.h"
#include "ibisWaveTableEntry.h"


class generateWaveData
{
public:
  ibisWaveTable currentWave;

    generateWaveData(ibisPin currentPin, ibisPin enablePin, ibisPin inputPin, ibisPin powerPin, ibisPin gndPin, ibisPin powerClampPin, ibisPin gndClampPin, ibisTypMinMax Vcc, ibisTypMinMax Gnd, ibisTypMinMax VccClamp, ibisTypMinMax GndClamp, int curveType, int spiceType, String spiceFile, String spiceCommand, int iterate, int cleanup, int index) {
    String namePrefixBuffer, nodeList[] = new String[11];
    int outputState = 0;
    int nodeIndex = 0;
    int i = 0;
    ibisModel model_p = currentPin.model;

    this.currentWave.waveData = new ibisWaveTableEntry[100];
    this.currentWave.size = 100;


    for (int m = 0; m < 100; m++)
    {
      this.currentWave.waveData[m] = new ibisWaveTableEntry();
    }

    if (curveType == 8) {
      outputState = 1;
    } else {
      outputState = 0;
    }







    nodeList[0] = currentPin.spiceNodeName;
    for (i = 1; i < 11; i++) {
      nodeList[i] = s2iString.dummyNodeName[i - 1];
    }




    String loadBuffer = "";
    if (!goodies.IS_USE_NA(this.currentWave.L_dut)) {

      String str = s2iString.indString(spiceType, "LDUTS2I", nodeList[nodeIndex],
          nodeList[++nodeIndex], this.currentWave.L_dut);
      loadBuffer = String.valueOf(loadBuffer) + str;
    }

    if (!goodies.IS_USE_NA(this.currentWave.R_dut)) {

      String str = s2iString.resString(spiceType, "RDUTS2I", nodeList[nodeIndex],
          nodeList[++nodeIndex], this.currentWave.R_dut);
      loadBuffer = String.valueOf(loadBuffer) + str;
    }

    if (!goodies.IS_USE_NA(this.currentWave.C_dut)) {


      String str = s2iString.capString(spiceType, "CDUTS2I", nodeList[nodeIndex],
          "0", this.currentWave.C_dut);
      loadBuffer = String.valueOf(loadBuffer) + str;
    }

    String outputNodeName = nodeList[nodeIndex];




    if (!goodies.IS_USE_NA(this.currentWave.L_fixture)) {

      String str = s2iString.indString(spiceType, "LFIXS2I", nodeList[nodeIndex],
          nodeList[++nodeIndex], this.currentWave.L_fixture);
      loadBuffer = String.valueOf(loadBuffer) + str;
    }

    if (!goodies.IS_USE_NA(this.currentWave.C_fixture)) {

      String str = s2iString.capString(spiceType, "CFIXS2I", nodeList[nodeIndex],
          "0", this.currentWave.C_fixture);
      loadBuffer = String.valueOf(loadBuffer) + str;
    }




    String dummyBuffer = s2iString.resString(spiceType, "RFIXS2I", nodeList[nodeIndex],
        nodeList[++nodeIndex], this.currentWave.R_fixture);
    loadBuffer = String.valueOf(loadBuffer) + dummyBuffer;







    String headerLine = "*Typ " + s2iString.curveNameString[curveType] +
      " curve for model " + model_p.modelName + "\n";

    setPinDC setPinDC1 = new setPinDC();
    if (enablePin != null) {
      inputBuffer = setPinDC1.setPinDC(enablePin, model_p.enable,
          1,
          "ENA", 0, spiceType);
    } else {
      inputBuffer = "";
    }
    setPinTran setPinTran1 = new setPinTran();
    if (inputPin != null) {

      dummyBuffer = setPinTran1.setPinTran(inputPin, model_p.polarity, outputState,
          "IN", 0, spiceType);
      inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
    }

    dummyBuffer = s2iString.DCSrcString(spiceType, "VFIXS2I", nodeList[nodeIndex],
        "0", this.currentWave.V_fixture);
    String inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;

    setupPwrAndTempCmds setupPwrTmpCmd = new setupPwrAndTempCmds();
    setupPwrTmpCmd.setupPwrAndTempCmds(curveType, spiceType, powerPin, gndPin,
        powerClampPin, gndClampPin, Vcc.typ, Gnd.typ,
        VccClamp.typ, GndClamp.typ, model_p.tempRange.typ);
    String powerBuffer = setupPwrTmpCmd.powerBuffer;
    String temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    setupTranCommands setupTranCmd = new setupTranCommands();
    String analysisBuffer = setupTranCmd.setupTranCommands(spiceType, model_p.simTime,
        outputNodeName);

    if (index < 10) {
      namePrefixBuffer = String.valueOf(s2iString.spiceFileTypPrefix[curveType]) + "0" + index;
    } else {
      namePrefixBuffer = String.valueOf(s2iString.spiceFileTypPrefix[curveType]) + index;
    }
    setupSpiceFileNames setSpFlNames1 = new setupSpiceFileNames();
    setSpFlNames1.setupSpiceFileNames(namePrefixBuffer, currentPin.pinName);
    String spiceInFile = setSpFlNames1.spiceInFile;
    String spiceOutFile = setSpFlNames1.spiceOutFile;
    String spiceMsgFile = setSpFlNames1.spiceMsgFile;

    setupSpiceInputFile setSpInFile = new setupSpiceInputFile();
    if (setSpInFile.setupSpiceInputFile(iterate, spiceType, spiceInFile, headerLine,
        spiceFile, model_p.modelFileTyp, model_p.extSpiceCmdFile, loadBuffer, inputBuffer, powerBuffer,
        temperatureBuffer, analysisBuffer) == 1)
    {
      return 1;
    }

    callSpice callSpice1 = new callSpice();
    checkForAbort checkAbort = new checkForAbort();

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
        spiceOutFile, spiceMsgFile) == 1) {


      int returnFromAbort = checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {

        System.out.println("Spice run (TYP) aborted.  ");
        System.out.println("See file " + spiceMsgFile + " for information.");
        System.out.println("Curve " + s2iString.curveNameString[curveType] + " not generated.");
        System.out.println("--- ");
        return 1;
      }
    }


    (this.currentWave.waveData[0]).t = 0.0D;
    (this.currentWave.waveData[0]).v.typ = 0.0D;
    (this.currentWave.waveData[0]).v.min = 0.0D;
    (this.currentWave.waveData[0]).v.max = 0.0D;

    getSpiceWaveData WaveData1 = new getSpiceWaveData();
    WaveData1.wave_p = this.currentWave;
    WaveData1.getSpiceWaveData(model_p.simTime, spiceType, spiceOutFile, "typ");
    this.currentWave = WaveData1.wave_p;

    if (cleanup == 1) {

      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        System.out.println("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        System.out.println("Can't remove file " + spiceOutFile);
      if (spiceType != 5 && spiceType != 0 &&
        !msgFile.delete()) {
        System.out.println("Can't remove file " + spiceMsgFile);
      }
      if (spiceType == 0) {

        spiceOutFile = String.valueOf(namePrefixBuffer) + currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        outFile2.delete();

        String hspiceIcFile = String.valueOf(namePrefixBuffer) + currentPin.pinName + ".ic";
        File outFile3 = new File(hspiceIcFile);
        outFile3.delete();
        String hspiceIc0File = String.valueOf(namePrefixBuffer) + currentPin.pinName + ".ic0";
        File outFile4 = new File(hspiceIc0File);
        outFile4.delete();
      }
    }




    headerLine = "*Min " + s2iString.curveNameString[curveType] +
      " curve for model " + model_p.modelName + "\n";

    if (enablePin != null) {
      inputBuffer = setPinDC1.setPinDC(enablePin, model_p.enable,
          1,
          "ENA", -1, spiceType);
    } else {
      inputBuffer = "";
    }
    if (inputPin != null) {

      dummyBuffer = setPinTran1.setPinTran(inputPin, model_p.polarity, outputState,
          "IN", -1, spiceType);
      inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
    }

    if (!goodies.IS_USE_NA(this.currentWave.V_fixture_min)) {

      dummyBuffer = s2iString.DCSrcString(spiceType, "VFIXS2I", nodeList[nodeIndex],
          "0", this.currentWave.V_fixture_min);
      inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
    }
    else {

      dummyBuffer = s2iString.DCSrcString(spiceType, "VFIXS2I", nodeList[nodeIndex],
          "0", this.currentWave.V_fixture);
      inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
    }

    setupPwrTmpCmd.setupPwrAndTempCmds(curveType, spiceType, powerPin, gndPin,
        powerClampPin, gndClampPin, Vcc.min, Gnd.min,
        VccClamp.min, GndClamp.min, model_p.tempRange.min);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    analysisBuffer = setupTranCmd.setupTranCommands(spiceType, model_p.simTime,
        outputNodeName);

    if (index < 10) {
      namePrefixBuffer = String.valueOf(s2iString.spiceFileMinPrefix[curveType]) + "0" + index;
    } else {
      namePrefixBuffer = String.valueOf(s2iString.spiceFileMinPrefix[curveType]) + index;
    }
    setSpFlNames1.setupSpiceFileNames(namePrefixBuffer, currentPin.pinName);
    spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    if (setSpInFile.setupSpiceInputFile(iterate, spiceType, spiceInFile, headerLine,
        spiceFile, model_p.modelFileMin, model_p.extSpiceCmdFile, loadBuffer, inputBuffer, powerBuffer,
        temperatureBuffer, analysisBuffer) == 1) {
      return 1;
    }
    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
        spiceOutFile, spiceMsgFile) == 1) {


      int returnFromAbort = checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {

        System.out.println("Spice run (MIN) aborted.  ");
        System.out.println("See file " + spiceMsgFile + " for information.");
        System.out.println("Curve " + s2iString.curveNameString[curveType] + " not generated.");
      }
    }

    WaveData1.wave_p = this.currentWave;
    WaveData1.getSpiceWaveData(model_p.simTime, spiceType, spiceOutFile, "min");
    this.currentWave = WaveData1.wave_p;
    if (cleanup == 1) {

      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        System.out.println("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        System.out.println("Can't remove file " + spiceOutFile);
      if (spiceType != 5 && spiceType != 0 &&
        !msgFile.delete()) {
        System.out.println("Can't remove file " + spiceMsgFile);
      }
      if (spiceType == 0) {

        spiceOutFile = String.valueOf(namePrefixBuffer) + currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        outFile2.delete();

        String hspiceIcFile = String.valueOf(namePrefixBuffer) + currentPin.pinName + ".ic";
        File outFile3 = new File(hspiceIcFile);
        outFile3.delete();
        String hspiceIc0File = String.valueOf(namePrefixBuffer) + currentPin.pinName + ".ic0";
        File outFile4 = new File(hspiceIc0File);
        outFile4.delete();
      }
    }




    headerLine = "*Max " + s2iString.curveNameString[curveType] +
      " curve for model " + model_p.modelName + "\n";

    if (enablePin != null) {
      inputBuffer = setPinDC1.setPinDC(enablePin, model_p.enable,
          1,
          "ENA", 1, spiceType);
    } else {
      inputBuffer = "";
    }
    if (inputPin != null) {

      dummyBuffer = setPinTran1.setPinTran(inputPin, model_p.polarity, outputState,
          "IN", 1, spiceType);
      inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
    }

    if (!goodies.IS_USE_NA(this.currentWave.V_fixture_max)) {

      dummyBuffer = s2iString.DCSrcString(spiceType, "VFIXS2I", nodeList[nodeIndex],
          "0", this.currentWave.V_fixture_max);
      inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
    }
    else {

      dummyBuffer = s2iString.DCSrcString(spiceType, "VFIXS2I", nodeList[nodeIndex],
          "0", this.currentWave.V_fixture);
      inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
    }

    setupPwrTmpCmd.setupPwrAndTempCmds(curveType, spiceType, powerPin, gndPin,
        powerClampPin, gndClampPin, Vcc.max,
        Gnd.max, VccClamp.max, GndClamp.max,
        model_p.tempRange.max);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    analysisBuffer = setupTranCmd.setupTranCommands(spiceType, model_p.simTime,
        outputNodeName);

    if (index < 10) {
      namePrefixBuffer = String.valueOf(s2iString.spiceFileMaxPrefix[curveType]) + "0" + index;
    } else {
      namePrefixBuffer = String.valueOf(s2iString.spiceFileMaxPrefix[curveType]) + index;
    }
    setSpFlNames1.setupSpiceFileNames(namePrefixBuffer, currentPin.pinName);
    spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    if (setSpInFile.setupSpiceInputFile(iterate, spiceType, spiceInFile, headerLine,
        spiceFile, model_p.modelFileMax, model_p.extSpiceCmdFile, loadBuffer, inputBuffer, powerBuffer,
        temperatureBuffer, analysisBuffer) == 1) {
      return 1;
    }
    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
        spiceOutFile, spiceMsgFile) == 1) {


      int returnFromAbort = checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {

        System.out.println("Spice run (MAX) aborted.  ");
        System.out.println("See file " + spiceMsgFile + " for information.");
        System.out.println("Curve " + s2iString.curveNameString[curveType] + " not generated.");
      }
    }

    WaveData1.wave_p = this.currentWave;
    WaveData1.getSpiceWaveData(model_p.simTime, spiceType, spiceOutFile, "max");
    this.currentWave = WaveData1.wave_p;

    if (cleanup == 1) {

      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        System.out.println("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        System.out.println("Can't remove file " + spiceOutFile);
      if (spiceType != 5 && spiceType != 0 &&
        !msgFile.delete()) {
        System.out.println("Can't remove file " + spiceMsgFile);
      }
      if (spiceType == 0) {

        spiceOutFile = String.valueOf(namePrefixBuffer) + currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        outFile2.delete();

        String hspiceIcFile = String.valueOf(namePrefixBuffer) + currentPin.pinName + ".ic";
        File outFile3 = new File(hspiceIcFile);
        outFile3.delete();
        String hspiceIc0File = String.valueOf(namePrefixBuffer) + currentPin.pinName + ".ic0";
        File outFile4 = new File(hspiceIc0File);
        outFile4.delete();
      }
    }

    return 0;
  }
};

#endif
