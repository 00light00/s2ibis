#ifndef _CALLSPICE
#define _CALLSPICE

#include <string>
using String = std::string;

#include "s2iString.h"

int callSpice(int iterate, String spiceCommand, int spiceType, String spiceInFile, String spiceOutFile, String spiceMsgFile) {
    String commandBuffer, shellFileName = String.valueOf(s2iString.spiceNameString[spiceType]) + ".sh";
    String batFileName = String.valueOf(s2iString.spiceNameString[spiceType]) + "_run.bat";
    String pathSep = System.getProperty("path.separator");

    File tempFile_p = new File(spiceOutFile);


    int status = 0;

    if (!spiceCommand.equals("")) {

      Object[] args = { spiceInFile, spiceOutFile, spiceMsgFile };
      MessageFormat mf = new MessageFormat(spiceCommand);
      commandBuffer = mf.format(args);
    } else {

      commandBuffer = s2iString.defaultSpiceCommand(spiceType,
          spiceInFile, spiceOutFile, spiceMsgFile);
    }
    if (iterate != 1 || !tempFile_p.canRead()) {

      printf("Starting " + s2iString.spiceNameString[spiceType] +
          " job with input " + spiceInFile);
      try {
        if (pathSep.charAt(0) == ':') {

          File shell_p = new File(shellFileName);
          PrintWriter out_shell =
            new PrintWriter(
              new BufferedWriter(
                new FileWriter(shell_p)));

          out_shell.println(commandBuffer);
          out_shell.close();

          Runtime rt = Runtime.getRuntime();
          Process proc = rt.exec("sh " + shellFileName);


          StreamGobbler errorGobbler = new StreamGobbler(proc.getErrorStream(), "ERROR");

          StreamGobbler opGobbler = new StreamGobbler(proc.getInputStream(), "OUTPUT");
          proc.waitFor();
          status = proc.exitValue();
        }
        else if (pathSep.charAt(0) == ';') {

          File bat_p = new File(batFileName);
          PrintWriter out_bat =
            new PrintWriter(
              new BufferedWriter(
                new FileWriter(bat_p)));

          commandBuffer = s2iString.spiceCommandForWin(spiceType,
              spiceInFile, spiceOutFile, spiceMsgFile);

          out_bat.println(commandBuffer);
          if (spiceType == 0) {
            out_bat.println("move " + spiceOutFile + ".lis " + spiceOutFile);
          }
          out_bat.close();

          Runtime rt = Runtime.getRuntime();
          Process proc = rt.exec(batFileName);


          StreamGobbler errorGobbler = new StreamGobbler(proc.getErrorStream(), "ERROR");

          StreamGobbler opGobbler = new StreamGobbler(proc.getInputStream(), "OUTPUT");

          errorGobbler.start();
          opGobbler.start();

          int exitVal = proc.waitFor();

          status = proc.exitValue();
        }

        if (status != 0 || pathSep.charAt(0) == ';')
        {
          return 1;
        }

        return 0;
      }
      catch (Exception ex) {
        printf("Exception while running Spice: " + ex.toString());
      }

    } else {

      printf("[iterate] set and file " + spiceOutFile + " exists");
      printf("Skipping Run");
    }
    return 0;



#endif
