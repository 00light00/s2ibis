#ifndef _CHECKFORCONVERGENCE
#define _CHECKFORCONVERGENCE
int checkForConvergence(int spiceType, String spiceOutFile) {
    File tempFile_p = new File(spiceOutFile);


    try {
      BufferedReader tempReader = new BufferedReader(new FileReader(tempFile_p)); String lineBuffer;
      while ((lineBuffer = tempReader.readLine()) != null) {

        int convergenceOccur = lineBuffer.indexOf(s2iString.convergenceMarker[spiceType]);
        if (convergenceOccur != -1)
        {
          printf("Found '" + s2iString.convergenceMarker[spiceType] + "' in " + tempFile_p);
          tempReader.close();
          return 1;
        }

      }
    } catch (IOException e1) {
      printf("Error " + e1.toString());
      return 1;
    }

    return 0;
  }



#endif
