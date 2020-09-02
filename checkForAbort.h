#ifndef _CHECKFORABORT
#define _CHECKFORABORT

int checkForAbort(int spiceType, String spiceOutFile, String spiceMsgFile) {
    File tempFile_p = new File(spiceOutFile);


    try {
      BufferedReader tempReader = new BufferedReader(new FileReader(tempFile_p));
      if (tempFile_p.canRead()) {
        String lineBuffer;

        while ((lineBuffer = tempReader.readLine()) != null) {

          int abortOccur = lineBuffer.indexOf(s2iString.abortMarker[spiceType]);
          if (abortOccur != -1) {

            printf("Found " + s2iString.abortMarker[spiceType] + " in " + tempFile_p);
            tempReader.close();
            return 1;
          }
        }
        try {
          tempReader.close();
        }
        catch (IOException e) {
          printf("Error " + e.toString() + " while closing " + spiceOutFile);
          return 1;
        }

      } else {

        printf("Unable to open " + tempFile_p + " for reading");
        return 1;
      }

    } catch (IOException e1) {
      printf("Error " + e1.toString());
      printf("Error in running " + s2iString.spiceNameString[spiceType]);
      System.exit(1);
    }



    tempFile_p = new File(spiceMsgFile);

    if (spiceType != 5)

      try {
        BufferedReader tempReader = new BufferedReader(new FileReader(tempFile_p));
        if (tempFile_p.canRead()) {
          String lineBuffer;

          while ((lineBuffer = tempReader.readLine()) != null) {

            int abortOccur = lineBuffer.indexOf(s2iString.abortMarker[spiceType]);
            if (abortOccur != -1) {

              tempReader.close();
              return 1;
            }
          }
          try {
            tempReader.close();
          }
          catch (IOException e) {
            printf("Error " + e.toString() + " while closing " + spiceMsgFile);
            return 1;
          }

        }
      } catch (IOException e1) {
        printf("Warning ... " + e1.toString());
      }
    return 0;
  }


#endif

