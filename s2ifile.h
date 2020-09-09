#ifndef S2IFILE_H
#define S2IFILE_H

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

#include "ConstantStuff.h"
#include "ibisTypMinMax.h"

/**--------------------------------------------------------------------
 *   ibis information in s2ifile
 *--------------------------------------------------------------------*/

/******************************************************************************
CLASS: ibisTOP
******************************************************************************/

class ibisTOP {
public:
  int ibisVersion, iterate, cleanup, summarize, spiceType;
  string thisFileName, fileRev, date, source, notes, disclaimer, copyright,
      spiceCommand;
  //  componentList   cList	= new componentList();
  ibisTOP() {
    ibisVersion = 0;
    iterate = 0;
    cleanup = 0;
    summarize = 0;
    spiceType = 0;
    thisFileName = ""; // null;
    fileRev = "";      // null;
    date = "";         // null;
    source = "";       // null;
    notes = "";        // null;
    disclaimer = "";   // null;
    copyright = "";    // null;
    spiceCommand = "";
    // components	= null;
  }
};

/******************************************************************************
CLASS: ibisGlobal
******************************************************************************/

class ibisGlobal {
public:
  string commentChar;
  ibisTypMinMax tempRange;
  ibisTypMinMax voltageRange;
  ibisTypMinMax pullupRef;
  ibisTypMinMax pulldownRef;
  ibisTypMinMax powerClampRef;
  ibisTypMinMax gndClampRef;
  ibisTypMinMax c_comp;
  ibisTypMinMax vil;
  ibisTypMinMax vih;
  ibisTypMinMax tr;
  ibisTypMinMax tf;
  double Rload, derateVIPct, derateRampPct, clampTol, simTime;
  //  ibisPackage pinParasitics = new ibisPackage();

  ibisGlobal() {
    commentChar = "";
    Rload = ConstantStuff::USE_NA; // 0;
    derateVIPct = 0;
    derateRampPct = 0;
    clampTol = 0;
    simTime = ConstantStuff::USE_NA; // 0;
  }
};

/******************************************************************************
CLASS: ibisVItable
******************************************************************************/

class ibisVItable {
public:
  vector<pair<double, ibisTypMinMax>> VIs;
};

/******************************************************************************
CLASS: ibisWaveTable
******************************************************************************/

class ibisWaveTable {
public:
  double R_fixture, V_fixture, V_fixture_min, V_fixture_max, L_fixture,
      C_fixture, R_dut, L_dut, C_dut;
  vector<pair<double, ibisTypMinMax>> waveData;

  // constructor for ibisWavetable class
  ibisWaveTable();

}; // class ibisWaveTable

/******************************************************************************
CLASS: ibisPackage
******************************************************************************/

struct ibisPackage {
  ibisTypMinMax R_pkg;
  ibisTypMinMax L_pkg;
  ibisTypMinMax C_pkg;
}; // class ibisPackage

/******************************************************************************
CLASS: ibisRamp
******************************************************************************/

struct ibisRamp {
  ibisTypMinMax dv_r;
  ibisTypMinMax dt_r;
  ibisTypMinMax dv_f;
  ibisTypMinMax dt_f;
};

/******************************************************************************
CLASS: ibisModel
******************************************************************************/

class ibisModel {
public:
  int thisModelProcessed;
  int hasBeenAnalyzed;
  int polarity;
  int modelType;
  int noModel;
  string modelFileTyp; // declared as TypMinMax class
  string modelFileMin;
  string modelFileMax;
  string extSpiceCmdFile; // for 0.4beta
  string modelName;
  int enable;
  double Vinl;
  double Vinh;
  double Vmeas;
  double Cref;
  double Rref;
  double Vref;
  double Rload;
  double derateRampPct;
  double derateVIPct;
  double clampTol;
  double simTime;

  ibisTypMinMax c_comp;
  ibisTypMinMax tempRange;
  ibisTypMinMax voltageRange;
  ibisTypMinMax pullupRef;
  ibisTypMinMax pulldownRef;
  ibisTypMinMax powerClampRef;
  ibisTypMinMax gndClampRef;
  ibisTypMinMax Rgnd;
  ibisTypMinMax Rpower;
  ibisTypMinMax Rac;
  ibisTypMinMax Cac;
  ibisTypMinMax vil;
  ibisTypMinMax vih;
  ibisTypMinMax tr;
  ibisTypMinMax tf;
  ibisVItable pulldown;
  ibisVItable pullup;
  ibisVItable gnd_clamp;
  ibisVItable power_clamp;
  vector<ibisWaveTable> risingWaveList;
  vector<ibisWaveTable> fallingWaveList;
  ibisRamp ramp;
  // Series
  //  ibisSeriesModel seriesModel;
  // Series

  // constructor for ibisModel class
  ibisModel(); // constructor for ibisModel class

}; // class ibisModel

class s2ifile {
public:
  unordered_map<string, vector<string>> keyAndData;
  unordered_map<string, int> keyNameToInt;
  string inFile;
  ibisTOP ibisStruct;
  ibisGlobal ibisGlobal;
  ibisTypMinMax typMinMax;
  // Linked List declarations
  //  pinMapList pmList;
  //  ibisPinMap tempPinMap;
  //  pinsList pList;
  //  ibisPin tempPin;

  //  waveTableList risingWaveList;
  //  waveTableList fallingWaveList;
  //  ibisWaveTable tempWaveTable;

  //  diffPinList dpList;
  //  ;
  //  ibisDiffPin tempDiffPin;

  //  seriesPinsList spList;
  //  ;
  //  ibisSeriesPin tempSeriesPin;

  //  seriesSwitchGpList ssgList;
  //  ;
  //  seriesSwitchGroup tempSeriesSwitchGp;

  //  modelsList mList;
  //  ibisModel tempModel;

  //  componentList cList;
  //  ibisComponent tempComponent;

  int compCount = 0;
  int modelCount = 0;
  bool modelProc = false;
  bool componentProc = false;
  bool globalProc = false;
  //  // reorg
  //  Vds tempVds;
  //  VdsList tempVdsList;
  //  ;
  //  // reorg

  s2ifile(string &infile);
  void s2iParse();
  void getKey(string &line, string &key);
  void processKey(string &key, string &line);
  void completeHeader(string &key, string &line);
  void completeComponent(string &key, string &line);
  void completeModel(string &key, string &line);
  string newVal(string &args);
  ibisTypMinMax TypMinMax(const string &args);
  double matchNum(const string &in);
  double stripFactor(double Result, char Factor);
};

#endif // S2IFILE_H
