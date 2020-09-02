#ifndef _GETSPICEWAVEDATA
#define _GETSPICEWAVEDATA

#include <string>
using String = std::string;

#include "ibisWaveTable.h"
#include <iostream>
#include "spiceVT.h"
#include "binParams.h"

class getSpiceWaveData
{
public:
  ibisWaveTable wave_p;

  getSpiceWaveData(double simTime, int spiceType, String spiceOutFile, String command) {
    File outFile_p = new File(spiceOutFile);

    double t = 0.0D;
    double v = 0.0D;
    double binTime = 0.0D;
    double vLastBin = 0.0D;
    double tLastBin = 0.0D;
    double vInterp = 0.0D;
    double tInterp = 0.0D;
    double vInterpBin = 0.0D;
    double tInterpBin = 0.0D;
    int numRead = 0;
    int i = 0;
    int row = 0;
    int key1 = 0;
    boolean flag = false;
    boolean flag_eldo = true;
    double temp_double = 0.0D;
    spiceVT V = new spiceVT();
    binParams binParam1 = new binParams();
    LinkedHashMap<Object, Object> waveData = new LinkedHashMap<>();

    binTime = simTime / 99.0D;
    if (!outFile_p.canRead()) {

      printf("Unable to open " + spiceOutFile + " for reading");
      return 1;
    }
    try {
      BufferedReader SpiceReader = new BufferedReader(new FileReader(outFile_p));

      String lineBuffer;
      do {

      } while ((lineBuffer = SpiceReader.readLine()) != null &&
        lineBuffer.indexOf(s2iString.tranDataBeginMarker[spiceType]) < 0);
      if (lineBuffer.indexOf(s2iString.tranDataBeginMarker[spiceType]) < 0) {

        printf("Data begin marker " + s2iString.tranDataBeginMarker[spiceType]);
        printf("not found in output file " + spiceOutFile);
        SpiceReader.close();
        return 1;
      }

      if (spiceType == 5) { do {

        } while ((lineBuffer = SpiceReader.readLine()) != null &&
          !lineBuffer.startsWith(s2iString.VIDataBeginMarker[spiceType]));

        if (!lineBuffer.startsWith(s2iString.VIDataBeginMarker[spiceType])) {

          printf("Data begin marker '" +
              s2iString.VIDataBeginMarker[spiceType] + "'");
          printf("not found in output file " + spiceOutFile);
          SpiceReader.close();
          return 1;
        }  }











      while ((lineBuffer = SpiceReader.readLine()) != null && flag_eldo) {
        if (lineBuffer != null) {

          StringTokenizer st = new StringTokenizer(lineBuffer);
          int cnt = st.countTokens();
          if (cnt != 0) {

            String temp = st.nextToken();
            try {
              temp_double = Double.parseDouble(temp);
              flag = true;
              row++;
            }
            catch (Exception ex1) {
              if (ex1.toString().length() != 0)
              {

                flag = false; }
              if (spiceType == 5)
                flag_eldo = false;
            }
          }
          if (cnt == 2 && flag) {




            V.t = temp_double;
            V.v = Double.parseDouble(st.nextToken());
            waveData.put(new Integer(row), V);
            V = new spiceVT();
          }
          if (cnt == 3 && flag) {




            V.t = Double.parseDouble(st.nextToken());
            V.v = Double.parseDouble(st.nextToken());
            waveData.put(new Integer(row), V);
            V = new spiceVT();
          }
        }
      }
      spiceVT[] waveArray = new spiceVT[waveData.size()];
      Iterator key = waveData.keySet().iterator();
      Iterator<spiceVT> value = waveData.values().iterator();
      while (key.hasNext()) {

        key.next();
        spiceVT V1 = value.next();
        waveArray[key1] = V1;
        V1 = new spiceVT();
        key1++;
      }





      binParam1.numPointsInBin = 0;
      binParam1.runningSum = v;
      binParam1.lastBin = goodies.ROUND(t / binTime);







      binTranData binTranData1 = new binTranData();

      for (int k = 0; k < key1; k++)
      {
        binTranData1.binTranData((waveArray[k]).t, (waveArray[k]).v, simTime,
            binTime, command, binParam1, this.wave_p);
      }





      vLastBin = binParam1.runningSum / binParam1.numPointsInBin;
      tLastBin = simTime;

      if (command.equalsIgnoreCase("typ")) {

        (this.wave_p.waveData[binParam1.lastBin]).t = tLastBin;
        (this.wave_p.waveData[binParam1.lastBin]).v.typ = vLastBin;
      }
      else if (command.equalsIgnoreCase("min")) {
        (this.wave_p.waveData[binParam1.lastBin]).v.min = vLastBin;
      } else {
        (this.wave_p.waveData[binParam1.lastBin]).v.max = vLastBin;
      }
      if (binParam1.lastBin != binParam1.interpBin) {

        tInterpBin = (this.wave_p.waveData[binParam1.interpBin]).t;
        if (command.equalsIgnoreCase("typ")) {
          vInterpBin = (this.wave_p.waveData[binParam1.interpBin]).v.typ;
        } else if (command.equalsIgnoreCase("min")) {
          vInterpBin = (this.wave_p.waveData[binParam1.interpBin]).v.min;
        } else {
          vInterpBin = (this.wave_p.waveData[binParam1.interpBin]).v.max;
        }  for (i = binParam1.interpBin + 1; i < binParam1.lastBin; i++) {

          tInterp = i * binTime;
          vInterp = vInterpBin + (tInterp - tInterpBin) * (
            v - vInterpBin) / (t - tInterpBin);
          if (command.equalsIgnoreCase("typ")) {

            (this.wave_p.waveData[i]).t = tInterp;
            (this.wave_p.waveData[i]).v.typ = vInterp;
          }
          else if (command.equalsIgnoreCase("min")) {
            (this.wave_p.waveData[i]).v.min = vInterp;
          } else {
            (this.wave_p.waveData[i]).v.max = vInterp;
          }
        }
      }
      SpiceReader.close();

    }
    catch (Exception ex) {
      printf("Exception while collecting spice data from out files (getSpiceWaveData): " +
          ex.toString());
    }
    return 0;
  }
};


#endif
