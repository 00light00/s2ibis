#ifndef _ANALYZEPIN
#define _ANALYZEPIN
class analyzePin
{
  ibisPin currentPin;

  public int analyzePin(ibisPin enablePin, ibisPin inputPin, ibisPin pullupPin, ibisPin pulldownPin, ibisPin powerClampPin, ibisPin gndClampPin, int spiceType, String spiceFile, String seriesSpiceFile, String spiceCommand, int iterate, int cleanup) throws IOException {
    int result = 0;
    int i = 0;
    int index = 0;
    ibisVItable pullupData = null;
    ibisVItable puDisabledData = null;
    ibisVItable pulldownData = null;
    ibisVItable pdDisabledData = null;
    ibisVItable powerClampData = null;
    ibisVItable gndClampData = null;

    waveTableList risingWave = new waveTableList();
    waveTableList fallingWave = new waveTableList();


    VITableList seriesVITable = new VITableList();
    int index2 = 0;
    double currentVds = 0.0D;
    VdsList VdsList1 = new VdsList();


    ibisTypMinMax Vcc = new ibisTypMinMax();
    ibisTypMinMax VccClamp = new ibisTypMinMax();
    ibisTypMinMax Gnd = new ibisTypMinMax();
    ibisTypMinMax GndClamp = new ibisTypMinMax();
    ibisTypMinMax sweepStart = new ibisTypMinMax();
    ibisTypMinMax sweepStart_pc = new ibisTypMinMax();
    double sweepRange = 0.0D;
    double sweepRange_pc = 0.0D;
    double sweepStep = 0.0D;
    double sweepStep_pc = 0.0D;
    double diodeDrop = 0.0D;
    double diodeDrop_pc = 0.0D;
    double subtractStart = 0.0D;
    double subtractEnd = 0.0D;
    setupVoltages setupVoltages1 = new setupVoltages();
    sortVIData sortVIData1 = new sortVIData();
    sortVISeriesData sortSeriesData1 = new sortVISeriesData();


    generateVICurve genVICurve1 = new generateVICurve();
    generateRampData genRmpData1 = new generateRampData();
    generateWaveData genWaveData1 = new generateWaveData();

    if (this.currentPin.seriesModel != null)
    {
      if (goodies.THIS_MODEL_NEEDS_SERIES_VI_DATA(this.currentPin.seriesModel.modelType)) {

        System.out.println("\nThis Model Needs series VI Data ..");
        setupVoltages1.setupVoltages(10,
            this.currentPin.seriesModel);

        sweepStep = setupVoltages1.sweepStep;
        sweepRange = setupVoltages1.sweepRange;
        diodeDrop = setupVoltages1.diodeDrop;
        sweepStart = setupVoltages1.sweepStart;
        Vcc = setupVoltages1.Vcc;
        Gnd = setupVoltages1.Gnd;

        VdsList1 = this.currentPin.seriesModel.seriesModel.series_MOSFET.vdslist;

        VdsList1.gototop();
        index2 = 0;
        VdsList1.gototop();
        while (index2 < 100 && VdsList1.current != null) {

          genVICurve1.VIData = VdsList1.current.seriesVITable;
          currentVds = VdsList1.current.V;

          result += genVICurve1.generateVICurve(this.currentPin, enablePin,
              inputPin, pullupPin, pulldownPin,
              powerClampPin, gndClampPin, Vcc, Gnd,
              VccClamp, GndClamp, sweepStart, sweepRange,
              sweepStep, 10, spiceType,
              seriesSpiceFile, spiceCommand, 1,
              1, iterate, cleanup, currentVds, index2);

          sortSeriesData1.VISeriesData = genVICurve1.VIData;
          sortSeriesData1.Vcc = Vcc;
          sortSeriesData1.sortVISeriesData();
          VdsList1.current.seriesVITable = sortSeriesData1.VISeriesData;
          index2++;
          VdsList1.next();
        }
      }
    }


    if (goodies.THIS_MODEL_NEEDS_PULLUP_DATA(this.currentPin.model.modelType)) {

      System.out.println("\nThis Model Needs PullupData ..");
      setupVoltages1.setupVoltages(2,
          this.currentPin.model);

      sweepStep = setupVoltages1.sweepStep;
      sweepRange = setupVoltages1.sweepRange;
      diodeDrop = setupVoltages1.diodeDrop;
      sweepStart = setupVoltages1.sweepStart;
      VccClamp = setupVoltages1.Vcc;
      GndClamp = setupVoltages1.Gnd;



      setupVoltages1.setupVoltages(0,
          this.currentPin.model);

      sweepStep = setupVoltages1.sweepStep;
      sweepRange = setupVoltages1.sweepRange;
      diodeDrop = setupVoltages1.diodeDrop;
      sweepStart = setupVoltages1.sweepStart;
      Vcc = setupVoltages1.Vcc;
      Gnd = setupVoltages1.Gnd;


      result += genVICurve1.generateVICurve(this.currentPin, enablePin,
          inputPin, pullupPin, pulldownPin,
          powerClampPin, gndClampPin, Vcc, Gnd,
          VccClamp, GndClamp, sweepStart, sweepRange,
          sweepStep, 0, spiceType,
          spiceFile, spiceCommand, 1,
          1, iterate, cleanup, 0.0D, 0);

      pullupData = genVICurve1.VIData;

      if (enablePin != null) {

        result += genVICurve1.generateVICurve(this.currentPin,
            enablePin, inputPin, pullupPin,
            pulldownPin, powerClampPin,
            gndClampPin, Vcc, Gnd, VccClamp,
            GndClamp, sweepStart, sweepRange,
            sweepStep, 4,
            spiceType, spiceFile, spiceCommand,
            0, 1,
            iterate, cleanup, 0.0D, 0);
        puDisabledData = genVICurve1.VIData;




        if (puDisabledData != null && pullupData != null) {






          setupVoltages1.setupVoltages(2,
              this.currentPin.model);




          i = 0;

          while (i < pullupData.size) {

            if (goodies.IS_USE_NA((pullupData.VIs[i]).i.typ) ||
              goodies.IS_USE_NA((puDisabledData.VIs[i]).i.typ)) {
              (pullupData.VIs[i]).i.typ = -1.33287736222333E20D;
            } else {
              (pullupData.VIs[i]).i.typ = (pullupData.VIs[i]).i.typ -
                (puDisabledData.VIs[i]).i.typ;
            }

            if (goodies.IS_USE_NA((pullupData.VIs[i]).i.min) ||
              goodies.IS_USE_NA((puDisabledData.VIs[i]).i.min)) {
              (pullupData.VIs[i]).i.min = -1.33287736222333E20D;
            } else {
              (pullupData.VIs[i]).i.min = (pullupData.VIs[i]).i.min -
                (puDisabledData.VIs[i]).i.min;
            }  if (goodies.IS_USE_NA((pullupData.VIs[i]).i.max) ||
              goodies.IS_USE_NA((puDisabledData.VIs[i]).i.max)) {
              (pullupData.VIs[i]).i.max = -1.33287736222333E20D;
            } else {
              (pullupData.VIs[i]).i.max = (pullupData.VIs[i]).i.max -
                (puDisabledData.VIs[i]).i.max;
            }
            i++;
          }
        }
      }
    }







    if (goodies.THIS_MODEL_NEEDS_PULLDOWN_DATA(this.currentPin.model.modelType)) {

      System.out.println("This Model Needs PulldownData ..");





      setupVoltages1.setupVoltages(3, this.currentPin.model);

      sweepStep = setupVoltages1.sweepStep;
      sweepRange = setupVoltages1.sweepRange;
      diodeDrop = setupVoltages1.diodeDrop;
      sweepStart = setupVoltages1.sweepStart;
      VccClamp = setupVoltages1.Vcc;
      GndClamp = setupVoltages1.Gnd;

      setupVoltages1.setupVoltages(1, this.currentPin.model);

      sweepStep = setupVoltages1.sweepStep;
      sweepRange = setupVoltages1.sweepRange;
      diodeDrop = setupVoltages1.diodeDrop;
      sweepStart = setupVoltages1.sweepStart;
      Vcc = setupVoltages1.Vcc;
      Gnd = setupVoltages1.Gnd;


      result += genVICurve1.generateVICurve(this.currentPin, enablePin,
          inputPin, pullupPin, pulldownPin,
          powerClampPin, gndClampPin, Vcc, Gnd,
          VccClamp, GndClamp, sweepStart, sweepRange,
          sweepStep, 1, spiceType,
          spiceFile, spiceCommand, 1,
          0, iterate, cleanup, 0.0D, 0);
      pulldownData = genVICurve1.VIData;

      if (enablePin != null) {

        result += genVICurve1.generateVICurve(this.currentPin,
            enablePin, inputPin, pullupPin,
            pulldownPin, powerClampPin,
            gndClampPin, Vcc, Gnd, VccClamp,
            GndClamp, sweepStart, sweepRange, sweepStep,
            5, spiceType,
            spiceFile, spiceCommand, 0,
            0, iterate, cleanup, 0.0D, 0);
        pdDisabledData = genVICurve1.VIData;

        if (pdDisabledData != null && pulldownData != null) {


          setupVoltages1.setupVoltages(3, this.currentPin.model);

          i = 0;
          while (i < pulldownData.size) {

            if (goodies.IS_USE_NA((pulldownData.VIs[i]).i.typ) ||
              goodies.IS_USE_NA((pdDisabledData.VIs[i]).i.typ)) {
              (pulldownData.VIs[i]).i.typ = -1.33287736222333E20D;
            } else {
              (pulldownData.VIs[i]).i.typ = (pulldownData.VIs[i]).i.typ -
                (pdDisabledData.VIs[i]).i.typ;
            }  if (goodies.IS_USE_NA((pulldownData.VIs[i]).i.min) ||
              goodies.IS_USE_NA((pdDisabledData.VIs[i]).i.min)) {
              (pulldownData.VIs[i]).i.min = -1.33287736222333E20D;
            } else {
              (pulldownData.VIs[i]).i.min = (pulldownData.VIs[i]).i.min -
                (pdDisabledData.VIs[i]).i.min;
            }  if (goodies.IS_USE_NA((pulldownData.VIs[i]).i.max) ||
              goodies.IS_USE_NA((pdDisabledData.VIs[i]).i.max)) {
              (pulldownData.VIs[i]).i.max = -1.33287736222333E20D;
            } else {
              (pulldownData.VIs[i]).i.max = (pulldownData.VIs[i]).i.max -
                (pdDisabledData.VIs[i]).i.max;
            }  i++;
          }
        }
      }
    }






    if (goodies.THIS_MODEL_NEEDS_POWER_CLAMP_DATA(this.currentPin.model.modelType)) {

      System.out.println("\nThis Model Needs Power ClampData ..");

      setupVoltages1.setupVoltages(0, this.currentPin.model);

      sweepStep = setupVoltages1.sweepStep;
      sweepRange = setupVoltages1.sweepRange;
      diodeDrop = setupVoltages1.diodeDrop;
      sweepStart = setupVoltages1.sweepStart;
      Vcc = setupVoltages1.Vcc;
      Gnd = setupVoltages1.Gnd;


      setupVoltages1.setupVoltages(2, this.currentPin.model);

      sweepStep = setupVoltages1.sweepStep;
      sweepRange = setupVoltages1.sweepRange;
      diodeDrop = setupVoltages1.diodeDrop;
      sweepStart = setupVoltages1.sweepStart;
      VccClamp = setupVoltages1.Vcc;
      GndClamp = setupVoltages1.Gnd;


      result += genVICurve1.generateVICurve(this.currentPin, enablePin,
          inputPin, pullupPin, pulldownPin,
          powerClampPin, gndClampPin, Vcc, Gnd,
          VccClamp, GndClamp, sweepStart, sweepRange,
          sweepStep, 2, spiceType,
          spiceFile, spiceCommand, 0,
          1, iterate, cleanup, 0.0D, 0);
      powerClampData = genVICurve1.VIData;
    }

    if (goodies.THIS_MODEL_NEEDS_GND_CLAMP_DATA(this.currentPin.model.modelType)) {

      System.out.println("This Model Needs GND ClampData ..");
      setupVoltages1.setupVoltages(1, this.currentPin.model);

      sweepStep = setupVoltages1.sweepStep;
      sweepRange = setupVoltages1.sweepRange;
      diodeDrop = setupVoltages1.diodeDrop;
      sweepStart = setupVoltages1.sweepStart;
      Vcc = setupVoltages1.Vcc;
      Gnd = setupVoltages1.Gnd;


      setupVoltages1.setupVoltages(3, this.currentPin.model);

      sweepStep = setupVoltages1.sweepStep;
      sweepRange = setupVoltages1.sweepRange;
      diodeDrop = setupVoltages1.diodeDrop;
      sweepStart = setupVoltages1.sweepStart;
      VccClamp = setupVoltages1.Vcc;
      GndClamp = setupVoltages1.Gnd;

      result += genVICurve1.generateVICurve(this.currentPin, enablePin,
          inputPin, pullupPin, pulldownPin,
          powerClampPin, gndClampPin, Vcc, Gnd,
          VccClamp, GndClamp, sweepStart, sweepRange,
          sweepStep, 3, spiceType,
          spiceFile, spiceCommand, 0,
          0, iterate, cleanup, 0.0D, 0);
      gndClampData = genVICurve1.VIData;
    }


    sortVIData1.sortVIData(this.currentPin.model, pullupData, pulldownData,
        powerClampData, gndClampData);






    if (goodies.THIS_MODEL_NEEDS_TRANSIENT_DATA(this.currentPin.model.modelType)) {

      System.out.println("This Model Needs Transient Data ..");
      setupVoltages1.setupVoltages(2, this.currentPin.model);

      sweepStep = setupVoltages1.sweepStep;
      sweepRange = setupVoltages1.sweepRange;
      diodeDrop = setupVoltages1.diodeDrop;
      sweepStart = setupVoltages1.sweepStart;
      VccClamp = setupVoltages1.Vcc;
      GndClamp = setupVoltages1.Gnd;

      setupVoltages1.setupVoltages(6, this.currentPin.model);

      sweepStep = setupVoltages1.sweepStep;
      sweepRange = setupVoltages1.sweepRange;
      diodeDrop = setupVoltages1.diodeDrop;
      sweepStart = setupVoltages1.sweepStart;
      Vcc = setupVoltages1.Vcc;
      Gnd = setupVoltages1.Gnd;

      result += genRmpData1.generateRampData(this.currentPin, enablePin, inputPin,
          pullupPin, pulldownPin, powerClampPin,
          gndClampPin, Vcc, Gnd, VccClamp, GndClamp,
          6, spiceType, spiceFile,
          spiceCommand, iterate, cleanup);
      result += genRmpData1.generateRampData(this.currentPin, enablePin, inputPin,
          pullupPin, pulldownPin, powerClampPin,
          gndClampPin, Vcc, Gnd, VccClamp, GndClamp,
          7, spiceType, spiceFile,
          spiceCommand, iterate, cleanup);

      risingWave = this.currentPin.model.risingWaveList;
      fallingWave = this.currentPin.model.fallingWaveList;

      index = 0;
      risingWave.gototop();
      while (index < 100 && risingWave.current != null) {

        genWaveData1.currentWave = risingWave.current;

        result += genWaveData1.generateWaveData(this.currentPin, enablePin,
            inputPin, pullupPin, pulldownPin,
            powerClampPin, gndClampPin, Vcc, Gnd,
            VccClamp, GndClamp, 8,
            spiceType, spiceFile, spiceCommand,
            iterate, cleanup, index);
        index++;
        risingWave.next();
      }


      index = 0;
      fallingWave.gototop();
      while (index < 100 && fallingWave.current != null) {

        genWaveData1.currentWave = fallingWave.current;
        result += genWaveData1.generateWaveData(this.currentPin, enablePin,
            inputPin, pullupPin, pulldownPin,
            powerClampPin, gndClampPin, Vcc, Gnd,
            VccClamp, GndClamp,
            9, spiceType,
            spiceFile, spiceCommand, iterate, cleanup,
            index);
        index++;
        fallingWave.next();
      }
    }

    return result;
  }
}

#endif
