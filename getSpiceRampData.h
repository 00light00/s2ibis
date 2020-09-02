#ifndef _GETSPICERAMPDATA
#define _GETSPICERAMPDATA

#include "ibisModel.h"
#include <iostream>
#include <stdio.h>
#include "spiceVT.h"


class getSpiceRampData
{
public:
    getSpiceRampData(ibisModel model, int curveType, int spiceType, String spiceOutFile, String command) {
    File outFile_p = new File(spiceOutFile);

    double t0 = 0.0D;
    double t1 = 0.0D;
    double t20 = 0.0D;
    double t80 = 0.0D;
    double v0 = 0.0D;
    double v1 = 0.0D;
    double v20 = 0.0D;
    double v80 = 0.0D;
    int row = 0;
    int key1 = 0;
    bool flag = false;
    bool flag_eldo = true;
    double temp_double = 0.0D;
    spiceVT V = new spiceVT();
    LinkedHashMap<Object, Object> rampData = new LinkedHashMap<>();


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

        printf("Data begin marker '" +
            s2iString.tranDataBeginMarker[spiceType] + "'");
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

          StringTokenizer st3 = new StringTokenizer(lineBuffer);
          int cnt = st3.countTokens();
          if (cnt != 0) {

            String temp = st3.nextToken();
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
            V.v = Double.parseDouble(st3.nextToken());
            rampData.put(new Integer(row), V);
            V = new spiceVT();
          }
          if (cnt == 3 && flag) {




            V.t = Double.parseDouble(st3.nextToken());
            V.v = Double.parseDouble(st3.nextToken());
            rampData.put(new Integer(row), V);
            V = new spiceVT();
          }
        }
      }
      spiceVT[] rampArray = new spiceVT[rampData.size()];
      Iterator key = rampData.keySet().iterator(); Iterator<spiceVT> value = rampData.values().iterator();
      while (key.hasNext()) {

        key.next();
        spiceVT V1 = value.next();
        rampArray[key1] = V1;
        V1 = new spiceVT();
        key1++;
      }
      v0 = (rampArray[0]).v;
      t0 = (rampArray[0]).t;
      v1 = (rampArray[rampData.size() - 1]).v;
      t1 = (rampArray[rampData.size() - 1]).t;

      v20 = v0 + 0.2D * (v1 - v0);
      v80 = v0 + 0.8D * (v1 - v0);
      double v_int = 0.0D, t_int = 0.0D;
      bool t20_done = false;
      bool t80_done = false;
      if (v1 < v0) {
        for (int k = 0; k < key1; k++) {

          if (!t20_done)
            if ((rampArray[k]).v > v20) {

              v_int = (rampArray[k]).v;
              t_int = (rampArray[k]).t;
            }
            else {

              t20 = t_int + (v20 - v_int) * ((rampArray[k]).t - t_int) / ((rampArray[k]).v - v_int);
              t20_done = true;
            }
          if (!t80_done)
            if ((rampArray[k]).v > v80) {

              v_int = (rampArray[k]).v;
              t_int = (rampArray[k]).t;
            }
            else {

              t80 = t_int + (v80 - v_int) * ((rampArray[k]).t - t_int) / ((rampArray[k]).v - v_int);
              t80_done = true;
            }
        }
      } else {
        for (int k = 0; k < key1; k++) {

          if (!t20_done)
            if ((rampArray[k]).v < v20) {

              v_int = (rampArray[k]).v;
              t_int = (rampArray[k]).t;
            }
            else {

              t20 = t_int + (v20 - v_int) * ((rampArray[k]).t - t_int) / ((rampArray[k]).v - v_int);
              t20_done = true;
            }
          if (!t80_done) {
            if ((rampArray[k]).v < v80) {

              v_int = (rampArray[k]).v;
              t_int = (rampArray[k]).t;
            }
            else {

              t80 = t_int + (v80 - v_int) * ((rampArray[k]).t - t_int) / ((rampArray[k]).v - v_int);
              t80_done = true;
            }
          }
        }
      }



      if (curveType == 6) {

        if (command.equalsIgnoreCase("typ"))
        {
          model.ramp.dv_r.typ = v80 - v20;
          model.ramp.dt_r.typ = t80 - t20;
        }
        else if (command.equalsIgnoreCase("min"))
        {
          model.ramp.dv_r.min = v80 - v20;
          model.ramp.dt_r.min = t80 - t20;
          model.ramp.dt_r.min -= model.ramp.dt_r.min * model.derateRampPct / 100.0D;
        }
        else
        {
          model.ramp.dv_r.max = v80 - v20;
          model.ramp.dt_r.max = t80 - t20;
          model.ramp.dt_r.max += model.ramp.dt_r.max * model.derateRampPct / 100.0D;

        }

      }
      else if (command.equalsIgnoreCase("typ")) {

        model.ramp.dv_f.typ = v20 - v80;
        model.ramp.dt_f.typ = t80 - t20;
      }
      else if (command.equalsIgnoreCase("min")) {

        model.ramp.dv_f.min = v20 - v80;
        model.ramp.dt_f.min = t80 - t20;
        model.ramp.dt_f.min -= model.ramp.dt_r.min * model.derateRampPct / 100.0D;
      }
      else {

        model.ramp.dv_f.max = v20 - v80;
        model.ramp.dt_f.max = t80 - t20;
        model.ramp.dt_f.max += model.ramp.dt_r.max * model.derateRampPct / 100.0D;
      }

      SpiceReader.close();
    }
    catch (Exception ex) {
      printf("Exception while collecting spice data from out files (getSpiceRampData): " +
          ex.toString());
      ex.printStackTrace();
    }
    return 0;
  }
};


#endif
