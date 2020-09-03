#include <bits/stdc++.h>
using namespace std;

#include "s2ifile.h"

int main(int argc, char *argv[]) {
  string inputFileName;

  /**--------------------------------------------------------------------
   *  Check to see if someone used the "-h" or "-help" switch anywhere.
   *--------------------------------------------------------------------*/
  for (int i = 0; i < argc; i++) {
    if (!strcmp(argv[i], "-h")) {
      printf("\nUsage: s2ibis3 input_filename\n\n");
      exit(0);
    }
  }

  /**--------------------------------------------------------------------
   *   Print a header line.
   *--------------------------------------------------------------------*/
  if (argc > 1) {
    inputFileName = argv[1];
  } else {
    printf("input file: ");
    cin >> inputFileName;
  }

  //  cout << inputFileName << endl;
  /**--------------------------------------------------------------------
   *   Read the input file and proceed with analysis if no errors.
   *--------------------------------------------------------------------*/
  s2ifile s2ibis3file(inputFileName);
  s2ibis3file.s2iParse();
  return 0;
}
