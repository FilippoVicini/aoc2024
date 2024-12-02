#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string fileName = "inputFile";
  string myText;
  vector<vector<int>> lines;
  vector<vector<int>> flines;
  vector<int> result;
  string first, second;

  ifstream in(fileName);
  if (!in) {
    cerr << "Error: Could not open file " << fileName << endl;
    return 1;
  }

  while (getline(in, myText)) {
    stringstream ss(myText);
    vector<int> currentLine;
    int number;

    while (ss >> number) {
      currentLine.push_back(number);
    }

    if (!currentLine.empty()) {
      lines.push_back(currentLine);
    } else {
      cerr << "Warning: Empty or invalid line skipped: " << myText << endl;
    }
  }

  vector<bool> vals;

  for (int i = 0; i < lines.size(); i++) {
    vector<int> vec = lines[i];
    if (is_sorted(lines[i].begin(), lines[i].end())) {
      cout << "sorted" << endl;
      flines.push_back(vec);
    } else if (is_sorted(lines[i].begin(), lines[i].end(), greater<int>())) {
      cout << "sorted" << endl;
      flines.push_back(vec);
    } else {
      cout << "not sorted" << endl;
    }
  }

  int count = 0;

  int safeCount = 0;

  for (const auto &line : lines) {
    bool safe = true;

    for (size_t j = 1; j < line.size(); j++) {
      int diff = line[j] - line[j - 1];

      if (abs(diff) > 3 || diff == 0) {
        safe = false;
        break;
      }

      if (j > 1 && (diff > 0) != (line[j - 1] - line[j - 2] > 0)) {
        safe = false;
        break;
      }
    }

    if (safe) {
      safeCount++;
    }
  }

  cout << "Safe Count: " << safeCount << endl;

  return 0;
}
