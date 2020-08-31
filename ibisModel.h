#ifndef _IBISMODEL
#define _IBISMODEL

#include <string>
#define String std::string

#include "ibisTypMinMax.h"
#include "ibisVItable.h"
#include "waveTableList.h"
#include "ibisRamp.h"
#include "ibisSeriesModel.h"

class ibisModel
{
public:
  int thisModelProcessed;
  int hasBeenAnalyzed;
  int polarity;
  int modelType;
  int noModel;
  String modelFileTyp;
  String modelFileMin;
  String modelFileMax;
  String extSpiceCmdFile;
  String modelName;
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
  ibisVItable pulldown = new ibisVItable();
  ibisVItable pullup = new ibisVItable();
  ibisVItable gnd_clamp = new ibisVItable();
  ibisVItable power_clamp = new ibisVItable();
  waveTableList risingWaveList = new waveTableList();
  waveTableList fallingWaveList = new waveTableList();
  ibisRamp ramp = new ibisRamp();

  ibisSeriesModel seriesModel = new ibisSeriesModel();


  ibisModel next;


  ibisModel() {
    this.thisModelProcessed = 0;
    this.hasBeenAnalyzed = 0;
    this.noModel = 0;
    this.polarity = 0;
    this.modelName = null;
    this.modelFileTyp = "";
    this.modelFileMin = "";
    this.modelFileMax = "";
    this.extSpiceCmdFile = "";
    this.modelType = 0;
    this.enable = 0;
    this.Vinl = -1.33287736222333E20;
    this.Vinh = -1.33287736222333E20;
    this.Vmeas = -1.33287736222333E20;
    this.Cref = -1.33287736222333E20;
    this.Rref = -1.33287736222333E20;
    this.Vref = -1.33287736222333E20;
    this.Rload = -1.33287736222333E20;
    this.derateRampPct = -1.33287736222333E20;
    this.derateVIPct = -1.33287736222333E20;
    this.clampTol = -1.33287736222333E20;
    this.simTime = -1.33287736222333E20;
    this.gnd_clamp = null;
    this.power_clamp = null;
    this.pullup = null;
    this.pulldown = null;
  }


  void setnext(ibisModel nextmod) {
    this.next = nextmod;
  }


  ibisModel getnext() {
    return this.next;
  }
};

