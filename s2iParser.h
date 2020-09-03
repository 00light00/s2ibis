/*******************************************************************************
*File Name	: s2iParser.java
*Description	: This is the parser that parses the *.s2i file
*		:
*		: North Carolina State University
*		: Electronics Research Laboratory
********************************************************************************
$Log: s2iParser.java,v $
Revision 1.4  2005/02/24 22:53:23  akvarma
Added code for extSpiceCmdFile.

Revision 1.3  2003/11/24 06:01:38  akvarma
Added series MOSFET functionality. Also added Series Pin Mapping, on, off, R
Series and other related keywords.

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

*/

// import java.io.*;
// import java.util.*;
// import java.util.regex.*;
// import java.lang.string.*;
// import java.awt.List;
// import java.text.SimpleDateFormat;

/**
 * This is the entry point of the parser.
 * IN: 	*.s2i File
 * OUT:	ibisTOP structure
 *	ibisGlobal structure
 **/

#include <chrono>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

#include "s2iHeader.cpp"

class s2iReader {
  string inFile;
  ibisTOP ibisStruct;
  ibisGlobal ibisGlobal;
};

class s2iParser {
  ibisTOP ibis;
  ibisGlobal global;
  ibisTypMinMax typMinMax;

  // Linked List declarations
  pinMapList pmList = new pinMapList();
  ibisPinMap tempPinMap = new ibisPinMap();
  pinsList pList = new pinsList();
  ibisPin tempPin = new ibisPin();

  waveTableList risingWaveList = new waveTableList();
  waveTableList fallingWaveList = new waveTableList();
  ibisWaveTable tempWaveTable = new ibisWaveTable();

  diffPinList dpList = new diffPinList();
  ;
  ibisDiffPin tempDiffPin = new ibisDiffPin();

  seriesPinsList spList = new seriesPinsList();
  ;
  ibisSeriesPin tempSeriesPin = new ibisSeriesPin();

  seriesSwitchGpList ssgList = new seriesSwitchGpList();
  ;
  seriesSwitchGroup tempSeriesSwitchGp = new seriesSwitchGroup();

  modelsList mList = new modelsList();
  ibisModel tempModel = new ibisModel();

  componentList cList = new componentList();
  ibisComponent tempComponent = new ibisComponent();

