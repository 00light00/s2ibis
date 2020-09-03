#include "s2ifile.h"

s2ifile::s2ifile(string &infile) : inFile(infile) {}

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
        keyTree[key].push_back(line);
        break;
      }
    }
  } else {
    cout << "file open failed!!" << endl;
  }
  return;
}

void s2ifile::getKey(string &line, string &key) {
  int idx = line.find(']');
  string token = line.substr(1, idx - 1);

  for (auto it = token.begin(); it != token.end(); it++) {
    *it = tolower(*it);
  }
  key = token;
  keyTree[token] = vector<string>();
  line = line.substr(idx + 1);
  cout << token << endl;
}
