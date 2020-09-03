#ifndef S2IFILE_H
#define S2IFILE_H

#include <bits/stdc++.h>
using namespace std;

#include "constantstuff.h"
#include "ibistypminmax.h"

/**--------------------------------------------------------------------
 *   ibis information in s2ifile
 *--------------------------------------------------------------------*/

/******************************************************************************
CLASS: ibisTOP
******************************************************************************/

struct ibisTOP {
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
struct ibisGlobal {
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

class s2ifile {
public:
  string inFile;
  ibisTOP ibisStruct;
  ibisGlobal ibisGlobal;
  ibisTypMinMax typMinMax;
  unordered_map<string, vector<string>> keyTree;
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

  //  int compCount = 0;
  //  int modelCount = 0;
  //  bool modelProc = false;
  //  bool componentProc = false;
  //  bool globalProc = false;
  //  // reorg
  //  Vds tempVds;
  //  VdsList tempVdsList;
  //  ;
  //  // reorg

  s2ifile(string &infile);
  void s2iParse();
  void getKey(string &line, string &key);
};

struct s2iParser {
  ibisTOP ibis;
  ibisGlobal global;
};

#endif // S2IFILE_H