  int compCount = 0;
  int modelCount = 0;
  bool modelProc = false;
  bool componentProc = false;
  bool globalProc = false;
  // reorg
  Vds tempVds = new Vds();
  VdsList tempVdsList = new VdsList();
  ;
  // reorg

public:
  void Sp2iParse(string inFile) {
    fstream inBufRdr;
    string line;
    string key = "";
    string temp1 = "";
    double tempRLC;

    string fileNameBuffer;

    char timebuff[80];
    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    strftime(timebuff, 80, "%b %c", localtime(&tt));
    //    SimpleDateFormat sd = new SimpleDateFormat("EEEE MMM d yyyy hh:mm:ss
    //    z");

    ibis.date = timebuff;

    fileNameBuffer = inFile;
    StringTokenizer st = new StringTokenizer(fileNameBuffer, ".");
    fileNameBuffer = st.nextToken();
    if (fileNameBuffer.length() > ConstantStuff.MAX_FILENAME_BASE_LENGTH)
      fileNameBuffer =
          fileNameBuffer.substring(0, ConstantStuff.MAX_FILENAME_BASE_LENGTH);
    ibis.thisFileName = fileNameBuffer + "." + ConstantStuff.FILENAME_EXTENSION;

    printf("This File Name = " + ibis.thisFileName);
    printf("Date = " + ibis.date);

    if ((inFile != null) && (!inFile.trim().equals(""))) {
      // If the input fileName is specified.
      // initialise the data structure
      // initS2i(fileData, true);

      try {
        int pinNo = 0;
        inBufRdr = new BufferedReader(
            new InputStreamReader(new FileInputStream(inFile)));
        line = inBufRdr.readLine();
        while (line != null) {
          char firstChar = ' ';
          if (line.trim().length() > 0)
            firstChar = line.trim().charAt(0);
          else {
            line = inBufRdr.readLine();
            continue;
          }
          if (firstChar == '[') {
            // word to the left of ']' is key, to the right is argument
            StringTokenizer st1 = new StringTokenizer(line, "]");
            int numToken1 = st1.countTokens();
            if (numToken1 != 0) {
              temp1 = st1.nextToken();
              StringTokenizer st2 = new StringTokenizer(temp1, "[");
              int numToken2 = st2.countTokens();
              if (numToken2 != 0) {
                key = st2.nextToken();
                string arg =
                    (numToken1 > 1) ? st1.nextToken().trim() : new string("");

                /** further parsing based on key value **/
                processKey(key, arg);
              }
            }
          } else if (firstChar == '|') {
            // comments are to be ignored
          } else if ((key != null) && (key.equalsIgnoreCase("pin mapping"))) {
            tempComponent.hasPinMapping = true;
            // if the last key was 'Pin mapping'
            StringTokenizer st3 = new StringTokenizer(line);
            string firstToken = " ";
            int cnt3 = st3.countTokens();
            if (cnt3 != 0)
              firstToken = st3.nextToken();

            tempPinMap = new ibisPinMap();

            if (cnt3 == 3) {
              tempPinMap.pinName = firstToken;
              tempPinMap.pulldownRef = st3.nextToken();
              tempPinMap.pullupRef = st3.nextToken();
              tempPinMap.gndClampRef = "NC";
              tempPinMap.powerClampRef = "NC";

            } else if (cnt3 == 5) {
              tempPinMap.pinName = firstToken;
              tempPinMap.pulldownRef = st3.nextToken();
              tempPinMap.pullupRef = st3.nextToken();
              tempPinMap.gndClampRef = st3.nextToken();
              tempPinMap.powerClampRef = st3.nextToken();
            } else {
              // Put an error message here.
            }
            pmList.add(tempPinMap);

          }

          else if ((key != null) && (key.equalsIgnoreCase("diff pin"))) {
            //	 dpList		= new diffPinList();		//initialize it.
            // if the last key was 'diff pin'
            StringTokenizer st3 = new StringTokenizer(line);
            string firstToken = " ";
            int cnt3 = st3.countTokens();
            if (cnt3 != 0)
              firstToken = st3.nextToken();

            tempDiffPin = new ibisDiffPin();

            if (cnt3 == 4) {
              tempDiffPin.pinName = firstToken;
              tempDiffPin.invPin = st3.nextToken();
              tempDiffPin.vdiff = matchNum(st3.nextToken());
              tempDiffPin.tdelay_typ = matchNum(st3.nextToken());
            } else if (cnt3 == 6) {
              tempDiffPin.pinName = firstToken;
              tempDiffPin.invPin = st3.nextToken();
              tempDiffPin.vdiff = matchNum(st3.nextToken());
              tempDiffPin.tdelay_typ = matchNum(st3.nextToken());
              tempDiffPin.tdelay_min = matchNum(st3.nextToken());
              tempDiffPin.tdelay_max = matchNum(st3.nextToken());
            } else {
              // Put an error message here.
            }
            dpList.add(tempDiffPin);

          }

          else if ((key != null) && (key.equalsIgnoreCase("disclaimer"))) {
            ibis.disclaimer = ibis.disclaimer + " " + line;
          }

          else if ((key != null) && (key.equalsIgnoreCase("Pin"))) {
            // if the last key was 'Pin'
            StringTokenizer st4 = new StringTokenizer(line);
            string firstToken = " ";
            int cnt4 = st4.countTokens();

            if (cnt4 != 0) {
              firstToken = st4.nextToken();
            }

            if ((firstToken != null) && (firstToken.equalsIgnoreCase("->"))) {
              if (cnt4 == 2) {
                tempPin.inputPin = st4.nextToken();
              } else if (cnt4 == 3) {
                tempPin.inputPin = st4.nextToken();
                tempPin.enablePin = st4.nextToken();
              }
            } else {
              tempPin = new ibisPin();
              if (cnt4 == 4) {
                tempPin.pinName = firstToken;
                tempPin.spiceNodeName = st4.nextToken();
                tempPin.signalName = st4.nextToken();
                tempPin.modelName = st4.nextToken();
              } else if (cnt4 == 7) {
                tempPin.pinName = firstToken;
                tempPin.spiceNodeName = st4.nextToken();
                tempPin.signalName = st4.nextToken();
                tempPin.modelName = st4.nextToken();
                // RLC are Floats
                tempRLC = new Double(matchNum(st4.nextToken()));
                tempPin.R_pin = tempRLC.floatValue();
                tempRLC = new Double(matchNum(st4.nextToken()));
                tempPin.L_pin = tempRLC.floatValue();
                tempRLC = new Double(matchNum(st4.nextToken()));
                tempPin.C_pin = tempRLC.floatValue();
              } else {
                // Put an error message here.
              }
              pList.add(tempPin);
            }
          } // if ((key != null) && (key.equalsIgnoreCase("Pin")))

          else if ((key != null) &&
                   (key.equalsIgnoreCase("Series Pin Mapping"))) {
            //	 spList		= new seriesPinsList();		//initialize it.
            StringTokenizer st5 = new StringTokenizer(line);
            string firstToken = " ";
            int cnt5 = st5.countTokens();
            if (cnt5 != 0)
              firstToken = st5.nextToken();

            tempSeriesPin = new ibisSeriesPin();

            if (cnt5 == 3) {
              tempSeriesPin.seriesPinName = firstToken;
              tempSeriesPin.seriesPin2name = st5.nextToken();
              tempSeriesPin.modelName = st5.nextToken();
            } else if (cnt5 == 4) {
              tempSeriesPin.seriesPinName = firstToken;
              tempSeriesPin.seriesPin2name = st5.nextToken();
              tempSeriesPin.modelName = st5.nextToken();
              tempSeriesPin.fnTableGp = st5.nextToken();
            } else {
              // Put an error message here.
            }
            spList.add(tempSeriesPin);
          } else {
            // series switch group
            if ((key != null) &&
                (key.equalsIgnoreCase("Series Switch Groups"))) {
              //	   ssgList		= new seriesSwitchGpList();
              ////initialize it.
              StringTokenizer st6 = new StringTokenizer(line);
              string firstToken = " ";
              int cnt6 = st6.countTokens();
              if (cnt6 != 0)
                firstToken = st6.nextToken();
              tempSeriesSwitchGp = new seriesSwitchGroup();
              tempSeriesSwitchGp.groupNames = new string[cnt6 - 1];
              tempSeriesSwitchGp.state = firstToken;
              for (int i = 0; i < cnt6 - 1; ++i) {
                string temp = st6.nextToken();
                tempSeriesSwitchGp.groupNames[i] = temp;
              }
              ssgList.add(tempSeriesSwitchGp);
            }
          }
          line = inBufRdr.readLine();
        } // while

        mList.add(tempModel);
        tempComponent.mList = mList;
        cList.add(tempComponent);

      } // try
      catch (java.io.IOException ioe) {
        string Msg = ioe.getMessage();
        if (Msg != null) {
          printf("s2ibis3: Unable to open " + inFile + " for reading");
          System.exit(1);
        }
      }
    } // if
  }   // s2iParse

