#ifndef _GETSPICEVIDATA
#define _GETSPICEVIDATA

#include <string>
using String = std::string;

#include "VIDataContainer.h"

class getSpiceVIData
{
public:
  int getSpiceVIData(VIDataContainer VIC, int tableSize, int spiceType, String spiceOutFile, String command) {
    File outFile_p = new File(spiceOutFile);

    double[][] tempData = new double[300][2];
    int rowIndex = 0;
    int i = 0;

    int numRead = 0;
    bool flag = false;
    bool flag_eldo = true;
    double temp_double = 0.0D;
    if (!outFile_p.canRead()) {

      printf("Unable to open " + spiceOutFile + " for reading");
      return 1;
    }

    try {
      BufferedReader SpiceReader = new BufferedReader(new FileReader(outFile_p));

      String lineBuffer;

      do {

      } while ((lineBuffer = SpiceReader.readLine()) != null &&
        lineBuffer.indexOf(s2iString.VIDataBeginMarker[spiceType]) < 0);
      if (lineBuffer.indexOf(s2iString.VIDataBeginMarker[spiceType]) < 0) {

        printf("Data begin marker '" +
            s2iString.VIDataBeginMarker[spiceType] + "'");
        printf("not found in output file " + spiceOutFile);
        SpiceReader.close();
        return 1;
      }

      if (spiceType == 5) {
          do {

        } while ((lineBuffer = SpiceReader.readLine()) != null &&
          !lineBuffer.startsWith(s2iString.VIDataBeginMarker[spiceType]));

        if (!lineBuffer.startsWith(s2iString.VIDataBeginMarker[spiceType])) {

          printf("Data begin marker '" +
              s2iString.VIDataBeginMarker[spiceType] + "'");
          printf("not found in output file " + spiceOutFile);
          SpiceReader.close();
          return 1;
        }
      }
      while ((lineBuffer = SpiceReader.readLine()) != null && flag_eldo) {
        if (lineBuffer != null) {

          StringTokenizer st2 = new StringTokenizer(lineBuffer);
          int cnt = st2.countTokens();
          if (cnt != 0) {

            String temp = st2.nextToken();
            try {
              temp_double = Double.parseDouble(temp);
              flag = true;
            }
            catch (Exception ex1) {
              if (ex1.toString().length() != 0) {


                flag = false;
                if (spiceType == 5)
                  flag_eldo = false;
              }
            }
          }
          if (cnt == 2 && flag) {




            tempData[rowIndex][0] = temp_double;
            tempData[rowIndex][1] = -Double.parseDouble(st2.nextToken());
            rowIndex++;
          }
          if ((cnt == 3 || cnt == 4) && flag) {




            tempData[rowIndex][0] = Double.parseDouble(st2.nextToken());
            st2.nextToken();
            tempData[rowIndex][1] = -Double.parseDouble(st2.nextToken());
            rowIndex++;
          }
        }
      }  SpiceReader.close();
    }
    catch (Exception ex) {
      printf("Exception while collecting spice data from out files (getSpiceVIData): " + ex.toString());
    }


    if (command.equalsIgnoreCase("typ")) {

      VIC.VIData2.size = rowIndex;
      for (int j = 0; j <= rowIndex - 1; j++)
      {
        (VIC.VIData2.VIs[j]).v = tempData[j][0];
        (VIC.VIData2.VIs[j]).i.typ = tempData[j][1];
        (VIC.VIData2.VIs[j]).i.min = 0.0D;
        (VIC.VIData2.VIs[j]).i.max = 0.0D;
      }

    } else if (command.equalsIgnoreCase("min")) {
      for (int j = 0; j < rowIndex; j++)
        (VIC.VIData2.VIs[j]).i.min = tempData[j][1];
    } else {
      for (int j = 0; j < rowIndex; j++)
        (VIC.VIData2.VIs[j]).i.max = tempData[j][1];
    }
    return 0;
  }
};

#endif
