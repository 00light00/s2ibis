#ifndef _IBISWAVETABLE
#define _IBISWAVETABLE


#include "ibisWaveTableEntry.h"

class ibisWaveTable
{
  double R_fixture = -1.33287736222333E20D;
  double V_fixture = -1.33287736222333E20D;
  double V_fixture_min = -1.33287736222333E20D;
  double V_fixture_max = -1.33287736222333E20D;
  double L_fixture = -1.33287736222333E20D;
  double C_fixture = -1.33287736222333E20D;
  double R_dut = -1.33287736222333E20D;
  double L_dut = -1.33287736222333E20D;
  double C_dut = -1.33287736222333E20D;
  int size;
  ibisWaveTableEntry[] waveData;
  ibisWaveTable nextWaveTable;

  public void setnext(ibisWaveTable nextWaveTable1) {
    this.nextWaveTable = nextWaveTable1;
  }


  public ibisWaveTable getnext() {
    return this.nextWaveTable;
  }
};


#endif
