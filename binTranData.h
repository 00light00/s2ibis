#ifndef _BINTRANDATA
#define _BINTRANDATA
#include "goodies.h"

void binTranData(double t, double v, double simTime, double binTime, String command, binParams binParam1, ibisWaveTable wave_p) {
    int currentBin = 0;
    int i = 0;
    double vLastBin = 0.0D;
    double tLastBin = 0.0D;
    double vInterp = 0.0D;
    double tInterp = 0.0D;
    double vInterpBin = 0.0D;
    double tInterpBin = 0.0D;
    currentBin = goodies.ROUND(t / binTime);
    if (currentBin == binParam1.lastBin) {
      binParam1.runningSum += v;
      binParam1.numPointsInBin++;
    }
    else {
      vLastBin = binParam1.runningSum / binParam1.numPointsInBin;
      tLastBin = binParam1.lastBin * binTime;
      if (command.equalsIgnoreCase("typ")) {

        (wave_p.waveData[binParam1.lastBin]).t = tLastBin;
        (wave_p.waveData[binParam1.lastBin]).v.typ = vLastBin;
      }
      else if (command.equalsIgnoreCase("min")) {
        (wave_p.waveData[binParam1.lastBin]).v.min = vLastBin;
      } else {
        (wave_p.waveData[binParam1.lastBin]).v.max = vLastBin;
      }
      if (binParam1.lastBin != binParam1.interpBin) {

        tInterpBin = (wave_p.waveData[binParam1.interpBin]).t;
        if (command.equalsIgnoreCase("typ")) {
          vInterpBin = (wave_p.waveData[binParam1.interpBin]).v.typ;
        } else if (command.equalsIgnoreCase("min")) {
          vInterpBin = (wave_p.waveData[binParam1.interpBin]).v.min;
        } else {
          vInterpBin = (wave_p.waveData[binParam1.interpBin]).v.max;
        }  for (i = binParam1.interpBin + 1; i < binParam1.lastBin; i++) {

          tInterp = i * binTime;
          vInterp = vInterpBin + (tInterp - tInterpBin) * (
            v - vInterpBin) / (t - tInterpBin);

          if (command.equalsIgnoreCase("typ")) {

            (wave_p.waveData[i]).t = tLastBin;
            (wave_p.waveData[i]).v.typ = vLastBin;
          }
          else if (command.equalsIgnoreCase("min")) {
            (wave_p.waveData[i]).v.min = vLastBin;
          } else {
            (wave_p.waveData[i]).v.max = vLastBin;
          }
        }
      }
      if (currentBin > binParam1.lastBin + 1) {
        binParam1.interpBin = binParam1.lastBin;
      } else {
        binParam1.interpBin = currentBin;
      }
      binParam1.lastBin = currentBin;
      binParam1.runningSum = v;
      binParam1.numPointsInBin = 1;
    }
  }
};
#endif
