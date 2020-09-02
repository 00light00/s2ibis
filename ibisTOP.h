#ifndef _IBISTOP
#define _IBISTOP

#include <string>
#define String std::string

#include "componentList.h"

class ibisTOP
{
public:
  int ibisVersion;
  int iterate;
  int cleanup;
  int summarize;
  int spiceType;
  String thisFileName;
  String fileRev;
  String date;
  String source;
  String notes;
  String disclaimer;
  String copyright;
  String spiceCommand;
  componentList cList;


  ibisTOP() {
    this->ibisVersion = 0;
    this->iterate = 0;
    this->cleanup = 0;
    this->summarize = 0;
    this->spiceType = 0;
    this->thisFileName = "";
    this->fileRev = "";

    this->source = "";
    this->notes = "";
    this->disclaimer = "";
    this->copyright = "";
    this->spiceCommand = "";
  }
};
#endif
