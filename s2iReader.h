#ifndef _S2IREADER
#define _S2IREADER

#include <string>




class s2iReader
{
public:
  string inFile;
  ibisTOP ibisStruct;
  ibisGlobal ibisGlobal;

};
#endif

#include "s2iParser.h"
int main(int argv, char* args[]) {
    s2iParser parser = new s2iParser();
    parser.Sp2iParse(inFile);
    parser.ibis.cList = parser.cList;
    ibisStruct = parser.ibis;
    ibisGlobal = parser.global;
    return 0;
}