  string newVal(string args) {
    string str;
    if ((args == null) || (args.equals("")) || (args.equals("NA")))
      str = new string("");
    else
      str = new string(args);
    return str;
  }

  /**
   * Depending on the key value, args are parsed and corresponding
   * s2i data structure is stuffed.
   *
   * @param key            the key value denoting parameter type
   * @param args           parameters values
   * @param sp2i           object s2i data structure
   */
  void processKey(string key, string args) {
    string firstArg = null;
    if (args != null) {
      StringTokenizer st = new StringTokenizer(args);
      int cnt = st.countTokens();
      if (cnt != 0)
        firstArg = st.nextToken();
    }
    if (key.equalsIgnoreCase("IBIS Ver")) {
      globalProc = true;
      componentProc = false;
      modelProc = false;

      if (firstArg.equalsIgnoreCase("1.1"))
        ibis.ibisVersion = ConstantStuff.VERSION_ONE_ONE;
      else if (firstArg.equalsIgnoreCase("2.1"))
        ibis.ibisVersion = ConstantStuff.VERSION_TWO_ONE;
      else if (firstArg.equalsIgnoreCase("3.2"))
        ibis.ibisVersion = ConstantStuff.VERSION_THREE_TWO;
      else {
        printf("s2ibis: Please begin with s2ibis comand " +
               "file with [IBIS Ver] command");
      }
    }
    if (globalProc) {
      /***********************************************************
       *        Filling up the Global parameters
       ***********************************************************/
      //**REWRITE THIS**
      if (key.equalsIgnoreCase("File name"))
        ibis.thisFileName = newVal(firstArg);

      if (key.equalsIgnoreCase("File rev")) {
        ibis.fileRev = newVal(firstArg);
      }

      if (key.equalsIgnoreCase("Date"))
        ibis.date = newVal(args);

      if (key.equalsIgnoreCase("Source"))
        ibis.source = newVal(args);

      if (key.equalsIgnoreCase("Notes"))
        ibis.notes = new string(args);

      if (key.equalsIgnoreCase("Disclaimer"))
        ibis.disclaimer = newVal(args);

      if (key.equalsIgnoreCase("Copyright"))
        ibis.copyright = newVal(args);

      if (key.equalsIgnoreCase("Spice type")) {
        if (firstArg.toUpperCase().equals("HSPICE"))
          ibis.spiceType = ConstantStuff.SPICE_TYPE_HSPICE;
        else if (firstArg.toUpperCase().equals("PSPICE"))
          ibis.spiceType = ConstantStuff.SPICE_TYPE_PSPICE;
        else if (firstArg.toUpperCase().equals("SPICE2"))
          ibis.spiceType = ConstantStuff.SPICE_TYPE_SPICE2;
        else if (firstArg.toUpperCase().equals("SPICE3"))
          ibis.spiceType = ConstantStuff.SPICE_TYPE_SPICE3;
        else if (firstArg.toUpperCase().equals("SPECTRE"))
          ibis.spiceType = ConstantStuff.SPICE_TYPE_SPECTRE;
        else if (firstArg.toUpperCase().equals("ELDO"))
          ibis.spiceType = ConstantStuff.SPICE_TYPE_ELDO;
      }

      if (key.equalsIgnoreCase("Spice command"))
        ibis.spiceCommand = newVal(args);
      if (key.equalsIgnoreCase("Iterate"))
        ibis.iterate = 1;
      if (key.equalsIgnoreCase("Cleanup"))
        ibis.cleanup = 1;
      if (key.equalsIgnoreCase("Summarize"))
        ibis.summarize = Integer.parseInt(newVal(args));
      if (key.equalsIgnoreCase("Temperature range")) {
        if (args != null)
          global.tempRange = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Voltage range")) {
        if (args != null)
          global.voltageRange = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Pullup reference")) {
        if (args != null)
          global.pullupRef = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Pulldown reference")) {
        if (args != null)
          global.pulldownRef = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("POWER clamp reference")) {
        if (args != null)
          global.powerClampRef = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("GND clamp reference")) {
        if (args != null)
          global.gndClampRef = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("C_comp")) {
        if (args != null)
          global.c_comp = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Vil")) {
        if (args != null)
          global.vil = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Vih")) {
        if (args != null)
          global.vih = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Tr")) {
        if (args != null)
          global.tr = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Tf")) {
        if (args != null)
          global.tf = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Rload"))
        global.Rload = matchNum(firstArg);
      if (key.equalsIgnoreCase("Sim time"))
        global.simTime = matchNum(firstArg);
      if (key.equalsIgnoreCase("Clamp tolerance"))
        global.clampTol = stod(newVal(firstArg));
      if (key.equalsIgnoreCase("Derate VI"))
        global.derateVIPct = stod(newVal(firstArg));
      if (key.equalsIgnoreCase("Derate ramp"))
        global.derateRampPct = stod(newVal(firstArg));
      if (key.equalsIgnoreCase("R_pkg")) {
        if (args != null)
          global.pinParasitics.R_pkg = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("L_pkg")) {
        if (args != null)
          global.pinParasitics.L_pkg = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("C_pkg")) {
        if (args != null)
          global.pinParasitics.C_pkg = TypMinMax(args);
      }
    }

    /***********************************************************
     *        Filling up the Component and all its parameters
     ***********************************************************/

    if (key.equalsIgnoreCase("Component")) {
      compCount++;
      if (compCount == 1) {
        globalProc = false;
        componentProc = true;
        modelProc = false;
        tempComponent.component = newVal(args);
      } else {
        mList.add(tempModel);
        tempModel = new ibisModel();
        tempComponent.mList = mList;
        cList.add(tempComponent);
        tempComponent = new ibisComponent();
        pList = new pinsList();
        pmList = new pinMapList();
        mList = new modelsList();
        dpList = new diffPinList();
        spList = new seriesPinsList();
        ssgList = new seriesSwitchGpList();
        modelCount = 0;
        globalProc = false;
        componentProc = true;
        modelProc = false;
        tempComponent.component = newVal(args);
      }
    }
    if (componentProc) {
      if (!modelProc) {
        if (key.equalsIgnoreCase("Manufacturer"))
          tempComponent.manufacturer = newVal(args);

        if (key.equalsIgnoreCase("Package model"))
          tempComponent.packageModel = newVal(args);

        //**REWRITE THIS**
        if (key.equalsIgnoreCase("Spice file"))
          tempComponent.spiceFile = newVal(args);
        // series
        if (key.equalsIgnoreCase("Series spice file"))
          tempComponent.seriesSpiceFile = newVal(args);
        // series
        if (key.equalsIgnoreCase("Temperature range")) {
          if (args != null)
            tempComponent.tempRange = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("Voltage range")) {
          if (args != null)
            tempComponent.voltageRange = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("Pullup reference")) {
          if (args != null)
            tempComponent.pullupRef = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("Pulldown reference")) {
          if (args != null)
            tempComponent.pulldownRef = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("POWER clamp reference")) {
          if (args != null)
            tempComponent.powerClampRef = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("GND clamp reference")) {
          if (args != null)
            tempComponent.gndClampRef = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("C_comp")) {
          if (args != null)
            tempComponent.c_comp = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("Vil")) {
          if (args != null)
            tempComponent.vil = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("Vih")) {
          if (args != null)
            tempComponent.vih = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("Tr")) {
          if (args != null)
            tempComponent.tr = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("Tf")) {
          if (args != null)
            tempComponent.tf = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("Rload"))
          tempComponent.Rload = matchNum(firstArg);
        if (key.equalsIgnoreCase("Sim time"))
          tempComponent.simTime = matchNum(firstArg);
        if (key.equalsIgnoreCase("Clamp tolerance"))
          tempComponent.clampTol = stod(newVal(firstArg));
        if (key.equalsIgnoreCase("Derate VI"))
          tempComponent.derateVIPct = stod(newVal(firstArg));
        if (key.equalsIgnoreCase("Derate ramp"))
          tempComponent.derateRampPct = stod(newVal(firstArg));

        if (key.equalsIgnoreCase("R_pkg")) {
          if (args != null)
            tempComponent.pinParasitics.R_pkg = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("L_pkg")) {
          if (args != null)
            tempComponent.pinParasitics.L_pkg = TypMinMax(args);
        }
        if (key.equalsIgnoreCase("C_pkg")) {
          if (args != null)
            tempComponent.pinParasitics.C_pkg = TypMinMax(args);
        }
      }
      if (key.equalsIgnoreCase("Model")) {
        modelProc = true;
        modelCount++;
        if (modelCount == 1) {
          tempModel.modelName = newVal(args);
        } else {
          tempModel.risingWaveList = risingWaveList;
          tempModel.fallingWaveList = fallingWaveList;
          mList.add(tempModel);
          tempModel = new ibisModel();
          tempModel.modelName = newVal(args);
          risingWaveList = new waveTableList();
          fallingWaveList = new waveTableList();
        }
      }
      if (key.equalsIgnoreCase("Model file")) {
        if (args != null) {
          StringTokenizer st = new StringTokenizer(args);
          int cnt = st.countTokens();
          for (int i = 0; i < cnt; ++i) {
            string temp = st.nextToken();
            if (i == 0)
              tempModel.modelFileTyp = newVal(temp);
            if (i == 1)
              tempModel.modelFileMin = newVal(temp);
            if (i == 2)
              tempModel.modelFileMax = newVal(temp);
          }
        }
      }
      /*
      New for 0.4beta
      */
      if (key.equalsIgnoreCase("ExtSpiceCmd"))
        tempModel.extSpiceCmdFile = newVal(args);
      // end 0.4beta
      if (key.equalsIgnoreCase("Model type")) {
        if (firstArg.toUpperCase().equals("INPUT"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_INPUT;
        else if (firstArg.toUpperCase().equals("OUTPUT"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_OUTPUT;
        else if (firstArg.toUpperCase().equals("I/O"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_I_O;
        else if (firstArg.toUpperCase().equals("3-STATE"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_3_STATE;
        else if (firstArg.toUpperCase().equals("OPEN_DRAIN"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_OPEN_DRAIN;
        else if (firstArg.toUpperCase().equals("I/O_OPEN_DRAIN"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN;
        else if (firstArg.toUpperCase().equals("OPEN_SINK"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_OPEN_SINK;
        else if (firstArg.toUpperCase().equals("I/O_OPEN_SINK"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK;
        else if (firstArg.toUpperCase().equals("OPEN_SOURCE"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_OPEN_SOURCE;
        else if (firstArg.toUpperCase().equals("I/O_OPEN_SOURCE"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE;
        else if (firstArg.toUpperCase().equals("INPUT_ECL"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_INPUT_ECL;
        else if (firstArg.toUpperCase().equals("OUTPUT_ECL"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_OUTPUT_ECL;
        else if (firstArg.toUpperCase().equals("I/O_ECL"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_I_O_ECL;
        else if (firstArg.toUpperCase().equals("TERMINATOR"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_TERMINATOR;
        // series models
        else if (firstArg.toUpperCase().equals("SERIES"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_SERIES;
        else if (firstArg.toUpperCase().equals("SERIES_SWITCH"))
          tempModel.modelType = ConstantStuff.MODEL_TYPE_SERIES_SWITCH;
      }
      if (key.equalsIgnoreCase("Polarity")) {
        if (firstArg.equalsIgnoreCase("NON-INVERTING"))
          tempModel.polarity = ConstantStuff.MODEL_POLARITY_NON_INVERTING;
        else if (firstArg.equalsIgnoreCase("INVERTING"))
          tempModel.polarity = ConstantStuff.MODEL_POLARITY_INVERTING;
      }
      if (key.equalsIgnoreCase("Enable")) {
        if (firstArg.toUpperCase().equals("ACTIVE-HIGH"))
          tempModel.enable = ConstantStuff.MODEL_ENABLE_ACTIVE_HIGH;
        else if (firstArg.toUpperCase().equals("ACTIVE-LOW"))
          tempModel.enable = ConstantStuff.MODEL_ENABLE_ACTIVE_LOW;
      }
      if (key.equalsIgnoreCase("NoModel"))
        tempModel.noModel++;
      if (key.equalsIgnoreCase("Vinl"))
        tempModel.Vinl = matchNum(firstArg);
      if (key.equalsIgnoreCase("Vinh"))
        tempModel.Vinh = matchNum(firstArg);
      if (key.equalsIgnoreCase("Vmeas"))
        tempModel.Vmeas = matchNum(firstArg);
      if (key.equalsIgnoreCase("Cref"))
        tempModel.Cref = matchNum(firstArg);
      if (key.equalsIgnoreCase("Rref"))
        tempModel.Rref = matchNum(firstArg);
      if (key.equalsIgnoreCase("Vref"))
        tempModel.Vref = matchNum(firstArg);
      if (key.equalsIgnoreCase("Rload"))
        tempModel.Rload = matchNum(firstArg);
      if (key.equalsIgnoreCase("Sim time"))
        tempModel.simTime = matchNum(firstArg);
      if (key.equalsIgnoreCase("Clamp tolerance"))
        tempModel.clampTol = stod(newVal(firstArg));
      if (key.equalsIgnoreCase("Derate VI"))
        tempModel.derateVIPct = stod(newVal(firstArg));
      if (key.equalsIgnoreCase("Derate ramp"))
        tempModel.derateRampPct = stod(newVal(firstArg));

      if (key.equalsIgnoreCase("Temperature range")) {
        if (args != null)
          tempModel.tempRange = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Voltage range")) {
        if (args != null)
          tempModel.voltageRange = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Pullup reference")) {
        if (args != null)
          tempModel.pullupRef = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Pulldown reference")) {
        if (args != null)
          tempModel.pulldownRef = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("POWER clamp reference")) {
        if (args != null)
          tempModel.powerClampRef = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("GND clamp reference")) {
        if (args != null)
          tempModel.gndClampRef = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("C_comp")) {
        if (args != null)
          tempModel.c_comp = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Rgnd")) {
        if (args != null)
          tempModel.Rgnd = TypMinMax(args);
      }

      if (key.equalsIgnoreCase("Rpower")) {
        if (args != null)
          tempModel.Rpower = TypMinMax(args);
      }

      if (key.equalsIgnoreCase("Rac")) {
        if (args != null)
          tempModel.Rac = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Cac")) {
        if (args != null)
          tempModel.Cac = TypMinMax(args);
      }

      if (key.equalsIgnoreCase("Vil")) {
        if (args != null)
          tempModel.vil = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Vih")) {
        if (args != null)
          tempModel.vih = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Tr")) {
        if (args != null)
          tempModel.tr = TypMinMax(args);
      }
      if (key.equalsIgnoreCase("Tf")) {
        if (args != null)
          tempModel.tf = TypMinMax(args);
      }

      if (key.equalsIgnoreCase("Rising waveform")) {
        // only initialize if there is a wave
        tempWaveTable = new ibisWaveTable();
        if (args != null) {
          StringTokenizer st = new StringTokenizer(args);
          int cnt = st.countTokens();
          for (int i = 0; i < cnt; ++i) {
            string temp = st.nextToken();
            if (i == 0)
              tempWaveTable.R_fixture = matchNum(temp);
            if (i == 1)
              tempWaveTable.V_fixture = matchNum(temp);
            if (i == 2)
              tempWaveTable.V_fixture_min = matchNum(temp);
            if (i == 3)
              tempWaveTable.V_fixture_max = matchNum(temp);
            if (i == 4)
              tempWaveTable.L_fixture = matchNum(temp);
            if (i == 5)
              tempWaveTable.C_fixture = matchNum(temp);
            if (i == 6)
              tempWaveTable.R_dut = matchNum(temp);
            if (i == 7)
              tempWaveTable.L_dut = matchNum(temp);
            if (i == 8)
              tempWaveTable.C_dut = matchNum(temp);
          }
        }
        risingWaveList.add(tempWaveTable);
      }

      if (key.equalsIgnoreCase("Falling waveform")) {
        tempWaveTable = new ibisWaveTable();
        if (args != null) {
          StringTokenizer st = new StringTokenizer(args);
          int cnt = st.countTokens();
          for (int i = 0; i < cnt; ++i) {
            string temp = st.nextToken();
            if (i == 0)
              tempWaveTable.R_fixture = matchNum(temp);
            if (i == 1)
              tempWaveTable.V_fixture = matchNum(temp);
            if (i == 2)
              tempWaveTable.V_fixture_min = matchNum(temp);
            if (i == 3)
              tempWaveTable.V_fixture_max = matchNum(temp);
            if (i == 4)
              tempWaveTable.L_fixture = matchNum(temp);
            if (i == 5)
              tempWaveTable.C_fixture = matchNum(temp);
            if (i == 6)
              tempWaveTable.R_dut = matchNum(temp);
            if (i == 7)
              tempWaveTable.L_dut = matchNum(temp);
            if (i == 8)
              tempWaveTable.C_dut = matchNum(temp);
          }
        }
        fallingWaveList.add(tempWaveTable);
      }

      if (key.equalsIgnoreCase("On")) {
        tempModel.seriesModel.OnState = true;
      }
      //	  if( key.equalsIgnoreCase( "series MOSFET" ) )
      if (key.equalsIgnoreCase("series_mosfet")) {
        tempVdsList = new VdsList();
        //	    tempModel.seriesModel.series_MOSFET
      }
      if (key.equalsIgnoreCase("Vds")) {
        if (args != null) {
          tempVds.V = matchNum(args);
          tempVdsList.add(tempVds);
          tempVds = new Vds();
        }
      }
      if (key.equalsIgnoreCase("Off")) {
        tempModel.seriesModel.OffState = true;
        tempModel.seriesModel.RSeriesOff.typ = ConstantStuff.R_SERIES_DEFAULT;
        tempModel.seriesModel.RSeriesOff.min = ConstantStuff.R_SERIES_DEFAULT;
        tempModel.seriesModel.RSeriesOff.max = ConstantStuff.R_SERIES_DEFAULT;
        tempModel.seriesModel.series_MOSFET.vdslist = tempVdsList;
      }
      if (key.equalsIgnoreCase("R series")) {
        if (args != null)
          tempModel.seriesModel.RSeriesOff = TypMinMax(args);
      }

    } // (componentProc = true)
    tempComponent.pList = pList;
    tempComponent.pmList = pmList;
    tempComponent.dpList = dpList;
    tempComponent.spList = spList;
    tempComponent.ssgList = ssgList;
  } // processKey

  ibisTypMinMax TypMinMax(string args) {
    StringTokenizer st = new StringTokenizer(args);
    int cnt = st.countTokens();
    ibisTypMinMax typMinMax = new ibisTypMinMax();
    for (int i = 0; i < cnt; ++i) {
      string temp = st.nextToken();
      if (i == 0)
        typMinMax.typ = matchNum(temp);
      if (i == 1)
        typMinMax.min = matchNum(temp);
      if (i == 2)
        typMinMax.max = matchNum(temp);
    }
    return typMinMax;
  }

  static double matchNum(string in) {
    double finalResult1 = 0;
    string dec = new string(
        "[-+]?([0-9]+\\.?[0-9]*|\\.[0-9]+)([eE][-+]?[0-9]*|[TGMkKmunpfa]?)?");
    string inText = "\\s*(" + dec + ")[-+]?[0-9]*[a-zA-Z]*\\s*";
    Pattern pattern;
    Matcher matcher;
    pattern = Pattern.compile(inText);
    matcher = pattern.matcher(in);
    if (matcher.matches()) {
      string result = matcher.group(1);
      int resultLength = result.length();
      char scalingFactor = result.charAt(resultLength - 1);
      string factor = new string("");

      if (Character.isDigit(scalingFactor))
        finalResult1 = stod(result);
      else {
        Character scaleChar = new Character(scalingFactor);
        factor = scaleChar.toString();
        finalResult1 = stripFactor(result, factor);
      }
    } else if (in.equalsIgnoreCase("NA")) {
      finalResult1 = ConstantStuff.USE_NA;
    }

    return finalResult1;
  }

  static double stripFactor(string aResult, string aFactor) {
    double finalResult = 0;
    if (aResult.trim().endsWith(aFactor)) {
      StringTokenizer st = new StringTokenizer(aResult, aFactor);
      string firstToken = st.nextToken();
      finalResult = stod(firstToken);
      if (aFactor.equals("n"))
        finalResult = finalResult * 1.e-9;
      else if (aFactor.equals("p"))
        finalResult = finalResult * 1.e-12;
      else if (aFactor.equals("m"))
        finalResult = finalResult * 1.e-3;
      else if (aFactor.equals("u"))
        finalResult = finalResult * 1.e-6;
      else if (aFactor.equals("f"))
        finalResult = finalResult * 1.e-15;
      else if (aFactor.equals("T"))
        finalResult = finalResult * 1.e12;
      else if (aFactor.equals("k"))
        finalResult = finalResult * 1.e3;
      else if (aFactor.equals("G"))
        finalResult = finalResult * 1.e9;
      else if (aFactor.equals("M"))
        finalResult = finalResult * 1.e6;
      return finalResult;
    } else
      return 0;
  }

public:
  static void main(string args[]) {
    s2iParser Rdr = new s2iParser();
    Rdr.Sp2iParse(args[0]);
  }
}
