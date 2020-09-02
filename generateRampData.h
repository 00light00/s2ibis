#ifndef _GENERATERAMPDATA
#define _GENERATERAMPDATA

int generateRampData(ibisPin currentPin, ibisPin enablePin, ibisPin inputPin, ibisPin powerPin, ibisPin gndPin, ibisPin powerClampPin, ibisPin gndClampPin, ibisTypMinMax Vcc, ibisTypMinMax Gnd, ibisTypMinMax VccClamp, ibisTypMinMax GndClamp, int curveType, int spiceType, String spiceFile, String spiceCommand, int iterate, int cleanup) {
    String loadBuffer, inputBuffer;
    int outputState = 0;

    ibisModel model_p = currentPin.model;

    if (curveType == 6) {
      outputState = 1;
    } else {
      outputState = 0;
    }



    if (model_p.modelType == ConstantStuff.MODEL_TYPE_OPEN_DRAIN ||
      model_p.modelType == ConstantStuff.MODEL_TYPE_OPEN_SINK ||
      model_p.modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN ||
      model_p.modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK) {

      loadBuffer = s2iString.resString(spiceType, "RLOADS2I",
          currentPin.spiceNodeName,
          powerPin.spiceNodeName, model_p.Rload);
    }
    else if (model_p.modelType == ConstantStuff.MODEL_TYPE_OPEN_SOURCE ||
      model_p.modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE) {

      loadBuffer = s2iString.resString(spiceType, "RLOADS2I",
          currentPin.spiceNodeName,
          gndPin.spiceNodeName, model_p.Rload);
    }
    else if (model_p.modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL ||
      model_p.modelType == ConstantStuff.MODEL_TYPE_I_O_ECL) {

      loadBuffer = s2iString.resString(spiceType, "RLOADS2I",
          currentPin.spiceNodeName,
          s2iString.dummyNodeName[0], model_p.Rload);
      String dummyBuffer = s2iString.DCSrcString(spiceType, "VTERMS2I",
          s2iString.dummyNodeName[0], powerPin.spiceNodeName,
          -2.0D);
      loadBuffer = String.valueOf(loadBuffer) + dummyBuffer;
    }
    else if (curveType == 6) {

      loadBuffer = s2iString.resString(spiceType, "RLOADS2I",
          currentPin.spiceNodeName, gndPin.spiceNodeName, model_p.Rload);
    }
    else {

      loadBuffer = s2iString.resString(spiceType, "RLOADS2I",
          currentPin.spiceNodeName, powerPin.spiceNodeName, model_p.Rload);
    }



    String headerLine = "*Typ " + s2iString.curveNameString[curveType] +
      " curve for model " + model_p.modelName + "\n";

    setPinDC setPinDC1 = new setPinDC();
    if (enablePin != null) {
      inputBuffer = setPinDC1.setPinDC(enablePin, model_p.enable, 1,
          "ENA", 0, spiceType);
    } else {
      inputBuffer = "";
    }
    setPinTran setPinTran1 = new setPinTran();
    if (inputPin != null) {

      String dummyBuffer = setPinTran1.setPinTran(inputPin, model_p.polarity, outputState,
          "IN", 0, spiceType);
      inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
    }

    setupPwrAndTempCmds setupPwrTmpCmd = new setupPwrAndTempCmds();
    setupPwrTmpCmd.setupPwrAndTempCmds(curveType, spiceType, powerPin, gndPin,
        powerClampPin, gndClampPin, Vcc.typ, Gnd.typ,
        VccClamp.typ, GndClamp.typ, model_p.tempRange.typ);
    String powerBuffer = setupPwrTmpCmd.powerBuffer;
    String temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    setupTranCommands setupTranCmd = new setupTranCommands();
    String analysisBuffer = setupTranCmd.setupTranCommands(spiceType, model_p.simTime,
        currentPin.spiceNodeName);

    setupSpiceFileNames setSpFlNames1 = new setupSpiceFileNames();
    setSpFlNames1.setupSpiceFileNames(s2iString.spiceFileTypPrefix[curveType],
        currentPin.pinName);
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
    getSpiceRampData RampData1 = new getSpiceRampData();

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
        spiceOutFile, spiceMsgFile) == 1) {


      int returnFromAbort = checkAbort.checkForAbort(spiceType, spiceOutFile,
          spiceMsgFile);
      if (returnFromAbort == 1) {

        printf("Spice run (TYP) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] +
            " not generated.");
        printf("--- ");
        return 1;
      }
    }

    RampData1.getSpiceRampData(model_p, curveType, spiceType, spiceOutFile, "typ");

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

        spiceOutFile = String.valueOf(s2iString.spiceFileTypPrefix[curveType]) + currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        if (!outFile2.delete()) {
          printf("Can't remove .st0 file " + spiceOutFile);
        }
        String hspiceIcFile = String.valueOf(s2iString.spiceFileTypPrefix[curveType]) + currentPin.pinName + ".ic";
        File outFile3 = new File(hspiceIcFile);
        outFile3.delete();
        String hspiceIc0File = String.valueOf(s2iString.spiceFileTypPrefix[curveType]) + currentPin.pinName + ".ic0";
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

      String dummyBuffer = setPinTran1.setPinTran(inputPin, model_p.polarity, outputState, "IN",
          -1, spiceType);
      inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
    }

    setupPwrTmpCmd.setupPwrAndTempCmds(curveType, spiceType, powerPin, gndPin,
        powerClampPin, gndClampPin, Vcc.min, Gnd.min,
        VccClamp.min, GndClamp.min, model_p.tempRange.min);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    analysisBuffer = setupTranCmd.setupTranCommands(spiceType, model_p.simTime,
        currentPin.spiceNodeName);

    setSpFlNames1.setupSpiceFileNames(s2iString.spiceFileMinPrefix[curveType],
        currentPin.pinName);
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

        printf("Spice run (MIN) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] + " not generated.");
      }
    }

    RampData1.getSpiceRampData(model_p, curveType, spiceType, spiceOutFile, "min");

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

        spiceOutFile = String.valueOf(s2iString.spiceFileMinPrefix[curveType]) + currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        if (!outFile2.delete()) {
          printf("Can't remove .st0 file " + spiceOutFile);
        }
        String hspiceIcFile = String.valueOf(s2iString.spiceFileMinPrefix[curveType]) + currentPin.pinName + ".ic";
        File outFile3 = new File(hspiceIcFile);
        outFile3.delete();
        String hspiceIc0File = String.valueOf(s2iString.spiceFileMinPrefix[curveType]) + currentPin.pinName + ".ic0";
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

      String dummyBuffer = setPinTran1.setPinTran(inputPin, model_p.polarity, outputState,
          "IN", 1, spiceType);
      inputBuffer = String.valueOf(inputBuffer) + "\n" + dummyBuffer;
    }

    setupPwrTmpCmd.setupPwrAndTempCmds(curveType, spiceType, powerPin, gndPin,
        powerClampPin, gndClampPin, Vcc.max, Gnd.max,
        VccClamp.max, GndClamp.max, model_p.tempRange.max);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    analysisBuffer = setupTranCmd.setupTranCommands(spiceType, model_p.simTime,
        currentPin.spiceNodeName);

    setSpFlNames1.setupSpiceFileNames(s2iString.spiceFileMaxPrefix[curveType],
        currentPin.pinName);
    spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    if (setSpInFile.setupSpiceInputFile(iterate, spiceType, spiceInFile, headerLine,
        spiceFile, model_p.modelFileMax, model_p.extSpiceCmdFile, loadBuffer, inputBuffer, powerBuffer,
        temperatureBuffer, analysisBuffer) == 1)
    {
      return 1;
    }

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
        spiceOutFile, spiceMsgFile) == 1) {


      int returnFromAbort = checkAbort.checkForAbort(spiceType, spiceOutFile,
          spiceMsgFile);
      if (returnFromAbort == 1) {

        printf("Spice run (MAX) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] + " not generated.");
      }
    }
    RampData1.getSpiceRampData(model_p, curveType, spiceType, spiceOutFile, "max");

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

        spiceOutFile = String.valueOf(s2iString.spiceFileMaxPrefix[curveType]) + currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        if (!outFile2.delete()) {
          printf("Can't remove .st0 file " + spiceOutFile);
        }
        String hspiceIcFile = String.valueOf(s2iString.spiceFileMaxPrefix[curveType]) + currentPin.pinName + ".ic";
        File outFile3 = new File(hspiceIcFile);
        outFile3.delete();
        String hspiceIc0File = String.valueOf(s2iString.spiceFileMaxPrefix[curveType]) + currentPin.pinName + ".ic0";
        File outFile4 = new File(hspiceIc0File);
        outFile4.delete();
      }
    }
    return 0;
  }

#endif
