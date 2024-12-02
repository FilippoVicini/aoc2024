#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool is_safe(const vector<int> &line) {
  for (size_t i = 1; i < line.size(); i++) {
    int diff = line[i] - line[i - 1];

    if (abs(diff) > 3 || diff == 0) {
      return false;
    }

    if (i > 1 && (diff > 0) != (line[i - 1] - line[i - 2] > 0)) {
      return false;
    }
  }
  return true;
}

int main() {

  string fileName = "inputFile";
  ifstream in(fileName);
  if (!in) {
    cerr << "Error: Could not open file " << fileName << endl;
    return 1;
  }

  vector<vector<int>> lines;
  string myText;

  while (getline(in, myText)) {
    stringstream ss(myText);
    vector<int> currentLine;
    int number;

    while (ss >> number) {
      currentLine.push_back(number);
    }

    if (!currentLine.empty()) {
      lines.push_back(currentLine);
    }
  }

  int safeCount = 0;

  for (const auto &line : lines) {
    if (is_safe(line)) {
      safeCount++;
      continue;
    }

    bool became_safe = false;

    for (size_t i = 0; i < line.size(); i++) {
      vector<int> modifiedLine = line;
      modifiedLine.erase(modifiedLine.begin() + i);
      if (is_safe(modifiedLine)) {
        became_safe = true;
        break;
      }
    }

    if (became_safe) {
      safeCount++;
    }
  }

  cout << "Safe Count (with adjustments): " << safeCount << endl;

  return 0;
}
