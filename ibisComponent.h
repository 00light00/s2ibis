#ifndef _IBISCOMPONENT
#define _IBISCOMPONENT

#include <string>
#define String std::string

#include "ibisTypMinMax.h"
#include "modelsList.h"
#include "pinsList.h"
#include "pinMapList.h"
#include "ibisPackage.h"
#include "diffPinList.h"
#include "seriesPinsList.h"
#include "seriesSwitchGpList.h"

class ibisComponent
{
public:
  int thisComponentProcessed;
  bool hasPinMapping;
  String component;
  String packageModel;
  String manufacturer;
  String spiceFile;
  String seriesSpiceFile;
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
  ibisTypMinMax vil;
  ibisTypMinMax vih;
  ibisTypMinMax tr;
  ibisTypMinMax tf;
  modelsList mList;
  pinsList pList;
  pinMapList pmList;

  ibisPackage pinParasitics;
  diffPinList dpList;
  seriesPinsList spList;
  seriesSwitchGpList ssgList;


  ibisComponent next;


  ibisComponent() {
    this->thisComponentProcessed = 0;
    this->hasPinMapping = false;
    this->component = nullptr;
    this->packageModel = nullptr;
    this->manufacturer = nullptr;
    this->spiceFile = nullptr;
    this->Rload = -1.33287736222333E20;
    this->derateRampPct = -1.33287736222333E20;
    this->derateVIPct = -1.33287736222333E20;
    this->clampTol = -1.33287736222333E20;
    this->simTime = -1.33287736222333E20;
    this->dpList = nullptr;
    this->spList = nullptr;
  }

  void setnext(ibisComponent nextmod) {
    this->next = nextmod;
  }


  ibisComponent getnext() {
    return this->next;
  }
};


#endif
