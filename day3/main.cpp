#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void getNumbers(string str, regex reg, vector<string> &vec) {
  sregex_iterator currentMatch(str.begin(), str.end(), reg);
  sregex_iterator lastMatch;
  while (currentMatch != lastMatch) {
    smatch match = *currentMatch;
    vec.push_back(match.str());
    currentMatch++;
  }
  cout << endl;
}

int processMulExpression(const string &expr) {
  regex mul_regex(R"(mul\((\d+),\s*(\d+)\))");
  smatch matches;
  if (regex_match(expr, matches, mul_regex)) {
    return stoi(matches[1]) * stoi(matches[2]);
  }
  return 0;
}

int main() {
  string fileName = "inputFile2";
  ifstream file(fileName);

  if (!file.is_open()) {
    cerr << "Error: Could not open file " << fileName << endl;
    return 1;
  }

  stringstream buffer;
  buffer << file.rdbuf();
  string content = buffer.str();
  cout << content;

  vector<string> matchesR;
  regex reg(R"(do\(\)|don't\(\)|mul\(\d+,\d+\))");
  getNumbers(content, reg, matchesR);

  bool enabled = true;
  int finalResult = 0;

  for (const string &expr : matchesR) {
    if (expr == "don't()") {
      enabled = false;
    } else if (expr == "do()") {
      enabled = true;
    } else if (expr.substr(0, 3) == "mul" && enabled) {
      cout << expr << " = ";
      int result = processMulExpression(expr);
      cout << result << endl;
      finalResult += result;
    }
  }

  cout << "\nFinal result after multiplying all values: " << finalResult
       << endl;

  return 0;
}
