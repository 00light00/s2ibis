#ifndef _RUNSPICEAGAIN
#define _RUNSPICEAGAIN

#include "callSpice.h"
#include "setupDCSweepCommands.h"
#include "setupSpiceInputFile.h"
#include "checkForAbort.h"
#include "checkForConvergence.h"
#

class runSpiceAgain
{
public:
  double sweepStart;
  double sweepEnd;

  runSpiceAgain(int curveType, int spiceType, double sweepStep, String spiceInFile, String spiceOutFile, String spiceMsgFile, int iterate, String headerLine, String spiceCommand, String spiceFile, String modelFileTyp, String extSpiceCmdFile, String loadBuffer, String inputBuffer, String powerBuffer, String temperatureBuffer)  {
    double newSweepStart = 0.0D, newSweepEnd = this.sweepEnd;
    String yes_no = "y";
    String user_in_string = "";
    String analysisBuffer = null;




    BigDecimal bdSS = new BigDecimal(this.sweepStart);
    printf("Current sweepStart = " + bdSS.setScale(2, 4));
    BigDecimal bdSE = new BigDecimal(this.sweepEnd);
    printf("Current sweepEnd = " + bdSE.setScale(2, 4));
    printf("Would you like to specifiy a different sweep range? [y/n] ");
    BufferedReader user_in = new BufferedReader(new InputStreamReader(System.in));
    setupDCSweepCommands setupDCSweepCmd = new setupDCSweepCommands();
    setupSpiceInputFile setSpInFile = new setupSpiceInputFile();
    callSpice callSpice1 = new callSpice();
    checkForAbort checkAbort = new checkForAbort();
    checkForConvergence chkConvergence = new checkForConvergence();

    yes_no = user_in.readLine();
    if (yes_no.equalsIgnoreCase("y") || yes_no.equalsIgnoreCase("yes") || yes_no.equalsIgnoreCase("")) {

      printf("New sweepStart (default:0) :");
      user_in_string = user_in.readLine();
      if (!user_in_string.equalsIgnoreCase("")) {

        try {
          newSweepStart = Double.parseDouble(user_in_string);
        }
        catch (Exception ex1) {
          printf("Faulty input - assuming default value");
          newSweepStart = 0.0D;
        }
      } else {

        newSweepStart = 0.0D;
      }
      printf("New sweepEnd (default:" + bdSE.setScale(2, 4) + ") :");
      user_in_string = user_in.readLine();
      if (!user_in_string.equalsIgnoreCase("")) {

        try {
          newSweepEnd = Double.parseDouble(user_in_string);
        }
        catch (Exception ex1) {
          printf("Faulty input - assuming default value");
          newSweepEnd = this.sweepEnd;
        }
      } else {

        newSweepEnd = this.sweepEnd;
      }
      bdSS = new BigDecimal(newSweepStart);
      bdSE = new BigDecimal(newSweepEnd);

      printf("New sweepStart = " + bdSS.setScale(2, 4));
      printf("New sweepEnd = " + bdSE.setScale(2, 4));
      this.sweepStart = newSweepStart;
      this.sweepEnd = newSweepEnd;
      analysisBuffer = setupDCSweepCmd.setupDCSweepCommands(curveType, spiceType, newSweepStart,
          newSweepEnd, sweepStep);

      if (setSpInFile.setupSpiceInputFile(iterate, spiceType, spiceInFile, headerLine,
          spiceFile, modelFileTyp, extSpiceCmdFile, loadBuffer, inputBuffer, powerBuffer,
          temperatureBuffer, analysisBuffer) == 1) {

        printf("Couldn't set up Spice File for " +
            s2iString.curveNameString[curveType] + " curve");
        return 1;
      }


      if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
          spiceOutFile, spiceMsgFile) == 1) {


        int returnFromAbort = checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
        if (returnFromAbort == 1) {

          printf("See file " + spiceMsgFile + " for information.");
          printf("Curve " + s2iString.curveNameString[curveType] + " not generated.");
          if (chkConvergence.checkForConvergence(spiceType, spiceOutFile) == 1)
          {
            printf("Spice run aborted CONVERENCE ISSUE detected.  ");
            return 1;
          }

        }
      }
    } else {

      printf("You entered '" + yes_no + "'");
      printf("Error in executing " + s2iString.spiceNameString[spiceType]);
      printf("Fatal Error. Exiting. ");
      System.exit(1);
      return 1;
    }
    return 0;
  }
};

#endif
