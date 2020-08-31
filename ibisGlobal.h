#ifndef _IBISGLOBAL
#define _IBISGLOBAL

#include <string>
#define String std::string

#include "ibisTypMinMax.h"

class ibisGlobal
{
public:
  String commentChar;
  ibisTypMinMax tempRange = new ibisTypMinMax();
  ibisTypMinMax voltageRange = new ibisTypMinMax();
  ibisTypMinMax pullupRef = new ibisTypMinMax();
  ibisTypMinMax pulldownRef = new ibisTypMinMax();
  ibisTypMinMax powerClampRef = new ibisTypMinMax();
  ibisTypMinMax gndClampRef = new ibisTypMinMax();
  ibisTypMinMax c_comp = new ibisTypMinMax();
  ibisTypMinMax vil = new ibisTypMinMax();
  ibisTypMinMax vih = new ibisTypMinMax();
  ibisTypMinMax tr = new ibisTypMinMax();
  ibisTypMinMax tf = new ibisTypMinMax();
  double Rload;
  double derateVIPct;
  double derateRampPct;
  double clampTol;
  double simTime;
  ibisPackage pinParasitics = new ibisPackage();


  ibisGlobal() {
    this.commentChar = null;
    this.Rload = -1.33287736222333E20D;
    this.derateVIPct = 0.0D;
    this.derateRampPct = 0.0D;
    this.clampTol = 0.0D;
    this.simTime = -1.33287736222333E20D;
  }
}

#endif
