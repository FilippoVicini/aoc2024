#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void read_file(vector<pair<int, int>> &rules, vector<vector<int>> &values) {
  ifstream infile("input");

  if (!infile) {
    std::cerr << "Error opening file!" << std::endl;
  }

  int first, second;
  string line;
  bool readingPairs = true;

  while (getline(infile, line)) {
    if (line.empty()) {
      readingPairs = false;
      continue;
    }

    if (readingPairs) {
      istringstream ss(line);
      int first, second;
      char delimiter;
      ss >> first >> delimiter >> second;
      rules.emplace_back(first, second);
    } else {
      vector<int> currentLineNumbers;

      istringstream ss(line);
      string num;
      while (getline(ss, num, ',')) {
        currentLineNumbers.push_back(stoi(num));
      }

      values.push_back(currentLineNumbers);
    }
  }
}

bool checkValid(vector<pair<int, int>> &rules, vector<vector<int>> &values) {
  for (const auto &p : rules) {
    for (size_t i = 0; i < values.size();) {
      auto pos1 = find(values[i].begin(), values[i].end(), p.first);
      auto pos2 = find(values[i].begin(), values[i].end(), p.second);

      if (pos1 == values[i].end() && pos2 == values[i].end()) {
        i++;
        continue;
      }

      if (pos1 != values[i].end() && pos2 != values[i].end()) {
        if (pos1 > pos2) {
          values.erase(values.begin() + i);
        } else {
          i++;
        }
      } else {
        i++;
      }
    }
  }
  return true;
}

int returnSum(vector<vector<int>> &values) {
  int sum = 0;
  for (int i = 0; i < values.size(); i++) {
    int size = values[i].size();
    if (size % 2 == 0) {
      sum += (values[i][size / 2 - 1] + values[i][size / 2]) / 2;
    } else {
      sum += values[i][size / 2];
    }
  }
  return sum;
}

int main() {

  vector<pair<int, int>> rules;
  vector<vector<int>> values;
  read_file(rules, values);

  for (const auto &p : rules) {
    std::cout << "(" << p.first << ", " << p.second << ")\n";
  }
  for (const auto &line : values) {
    for (const auto &num : line) {
      cout << num << " ";
    }
    cout << endl;
  }
  checkValid(rules, values);
  for (const auto &p : rules) {
    std::cout << "(" << p.first << ", " << p.second << ")\n";
  }
  for (const auto &line : values) {
    for (const auto &num : line) {
      cout << num << " ";
    }
    cout << endl;
  }

  int sum = returnSum(values);

  cout << "SUM" << sum;
}
