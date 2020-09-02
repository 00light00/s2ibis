#ifndef _IBISPIN
#define _IBISPIN

#include <string>
using String = std::string;
#include "ibisModel.h"

class ibisPin
{
  float NA_float = 0.0F;

  String spiceNodeName;

  String pinName;

  String signalName;

  String modelName;

  String inputPin;

  String enablePin;

  String pullupRef;

  String pulldownRef;

  String powerClampRef;
  String gndClampRef;
  double R_pin;
  double L_pin;
  double C_pin;
  ibisModel model;
  ibisModel seriesModel;
  String seriesPin2name;
  String fnTableGp;
  ibisPin nextPin;

  public ibisPin() {
    this.spiceNodeName = null;
    this.pinName = null;
    this.modelName = null;
    this.signalName = null;
    this.enablePin = "";
    this.inputPin = "";
    this.pullupRef = null;
    this.pulldownRef = null;
    this.powerClampRef = null;
    this.gndClampRef = null;
    this.seriesPin2name = null;
    this.seriesModel = null;
    this.R_pin = -1.33287736222333005E18D;
    this.C_pin = -1.33287736222333005E18D;
    this.L_pin = -1.33287736222333005E18D;
  }


  public void setnext(ibisPin nextPin1) {
    this.nextPin = nextPin1;
  }


  public ibisPin getnext() {
    return this.nextPin;
  }
};

#endif
