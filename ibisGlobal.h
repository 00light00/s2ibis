#ifndef _IBISGLOBAL
#define _IBISGLOBAL

#include <string>
#define String std::string

#include "ibisTypMinMax.h"
#include "ibisPackage.h"

class ibisGlobal
{
public:
  String commentChar;
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
  double Rload;
  double derateVIPct;
  double derateRampPct;
  double clampTol;
  double simTime;
  ibisPackage pinParasitics;


  ibisGlobal() {
    this->commentChar = "";
    this->Rload = -1.33287736222333E20;
    this->derateVIPct = 0.0;
    this->derateRampPct = 0.0;
    this->clampTol = 0.0;
    this->simTime = -1.33287736222333E20;
  }
}

#endif
