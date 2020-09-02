#ifndef _S2IBISPRINT
#define _S2IBISPRINT


#include "ibisTOP.h"
#include "ibisComponent.h"
#include "componentList.h"
#include "ibisPin.h"
#include "ibisSeriesPin.h"

class s2ibisPrint
{
  ibisTOP ibisHead;

  public: void printMain() {
    File outFile = new File(this.ibisHead.thisFileName);

    try {
      PrintWriter ibisWriter = new PrintWriter(new BufferedWriter(
            new FileWriter(outFile)));

      printf("Opening file " + this.ibisHead.thisFileName + " for writing ...");





      if (!outFile.canWrite()) {

        printf("Unable to open " + outFile + "for writing");

        return;
      }
      print_TOP(ibisWriter);
      ibisWriter.close();
      printf("done.");
    }
    catch (Exception ex) {
      printf("Exception while writing ibis output file (printMain): " +
          ex.toString() + ": ");
      ex.printStackTrace();
    }
  }
  public: void print_TOP(PrintWriter ibisWriter) {
    ibisComponent tempComponent = new ibisComponent();
    ibisComponent tempComponent2 = new ibisComponent();


    ibisWriter.println("|************************************************************************");
    ibisWriter.println("| IBIS file " + this.ibisHead.thisFileName +
        " created by s2ibis3 verion " + "1.1");
    ibisWriter.println("| North Carolina State University, ERL, 2006");
    ibisWriter.println("|************************************************************************");
    String version = print_IBIS_Version(ibisWriter, this.ibisHead.ibisVersion);
    printString(ibisWriter, "[IBIS ver]",
        80, version);
    ibisWriter.println("[File name] " + this.ibisHead.thisFileName);
    ibisWriter.println("[File Rev] " + this.ibisHead.fileRev);
    ibisWriter.println("[Date]  " + this.ibisHead.date);
    if (!this.ibisHead.source.equals(""))
      printString(ibisWriter, "[Source]",
          80, this.ibisHead.source);
    if (!this.ibisHead.notes.equals(""))
      printString(ibisWriter, "[Notes]",
          80, this.ibisHead.notes);
    if (!this.ibisHead.disclaimer.equals(""))
      printString(ibisWriter, "[Disclaimer]",
          80, this.ibisHead.disclaimer);
    if (this.ibisHead.ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !this.ibisHead.copyright.equals("")) {
      printString(ibisWriter, "[Copyright]",
          80, this.ibisHead.copyright);
    }




    componentList compListForPrint = new componentList();
    this.ibisHead.cList.gototop(); int i1;
    for (i1 = 0; i1 < this.ibisHead.cList.count; i1++) {

      tempComponent2 = this.ibisHead.cList.current;
      this.ibisHead.cList.next();
      compListForPrint.add(tempComponent2);
    }


    compListForPrint.gototop();
    for (i1 = 0; i1 < compListForPrint.count; i1++) {

      tempComponent2 = compListForPrint.current;
      printComponent(ibisWriter, tempComponent2, this.ibisHead.ibisVersion);
      compListForPrint.next();
    }
    ibisWriter.println("[End]");
  }





  String print_IBIS_Version(PrintWriter ibisWriter, int ibisVersion) {
    String s = "";
    if (ibisVersion == ConstantStuff.VERSION_ONE_ZERO) {
      s = "1.0";
    } else if (ibisVersion == ConstantStuff.VERSION_ONE_ONE) {
      s = "1.1";
    }  if (ibisVersion == ConstantStuff.VERSION_TWO_ZERO) {
      s = "2.0";
    } else if (ibisVersion == ConstantStuff.VERSION_TWO_ONE) {
      s = "2.1";
    } else if (ibisVersion == ConstantStuff.VERSION_THREE_TWO) {
      s = "3.2";
    } else {
      s = "unknown";
    }  return s;
  }







