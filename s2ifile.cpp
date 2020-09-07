#include <chrono>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;
#include "s2ifile.h"

s2ifile::s2ifile(string &infile) : inFile(infile) {
  int size = KeyNames.size();
  for (int i = 0; i < size; ++i) {
    keyNameToInt[KeyNames[i]] = i + 1;
  }
  //  keyAndData.resize(KeyNames.size() + 1);
}

void s2ifile::s2iParse() {
  fstream fs(inFile);
  chrono::system_clock::time_point nowtime = chrono::system_clock::now();
  time_t tt = chrono::system_clock::to_time_t(nowtime);
  char datebuff[80];
  strftime(datebuff, 80, "%b %c", localtime(&tt));
  printf("This File Name = %s\n", inFile.c_str());
  printf("Date = %s\n", datebuff);

  //  cout << fs.eof() << endl;
  if (fs.is_open()) {
    try {
      string key = "";
      while (!fs.eof()) {
        string line;
        getline(fs, line);
        switch (line[0]) {
        case '\0':
        case '\n':
        case '|':
          break;
        case '[':
          getKey(line, key);
        default:
          //        cout << line << endl;
          keyAndData[key].push_back(line);
          processKey(key, line);
          break;
        }
      }
    } catch (const exception &ex) {
      string Msg = ex.what();
      if (!Msg.empty()) {
        cout << "error: " + Msg << endl;
        cout << "s2ibis3: Unable to open " + inFile + " for reading" << endl;
        exit(1);
      }
    }
  } else {
    cout << "file open failed!!" << endl;
  }
  return;
}

void s2ifile::getKey(string &line, string &key) {
  long long idx = line.find(']');
  string token = line.substr(1, idx - 1);

  for (auto it = token.begin(); it != token.end(); it++) {
    *it = tolower(*it);
  }

  key = token;
  keyAndData[token] = vector<string>();
  line = line.substr(idx + 1);
  cout << token << endl;
}

void s2ifile::processKey(string &key, string &line) {
  stringstream sst(line);
  string firstArg = "";
  if (!line.empty())
    sst >> firstArg;

  /***********************************************************
   *        Filling up the Global parameters
   ***********************************************************/
  if (strcmp(key.c_str(), "ibis ver") == 0) {
    globalProc = true;
    componentProc = false;
    modelProc = false;
    if (strcmp(firstArg.c_str(), "1.1") == 0)
      ;
    else if (strcmp(firstArg.c_str(), "2.1") == 0)
      ;
    //      ibis.ibisVersion = ConstantStuff::VERSION_TWO_ONE;
    else if (strcmp(firstArg.c_str(), "3.2") == 0)
      ;
    //    ibis.ibisVersion = ConstantStuff::VERSION_THREE_TWO;
    else {
      cout << "s2ibis: Please begin with s2ibis comand file with [IBIS Ver] "
              "command"
           << endl;
    }
  }

  if (globalProc) {
    completeHeader(key, line);
  }

  /***********************************************************
   *        Filling up the Component and all its parameters
   ***********************************************************/
  if (strcmp(key.c_str(), "component") == 0) {
    globalProc = false;
    componentProc = true;
    modelProc = false;
  }
  /***********************************************************
   *        Filling up the Model and all its parameters
   ***********************************************************/
  if (strcmp(key.c_str(), "model") == 0) {
    globalProc = false;
    componentProc = true;
    modelProc = false;
  }
}

void s2ifile::completeHeader(string &key, string &line) {
  static map<string, function<void()>> headerKeyfunc{
      {"temperature range",
       [&]() {
         if (!line.empty())
           ibisGlobal.tempRange = TypMinMax(line);
       }},
      {"voltage range",
       [&]() {
         if (!line.empty())
           ibisGlobal.voltageRange = TypMinMax(line);
       }},
      {"pullup reference",
       [&]() {
         if (!line.empty())
           ibisGlobal.pullupRef = TypMinMax(line);
       }},
      {"pulldown reference",
       [&]() {
         if (!line.empty())
           ibisGlobal.pulldownRef = TypMinMax(line);
       }},
      {"power clamp reference",
       [&]() {
         if (!line.empty())
           ibisGlobal.powerClampRef = TypMinMax(line);
       }},
      {"gnd clamp reference",
       [&]() {
         if (!line.empty())
           ibisGlobal.gndClampRef = TypMinMax(line);
       }},
  };
  auto it = headerKeyfunc.find(key);
  if (it != headerKeyfunc.end()) {
    it->second();
  }
}

string s2ifile::newVal(string &args) {

  string str;
  if (args.empty() || (strcmp(args.c_str(), "") == 0) ||
      (strcmp(args.c_str(), "NA") == 0))
    str = "";
  else
    str = args;
  return str;
}

ibisTypMinMax s2ifile::TypMinMax(const string &args) {
  stringstream sst(args);
  ibisTypMinMax typMinMax;
  for (int i = 0; i < 3; ++i) {
    string temp;
    sst >> temp;
    switch (i) {
    case 0:
      typMinMax.typ = matchNum(temp);
      break;
    case 1:
      typMinMax.min = matchNum(temp);
      break;
    case 2:
      typMinMax.max = matchNum(temp);
      break;
    }
  }
  return typMinMax;
}

double s2ifile::matchNum(const string &in) {
  stringstream sst(in);
  double finalResult = 0;
  string factor;
  if (!strcmp(in.c_str(), "NA")) {
    finalResult = ConstantStuff::USE_NA;
  } else {
    sst >> finalResult >> factor;
    finalResult = stripFactor(finalResult, factor[0]);
  }

  return finalResult;
}

double s2ifile::stripFactor(double Result, char Factor) {
  double finalResult = Result;
  switch (Factor) {
  case 'n':
    finalResult = finalResult * 1.e-9;
    break;
  case 'p':
    finalResult = finalResult * 1.e-12;
    break;
  case 'm':
    finalResult = finalResult * 1.e-3;
    break;
  case 'u':
    finalResult = finalResult * 1.e-6;
    break;
  case 'f':
    finalResult = finalResult * 1.e-15;
    break;
  case 'T':
    finalResult = finalResult * 1.e12;
    break;
  case 'k':
    finalResult = finalResult * 1.e3;
    break;
  case 'G':
    finalResult = finalResult * 1.e9;
    break;
  case 'M':
    finalResult = finalResult * 1.e6;
    break;
  }
  return finalResult;
}

ibisWaveTable::ibisWaveTable() {
  R_fixture = ConstantStuff::USE_NA;
  V_fixture = ConstantStuff::USE_NA;
  V_fixture_min = ConstantStuff::USE_NA;
  V_fixture_max = ConstantStuff::USE_NA;
  L_fixture = ConstantStuff::USE_NA;
  C_fixture = ConstantStuff::USE_NA;
  R_dut = ConstantStuff::USE_NA;
  L_dut = ConstantStuff::USE_NA;
  C_dut = ConstantStuff::USE_NA;
}
