#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void read_file(vector<string> &lines) {
  ifstream infile("input");
  if (!infile) {
    cerr << "Error opening file!" << endl;
    return;
  }
  string line;
  while (getline(infile, line)) {
    lines.push_back(line);
  }
}

void parseLines(vector<string> &lines,
                vector<pair<long, vector<long>>> &values) {
  for (const string &line : lines) {
    stringstream ss(line);
    long key;
    char colon;
    ss >> key >> colon;
    vector<long> inner;
    long value;
    while (ss >> value) {
      inner.push_back(value);
    }
    values.emplace_back(key, inner);
  }
}

void generateSignCombinations(int n, vector<string> &combinations) {
  int total = 1 << (n - 1); // For n numbers, there are n-1 operator slots
  for (int i = 0; i < total; ++i) {
    string combination;
    for (int j = 0; j < n - 1; ++j) {
      if (i & (1 << j)) {
        combination += '+';
      } else {
        combination += '*';
      }
    }
    combinations.push_back(combination);
  }
}

long evaluateExpression(const vector<long> &numbers, const string &operators) {
  if (numbers.empty())
    return 0;

  long result = numbers[0];
  for (size_t i = 0; i < operators.size(); ++i) {
    if (operators[i] == '+') {
      result += numbers[i + 1];
    } else if (operators[i] == '*') {
      result *= numbers[i + 1];
    }
  }
  return result;
}

long calculateCalibrationResult(vector<pair<long, vector<long>>> &values) {
  long totalCalibrationResult = 0;

  for (const auto &entry : values) {
    long target = entry.first;
    const vector<long> &numbers = entry.second;

    if (numbers.empty())
      continue;

    vector<string> signCombinations;
    generateSignCombinations(numbers.size(), signCombinations);

    bool isPossible = false;
    for (const string &operators : signCombinations) {
      long result = evaluateExpression(numbers, operators);
      if (result == target) {
        isPossible = true;
        totalCalibrationResult += target;
        break;
      }
    }
  }
  return totalCalibrationResult;
}

int main() {
  vector<string> lines;
  vector<pair<long, vector<long>>> values;

  read_file(lines);
  parseLines(lines, values);

  long totalCalibrationResult = calculateCalibrationResult(values);
  cout << "Total Calibration Result: " << totalCalibrationResult << endl;

  return 0;
}