  void printComponent(PrintWriter ibisWriter, ibisComponent component, int ibisVersion) {
    ibisModel tempModel = null;
    ibisPin tempPin = null;
    ibisSeriesPin tempSeriesPin = null;
    seriesSwitchGroup tempSeriesSwitchGp = null;
    ibisPinMap tempPinMap = null;
    ibisDiffPin tempDiffPin = null;

    printString(ibisWriter, "|", 80, "");


    printHeader(ibisWriter, component.component, "Component");
    printString(ibisWriter, "[Component]", 80, component.component);
    printString(ibisWriter, "[Manufacturer]", 80, component.manufacturer);



    printString(ibisWriter, "[Package]", 80, "");
    printTypMinMaxHeader(ibisWriter);

    String s = Get_TypMinMax_as_String(component.pinParasitics.R_pkg, "");
    printString(ibisWriter, "R_pkg", 80, s);
    s = Get_TypMinMax_as_String(component.pinParasitics.L_pkg, "H");
    printString(ibisWriter, "L_pkg", 80, s);

    s = Get_TypMinMax_as_String(component.pinParasitics.C_pkg, "F");
    printString(ibisWriter, "C_pkg", 80, s);

    printString(ibisWriter, "|", 80, "");




    component.pList.gototop();
    if (component.pList != null) {

      ibisWriter.println("[Pin]  signal_name          model_name           R_pin     L_pin     C_pin");
      for (int i = 0; i < component.pList.count; i++) {

        tempPin = component.pList.current;
        printPin(ibisWriter, tempPin);
        component.pList.next();
      }
      printString(ibisWriter, "|", 80, "");
    }





    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && component.hasPinMapping) {

      component.pmList.gototop();
      ibisWriter.println("[Pin Mapping]  pulldown_ref    pullup_ref      gnd_clamp_ref   power_clamp_ref");
      printString(ibisWriter, "|", 80, "");
      for (int i = 0; i < component.pmList.count; i++) {

        tempPinMap = component.pmList.current;
        printPinMap(ibisWriter, tempPinMap);
        component.pmList.next();
      }
      printString(ibisWriter, "|", 80, "");
    }





    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && component.dpList != null) {

      component.dpList.gototop();
      if (component.dpList.count != 0)
        ibisWriter.println("[Diff pin]  inv_pin  vdiff  tdelay_typ  tdelay_min  tdelay_max");
      printString(ibisWriter, "|", 80, "");
      for (int i = 0; i < component.dpList.count; i++) {

        tempDiffPin = component.dpList.current;
        printDiffPin(ibisWriter, tempDiffPin);
        component.dpList.next();
      }
      printString(ibisWriter, "|", 80, "");
    }




    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && component.spList != null) {

      component.spList.gototop();
      if (component.spList.count != 0)
        ibisWriter.println("[Series Pin Mapping]  pin_2        model_name        function_table_group");
      for (int i = 0; i < component.spList.count; i++) {

        tempSeriesPin = component.spList.current;
        printSeriesPin(ibisWriter, tempSeriesPin);
        component.spList.next();
      }
      printString(ibisWriter, "|", 80, "");
    }





    if (component.ssgList != null) {

      seriesSwitchGpList ssgListForPrint = new seriesSwitchGpList();
      component.ssgList.gototop();
      for (int j = 0; j < component.ssgList.count; j++) {

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
      printString(ibisWriter, "|", 80, "");
    }





    component.mList.gototop();

    for (int i1 = 0; i1 < component.mList.count; i1++) {

      tempModel = component.mList.current;
      if (tempModel.noModel == 0)
      {
        printModel(ibisWriter, tempModel, this.ibisHead.ibisVersion);
      }
      component.mList.next();
    }
    printString(ibisWriter, "|End [Component]", 80, "");
  }








  void printDiffPin(PrintWriter ibisWriter, ibisDiffPin diffPin) {
    String tempBuf = diffPin.pinName;
    tempBuf = spaceFill(tempBuf, 12 - tempBuf.length());
    tempBuf = String.valueOf(tempBuf) + diffPin.invPin;
    tempBuf = spaceFill(tempBuf, 21 - tempBuf.length());
    String numBuf = Get_Double_as_String(diffPin.vdiff, "V");
    tempBuf = String.valueOf(tempBuf) + numBuf;
    tempBuf = spaceFill(tempBuf, 31 - tempBuf.length());
    numBuf = Get_Double_as_String(diffPin.tdelay_typ, "s");
    tempBuf = String.valueOf(tempBuf) + numBuf;

    if (!goodies.IS_NOT_USED(diffPin.tdelay_min)) {

      tempBuf = spaceFill(tempBuf, 43 - tempBuf.length());
      numBuf = Get_Double_as_String(diffPin.tdelay_min, "s");
      tempBuf = String.valueOf(tempBuf) + numBuf;
      tempBuf = spaceFill(tempBuf, 55 - tempBuf.length());
      numBuf = Get_Double_as_String(diffPin.tdelay_max, "s");
      tempBuf = String.valueOf(tempBuf) + numBuf;
    }
    printString(ibisWriter, tempBuf, 80, "");
  }







  void printPinMap(PrintWriter ibisWriter, ibisPinMap pinMap) {
    String tempBuf = pinMap.pinName;
    tempBuf = spaceFill(tempBuf, 15 - tempBuf.length());
    tempBuf = String.valueOf(tempBuf) + pinMap.pulldownRef;
    tempBuf = spaceFill(tempBuf, 31 - tempBuf.length());
    tempBuf = String.valueOf(tempBuf) + pinMap.pullupRef;
    tempBuf = spaceFill(tempBuf, 47 - tempBuf.length());
    tempBuf = String.valueOf(tempBuf) + pinMap.gndClampRef;
    tempBuf = spaceFill(tempBuf, 63 - tempBuf.length());
    tempBuf = String.valueOf(tempBuf) + pinMap.powerClampRef;

    printString(ibisWriter, tempBuf, 80, "");
  }










  void printPin(PrintWriter ibisWriter, ibisPin pin) {
    if (pin.model != null)
    { if (pin.model.noModel == 1) {
        s = "|";
      } else {
        s = "";
      }  }
    else { s = ""; }


    String s = String.valueOf(s) + pin.pinName;
    s = spaceFill(s, 7 - s.length());
    s = String.valueOf(s) + pin.signalName;
    s = spaceFill(s, 28 - s.length());
    s = String.valueOf(s) + pin.modelName;
    if (!goodies.IS_NOT_USED(pin.R_pin)) {

      s = spaceFill(s, 49 - s.length());
      String tempBuf = Get_Double_as_String(pin.R_pin, "");
      s = String.valueOf(s) + tempBuf;
      s = spaceFill(s, 59 - s.length());
      tempBuf = Get_Double_as_String(pin.L_pin, "H");
      s = String.valueOf(s) + tempBuf;
      s = spaceFill(s, 69 - s.length());
      tempBuf = Get_Double_as_String(pin.C_pin, "F");
      s = String.valueOf(s) + tempBuf;
    }
    printString(ibisWriter, s, 80, "");
  }





  void printSeriesPin(PrintWriter ibisWriter, ibisSeriesPin seriesPin) {
    String s = "";






    s = String.valueOf(s) + seriesPin.seriesPinName;
    s = spaceFill(s, 7 - s.length());
    s = String.valueOf(s) + seriesPin.seriesPin2name;
    s = spaceFill(s, 28 - s.length());
    s = String.valueOf(s) + seriesPin.modelName;
    s = spaceFill(s, 49 - s.length());
    if (seriesPin.fnTableGp != null) {
      s = String.valueOf(s) + seriesPin.fnTableGp;
    } else {
      s = (new StringBuilder(String.valueOf(s))).toString();
    }
    printString(ibisWriter, s, 80, "");
  }





  void printSeriesSwitchGp(PrintWriter ibisWriter, seriesSwitchGroup seriesSwitchGp) {
    String s = "";


    s = String.valueOf(s) + seriesSwitchGp.state;
    for (int i = 0; i < seriesSwitchGp.groupNames.length; i++)
    {
      s = String.valueOf(s) + " " + seriesSwitchGp.groupNames[i];
    }

    printString(ibisWriter, s, 80, "/");
  }














  void printModel(PrintWriter ibisWriter, ibisModel model, int ibisVersion) {
    String s = "";
    String numberBuffer = "";


    printHeader(ibisWriter, model.modelName, "Model");
    printString(ibisWriter, "[Model]", 80, model.modelName);


    s = getModelTypeAsString(model.modelType);
    printString(ibisWriter, "Model_type", 80, s);


    if (model.polarity == ConstantStuff.MODEL_POLARITY_NON_INVERTING) {
      s = "Non-Inverting";
    } else if (model.polarity == ConstantStuff.MODEL_POLARITY_INVERTING) {
      s = "Inverting";
    } else if (model.polarity == 0) {
      s = "";
    }
    if (!s.equals("")) {
      printString(ibisWriter, "Polarity      ", 80, s);
    }


    if (model.enable == ConstantStuff.MODEL_ENABLE_ACTIVE_HIGH) {
      s = "Active-High";
    } else if (model.enable == ConstantStuff.MODEL_ENABLE_ACTIVE_LOW) {
      s = "Active-Low";
    } else if (model.enable == 0) {
      s = "";
    }
    if (!s.equals("")) {
      printString(ibisWriter, "Enable       ", 80, s);
    }

    if (!goodies.IS_USE_NA(model.Vinl)) {

      s = Get_Double_as_String(model.Vinl, "V");
      printString(ibisWriter, "Vinl = ", 80, s);
    }

    if (!goodies.IS_USE_NA(model.Vinh)) {

      s = Get_Double_as_String(model.Vinh, "V");
      printString(ibisWriter, "Vinh = ", 80, s);
    }

    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.Vmeas)) {

      s = Get_Double_as_String(model.Vmeas, "V");
      printString(ibisWriter, "Vmeas = ", 80, s);
    }

    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.Cref)) {

      s = Get_Double_as_String(model.Cref, "F");
      printString(ibisWriter, "Cref = ", 80, s);
    }
    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.Rref)) {

      s = Get_Double_as_String(model.Rref, "");
      printString(ibisWriter, "Rref = ", 80, s);
    }
    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.Vref)) {

      s = Get_Double_as_String(model.Vref, "V");
      printString(ibisWriter, "Vref = ", 80, s);
    }

    s = Get_TypMinMax_as_String(model.c_comp, "F");
    printString(ibisWriter, "C_comp", 80, s);

    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.Rgnd.typ)) {

      s = Get_TypMinMax_as_String(model.Rgnd, "");
      printString(ibisWriter, "[Rgnd]      ", 80, s);
    }
    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.Rpower.typ)) {

      s = Get_TypMinMax_as_String(model.Rpower, "");
      printString(ibisWriter, "[Rpower]     ", 80, s);
    }
    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.Rac.typ)) {

      s = Get_TypMinMax_as_String(model.Rac, "");
      printString(ibisWriter, "[Rac]     ", 80, s);
    }
    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.Cac.typ)) {

      s = Get_TypMinMax_as_String(model.Cac, "F");
      printString(ibisWriter, "[Cac]     ", 80, s);
    }
    printString(ibisWriter, "|", 80, "");
    printString(ibisWriter, "|", 80, "");

    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.tempRange.typ)) {

      s = Get_TypMinMax_as_String(model.tempRange, "");
      printString(ibisWriter, "[Temperature Range]", 80, s);
    }

    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.voltageRange.typ)) {

      s = Get_TypMinMax_as_String(model.voltageRange, "V");
      printString(ibisWriter, "[Voltage Range]     ",
          80, s);
    }

    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.pullupRef.typ)) {

      s = Get_TypMinMax_as_String(model.pullupRef, "V");
      printString(ibisWriter, "[Pullup Reference]     ",
          80, s);
    }

    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.pulldownRef.typ)) {

      s = Get_TypMinMax_as_String(model.pulldownRef, "V");
      printString(ibisWriter, "[Pulldown Reference]     ",
          80, s);
    }

    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.powerClampRef.typ)) {

      s = Get_TypMinMax_as_String(model.powerClampRef, "V");
      printString(ibisWriter, "[POWER Clamp Reference]     ",
          80, s);
    }

    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
      !goodies.IS_USE_NA(model.gndClampRef.typ)) {

      s = Get_TypMinMax_as_String(model.gndClampRef, "V");
      printString(ibisWriter, "[GND Clamp Reference]     ",
          80, s);
    }

    if (model.pulldown != null) {

      printString(ibisWriter, "[Pulldown]", 80, "");
      print_VItable(ibisWriter, model.pulldown);
    }

    if (model.pullup != null) {

      printString(ibisWriter, "[Pullup]", 80, "");
      print_VItable(ibisWriter, model.pullup);
    }
    if (model.gnd_clamp != null) {

      printString(ibisWriter, "[GND_clamp]", 80, "");
      printClampTable(ibisWriter, model.gnd_clamp, model.clampTol);
    }
    if (model.power_clamp != null) {

      printString(ibisWriter, "[POWER_clamp]", 80, "");
      printClampTable(ibisWriter, model.power_clamp, model.clampTol);
    }
    if (!goodies.IS_USE_NA(model.ramp.dv_r.typ))
    {
      printRamp(ibisWriter, model.ramp, model.Rload);
    }


    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE) {

      VdsList VdsList1 = model.seriesModel.series_MOSFET.vdslist;
      VdsList1.gototop();
      if (model.seriesModel.OnState)
      {
        printString(ibisWriter, "[On]", 80, "");
      }
      for (int i = 0; i < VdsList1.count; i++) {

        ibisVItable seriesVITable = VdsList1.current.seriesVITable;

        printString(ibisWriter, "[series MOSFET]", 80, "");
        numberBuffer = Get_Double_as_String(VdsList1.current.V, "");
        printString(ibisWriter, "Vds = ", 80, numberBuffer);
        print_VItable(ibisWriter, VdsList1.current.seriesVITable);

        VdsList1.next();
      }
      if (model.seriesModel.OffState)
      {
        printString(ibisWriter, "[Off]", 80, "");
      }
      if (ibisVersion != ConstantStuff.VERSION_ONE_ONE &&
        !goodies.IS_USE_NA(model.seriesModel.RSeriesOff.typ)) {

        s = Get_TypMinMax_as_String(model.seriesModel.RSeriesOff, "");
        printString(ibisWriter, "[R Series]     ", 80, s);
      }
    }



    if (ibisVersion != ConstantStuff.VERSION_ONE_ONE) {

      waveTableList risingWaveL = model.risingWaveList;
      waveTableList fallingWaveL = model.fallingWaveList;

      risingWaveL.gototop();
      fallingWaveL.gototop();
      int i;
      for (i = 0; i < risingWaveL.count; i++) {

        ibisWaveTable risingWave = risingWaveL.current;
        printString(ibisWriter, "[Rising Waveform]", 80, "");
        numberBuffer = Get_Double_as_String(risingWave.R_fixture, "");
        printString(ibisWriter, "R_fixture=", 80, numberBuffer);
        numberBuffer = Get_Double_as_String(risingWave.V_fixture, "");
        printString(ibisWriter, "V_fixture=", 80, numberBuffer);

        if (!goodies.IS_USE_NA(risingWave.V_fixture_min)) {

          numberBuffer = Get_Double_as_String(risingWave.V_fixture_min, "");
          printString(ibisWriter, "V_fixture_min=", 80, numberBuffer);
        }
        if (!goodies.IS_USE_NA(risingWave.V_fixture_max)) {

          numberBuffer = Get_Double_as_String(risingWave.V_fixture_max, "");
          printString(ibisWriter, "V_fixture_max=", 80, numberBuffer);
        }
        if (!goodies.IS_USE_NA(risingWave.L_fixture)) {

          numberBuffer = Get_Double_as_String(risingWave.L_fixture, "H");
          printString(ibisWriter, "L_fixture=", 80, numberBuffer);
        }
        if (!goodies.IS_USE_NA(risingWave.C_fixture)) {

          numberBuffer = Get_Double_as_String(risingWave.C_fixture, "F");
          printString(ibisWriter, "C_fixture=", 80, numberBuffer);
        }
        if (!goodies.IS_USE_NA(risingWave.R_dut)) {

          numberBuffer = Get_Double_as_String(risingWave.R_dut, "");
          printString(ibisWriter, "R_dut=", 80, numberBuffer);
        }
        if (!goodies.IS_USE_NA(risingWave.L_dut)) {

          numberBuffer = Get_Double_as_String(risingWave.L_dut, "L");
          printString(ibisWriter, "L_dut=", 80, numberBuffer);
        }
        if (!goodies.IS_USE_NA(risingWave.C_dut)) {

          numberBuffer = Get_Double_as_String(risingWave.L_dut, "F");
          printString(ibisWriter, "C_dut=", 80, numberBuffer);
        }

        printWaveTable(ibisWriter, risingWave);
        risingWaveL.next();
      }
      for (i = 0; i < fallingWaveL.count; i++) {

        ibisWaveTable fallingWave = fallingWaveL.current;
        printString(ibisWriter, "[Falling Waveform]", 80, "");
        numberBuffer = Get_Double_as_String(fallingWave.R_fixture, "");
        printString(ibisWriter, "R_fixture=", 80, numberBuffer);
        numberBuffer = Get_Double_as_String(fallingWave.V_fixture, "");
        printString(ibisWriter, "V_fixture=", 80, numberBuffer);

        if (!goodies.IS_USE_NA(fallingWave.V_fixture_min)) {

          numberBuffer = Get_Double_as_String(fallingWave.V_fixture_min, "");
          printString(ibisWriter, "V_fixture_min=", 80, numberBuffer);
        }
        if (!goodies.IS_USE_NA(fallingWave.V_fixture_max)) {

          numberBuffer = Get_Double_as_String(fallingWave.V_fixture_max, "");
          printString(ibisWriter, "V_fixture_max=", 80, numberBuffer);
        }
        if (!goodies.IS_USE_NA(fallingWave.L_fixture)) {

          numberBuffer = Get_Double_as_String(fallingWave.L_fixture, "H");
          printString(ibisWriter, "L_fixture=", 80, numberBuffer);
        }
        if (!goodies.IS_USE_NA(fallingWave.C_fixture)) {

          numberBuffer = Get_Double_as_String(fallingWave.C_fixture, "F");
          printString(ibisWriter, "C_fixture=", 80, numberBuffer);
        }
        if (!goodies.IS_USE_NA(fallingWave.R_dut)) {

          numberBuffer = Get_Double_as_String(fallingWave.R_dut, "");
          printString(ibisWriter, "R_dut=", 80, numberBuffer);
        }
        if (!goodies.IS_USE_NA(fallingWave.L_dut)) {

          numberBuffer = Get_Double_as_String(fallingWave.L_dut, "L");
          printString(ibisWriter, "L_dut=", 80, numberBuffer);
        }
        if (!goodies.IS_USE_NA(fallingWave.C_dut)) {

          numberBuffer = Get_Double_as_String(fallingWave.L_dut, "F");
          printString(ibisWriter, "C_dut=", 80, numberBuffer);
        }

        printWaveTable(ibisWriter, fallingWave);
        fallingWaveL.next();
      }
    }
    s = "|End [Model] " + model.modelName;
    printString(ibisWriter, s, 80, "");
  }







  String getModelTypeAsString(int modelType) {
    String s = "";
    if (modelType == ConstantStuff.MODEL_TYPE_INPUT) {
      s = "Input";
    } else if (modelType == ConstantStuff.MODEL_TYPE_OUTPUT) {
      s = "Output";
    } else if (modelType == ConstantStuff.MODEL_TYPE_3_STATE) {
      s = "3-state";
    } else if (modelType == ConstantStuff.MODEL_TYPE_OPEN_DRAIN) {
      s = "Open_drain";
    } else if (modelType == ConstantStuff.MODEL_TYPE_I_O) {
      s = "I/O";
    } else if (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN) {
      s = "I/O_Open_Drain";
    } else if (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK) {
      s = "I/O_open_sink";
    } else if (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE) {
      s = "I/O_open_source";
    } else if (modelType == ConstantStuff.MODEL_TYPE_INPUT_ECL) {
      s = "Input_ECL";
    } else if (modelType == ConstantStuff.MODEL_TYPE_I_O_ECL) {
      s = "I/O_ECL";
    } else if (modelType == ConstantStuff.MODEL_TYPE_TERMINATOR) {
      s = "Terminator";
    } else if (modelType == ConstantStuff.MODEL_TYPE_OPEN_SINK) {
      s = "Open_sink";
    } else if (modelType == ConstantStuff.MODEL_TYPE_OPEN_SOURCE) {
      s = "Open_Source";
    } else if (modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL) {
      s = "Output_ECL";
    }
    else if (modelType == ConstantStuff.MODEL_TYPE_SERIES) {
      s = "Series";
    } else if (modelType == ConstantStuff.MODEL_TYPE_SERIES_SWITCH) {
      s = "Series_switch";
    }
    else if (modelType == 0) {
      s = "??undefined??";
    } else {
      s = "??undefined??";
    }
    return s;
  }




  int print_VItable(PrintWriter ibisWriter, ibisVItable VItable) {
    int size = VItable.size;
    String s = "";
    String s1 = "";
    if (VItable == null)
      return 1;
    if (VItable.VIs == null) {
      return 1;
    }


    printString(ibisWriter, "|Voltage", 80,
        "  I(typ)              I(min)              I(max)");
    printString(ibisWriter, "|", 80, "");

    for (int i = 0; i < size; i++) {

      s = Get_TypMinMax_as_String((VItable.VIs[i]).i, "A");
      BigDecimal bd = new BigDecimal((VItable.VIs[i]).v);
      s1 = "  " + bd.setScale(2, 4);

      printString(ibisWriter, s1, 80, s);
    }

    printString(ibisWriter, "|", 80, "");

    return 0;
  }






  int printClampTable(PrintWriter ibisWriter, ibisVItable clampTable, double clampTol) {
    int size = clampTable.size;
    String s1 = "";
    String s = "";

    int lastPrinted = 0;


    if (clampTable == null)
      return 1;
    if (clampTable.VIs == null) {
      return 1;
    }
    printString(ibisWriter, "|Voltage", 80,
        "  I(typ)              I(min)              I(max)");
    printString(ibisWriter, "|", 80, "");

    BigDecimal bd = new BigDecimal((clampTable.VIs[0]).v);
    s1 = "  " + bd.setScale(2, 4);
    ibisTypMinMax tempCurrent = (clampTable.VIs[0]).i;
    if (goodies.fabs(tempCurrent.typ) < clampTol)
      tempCurrent.typ = 0.0D;
    if (goodies.fabs(tempCurrent.min) < clampTol)
      tempCurrent.min = 0.0D;
    if (goodies.fabs(tempCurrent.max) < clampTol) {
      tempCurrent.max = 0.0D;
    }
    s = Get_TypMinMax_as_String(tempCurrent, "A");
    printString(ibisWriter, s1, 80, s);






    for (int i = 1; i < size - 1; i++) {

      tempCurrent = (clampTable.VIs[i]).i;
      if (goodies.fabs(tempCurrent.typ) > clampTol ||
        goodies.fabs(tempCurrent.min) > clampTol ||
        goodies.fabs(tempCurrent.max) > clampTol) {

        if (i > lastPrinted + 1) {

          bd = new BigDecimal((clampTable.VIs[i - 1]).v);
          s1 = "  " + bd.setScale(2, 4);
          tempCurrent.typ = 0.0D;
          tempCurrent.min = 0.0D;
          tempCurrent.max = 0.0D;
          s = Get_TypMinMax_as_String(tempCurrent, "A");
          printString(ibisWriter, s1, 80, s);
          tempCurrent = (clampTable.VIs[i]).i;
        }
        bd = new BigDecimal((clampTable.VIs[i]).v);
        s1 = "  " + bd.setScale(2, 4);

        if (goodies.fabs(tempCurrent.typ) < clampTol)
          tempCurrent.typ = 0.0D;
        if (goodies.fabs(tempCurrent.min) < clampTol)
          tempCurrent.min = 0.0D;
        if (goodies.fabs(tempCurrent.max) < clampTol) {
          tempCurrent.max = 0.0D;
        }
        s = Get_TypMinMax_as_String(tempCurrent, "A");
        printString(ibisWriter, s1, 80, s);
        lastPrinted = i;

      }
      else if (i != 1 && i == lastPrinted + 1) {

        bd = new BigDecimal((clampTable.VIs[i]).v);
        s1 = "  " + bd.setScale(2, 4);
        tempCurrent.typ = 0.0D;
        tempCurrent.min = 0.0D;
        tempCurrent.max = 0.0D;
        s = Get_TypMinMax_as_String(tempCurrent, "A");
        printString(ibisWriter, s1, 80, s);
      }
    }

    bd = new BigDecimal((clampTable.VIs[size - 1]).v);
    s1 = "  " + bd.setScale(2, 4);
    tempCurrent = (clampTable.VIs[size - 1]).i;
    if (goodies.fabs(tempCurrent.typ) < clampTol)
      tempCurrent.typ = 0.0D;
    if (goodies.fabs(tempCurrent.min) < clampTol)
      tempCurrent.min = 0.0D;
    if (goodies.fabs(tempCurrent.max) < clampTol) {
      tempCurrent.max = 0.0D;
    }
    s = Get_TypMinMax_as_String(tempCurrent, "A");
    printString(ibisWriter, s1, 80, s);
    printString(ibisWriter, "|", 80, "");
    return 0;
  }






  int printWaveTable(PrintWriter ibisWriter, ibisWaveTable waveTable) {
    int size = waveTable.size;




    if (waveTable == null)
      return 1;
    if (waveTable.waveData == null) {
      return 1;
    }
    printString(ibisWriter, "|time ", 80,
        "  V(typ)              V(min)              V(max)");
    printString(ibisWriter, "|", 80, "");

    for (int i = 0; i < size; i++) {

      String s1 = Get_Double_as_String_for_time((waveTable.waveData[i]).t, "S");
      s1 = spaceFill(s1, 15 - s1.length());
      String s = Get_TypMinMax_as_String((waveTable.waveData[i]).v, "V");
      printString(ibisWriter, s1, 80, s);
    }
    printString(ibisWriter, "|", 80, "");
    return 0;
  }









  void printRamp(PrintWriter ibisWriter, ibisRamp ramp, double rload) {
    printString(ibisWriter, "[Ramp]", 80, "");
    printString(ibisWriter,
        "| variable       typ                 min                 max",
        80, "");


    if (!goodies.IS_USE_NA(ramp.dv_r.typ)) {

      s = Get_Double_as_String(ramp.dv_r.typ, "");
      String str1 = Get_Double_as_String(ramp.dt_r.typ, "");
      String dummyBuffer = "/" + str1;
      s = String.valueOf(s) + dummyBuffer;
    } else {

      s = "NA";
    }  String s = spaceFill(s, 20 - s.length());

    if (!goodies.IS_USE_NA(ramp.dv_r.min)) {

      String str1 = Get_Double_as_String(ramp.dv_r.min, "");
      s = String.valueOf(s) + str1;
      str1 = Get_Double_as_String(ramp.dt_r.min, "");
      String dummyBuffer = "/" + str1;
      s = String.valueOf(s) + dummyBuffer;
    }
    else {

      String dummyBuffer = "NA";
      s = String.valueOf(s) + dummyBuffer;
    }
    s = spaceFill(s, 40 - s.length());

    if (!goodies.IS_USE_NA(ramp.dv_r.max)) {

      String str2 = Get_Double_as_String(ramp.dv_r.max, "");
      s = String.valueOf(s) + str2;
      str2 = Get_Double_as_String(ramp.dt_r.max, "");
      String str1 = "/" + str2;
      s = String.valueOf(s) + str1;
    }
    else {

      String str = "NA";
      s = String.valueOf(s) + str;
    }
    printString(ibisWriter, "dV/dt_r", 80, s);


    if (!goodies.IS_USE_NA(ramp.dv_f.typ)) {

      s = Get_Double_as_String(ramp.dv_f.typ, "");
      String str2 = Get_Double_as_String(ramp.dt_f.typ, "");
      String str1 = "/" + str2;
      s = String.valueOf(s) + str1;
    } else {

      s = "NA";
    }  s = spaceFill(s, 20 - s.length());

    if (!goodies.IS_USE_NA(ramp.dv_f.min)) {

      String str2 = Get_Double_as_String(ramp.dv_f.min, "");
      s = String.valueOf(s) + str2;
      str2 = Get_Double_as_String(ramp.dt_f.min, "");
      String str1 = "/" + str2;
      s = String.valueOf(s) + str1;
    }
    else {

      String str = "NA";
      s = String.valueOf(s) + str;
    }
    s = spaceFill(s, 40 - s.length());

    if (!goodies.IS_USE_NA(ramp.dv_f.max)) {

      String str2 = Get_Double_as_String(ramp.dv_f.max, "");
      s = String.valueOf(s) + str2;
      str2 = Get_Double_as_String(ramp.dt_f.max, "");
      String str1 = "/" + str2;
      s = String.valueOf(s) + str1;
    }
    else {

      String str = "NA";
      s = String.valueOf(s) + str;
    }

    printString(ibisWriter, "dV/dt_f", 80, s);
    String numberBuffer = Get_Double_as_String(rload, "");
    printString(ibisWriter, "R_load =", 80, numberBuffer);
    printString(ibisWriter, "|", 80, "");
  }







  String spaceFill(String str, int numSpaces) {
    for (int i = 0; i < numSpaces; i++)
      str = String.valueOf(str) + " ";
    return str;
  }


  String Get_TypMinMax_as_String(ibisTypMinMax TypMinMax, String trailStr) {
    String dummyStr = "";
    String s = "";


    s = "  " + Get_Double_as_String(TypMinMax.typ, trailStr);
    int position = s.length();
    s = spaceFill(s, 20 - position);
    dummyStr = Get_Double_as_String(TypMinMax.min, trailStr);
    s = String.valueOf(s) + dummyStr;
    position = s.length();
    s = spaceFill(s, 40 - position);
    dummyStr = Get_Double_as_String(TypMinMax.max, trailStr);
    s = String.valueOf(s) + dummyStr;
    return s;
  }





  String Get_Double_as_String(double number, String trailStr) {
    String s = "";
    double exponent = 1.0E-15D;

    int expFound = 0;

    if (goodies.IS_USE_NA(number)) {
      s = "NA";
    } else {

      for (int i = 0; i < 9; i++) {

        if (isExponent(number, exponent)) {

          BigDecimal bd = new BigDecimal(number / exponent);

          s = bd.setScale(4, 4) + s2iString.SIsuffixString[i] + trailStr;
          expFound = 1;

          break;
        }
        exponent *= 1000.0D;
      }
      if (expFound == 0)
        s = String.valueOf(number) + trailStr;
    }
    return s;
  }

  String Get_Double_as_String_for_time(double number, String trailStr) {
    String s = "";
    double exponent = 1.0E-15D;

    int expFound = 0;

    if (goodies.IS_USE_NA(number)) {
      s = "NA";
    } else {

      for (int i = 0; i < 9; i++) {

        if (isExponent(number, exponent)) {

          BigDecimal bd = new BigDecimal(number / exponent);
          s = bd.setScale(2, 4) + s2iString.SIsuffixString[i] + trailStr;
          expFound = 1;

          break;
        }
        exponent *= 1000.0D;
      }
      if (expFound == 0)
        s = String.valueOf(number) + trailStr;
    }
    return s;
  }


  boolean isExponent(double number, double expon) {
    if (goodies.fabs(number / expon) >= 0.1D && goodies.fabs(number / expon) < 100.0D) {
      return true;
    }
    return false;
  }


  void printTypMinMaxHeader(PrintWriter ibisWriter) {
    printString(ibisWriter, "| variable       typ                 min                 max",
        80, "");
  }



  void printHeader(PrintWriter ibisWriter, String name, String heading) {
    String spaceFill = " ";
    int spacing = (62 - heading.length() + name.length()) / 2;
    for (int i2 = 0; i2 < spacing; i2++) {
      spaceFill = String.valueOf(spaceFill) + " ";
    }
    ibisWriter.println("|************************************************************************");
    printString(ibisWriter, "|", 80, String.valueOf(spaceFill) + heading + " " + name);
    ibisWriter.println("|************************************************************************");
    printString(ibisWriter, "|", 80, "");
  }





  void printString(PrintWriter ibisWriter, String indent, int width, String string) {
    int j = 1;
    StringTokenizer st = new StringTokenizer(string);

    int cnt = st.countTokens();
    int totalLength = 0;
    String nextTok = "";

    String newString = indent;
    if (indent.length() < 8) {

      newString = String.valueOf(newString) + " " + " ";
      if (string.length() > width) {

        for (int i = 0; i < cnt; i++) {

          nextTok = st.nextToken();
          newString = String.valueOf(newString) + " " + nextTok;

          if (totalLength > 1024) {
            break;
          }
          totalLength += nextTok.length();

          if (newString.length() >= j * width) {

            newString = String.valueOf(newString) + "\n  ";
            j++;
          }
        }
      } else {

        newString = String.valueOf(newString) + string;
      }
    } else {

      newString = String.valueOf(newString) + " ";
      if (string.length() > width) {

        for (int i = 0; i < cnt; i++) {

          nextTok = st.nextToken();
          newString = String.valueOf(newString) + " " + nextTok;
          totalLength += nextTok.length();
          if (totalLength > 1024) {
            break;
          }
          if (newString.length() + 2 * j * 8 >= j * width) {

            newString = String.valueOf(newString) + "\n  ";
            j++;
          }
        }
      } else {

        newString = String.valueOf(newString) + string;
      }
    }  ibisWriter.println(newString);
  }
}

#endif

