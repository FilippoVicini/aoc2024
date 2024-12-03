#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <regex>

using namespace std;
void getNumbers(string str, regex reg, vector<string> &vec) {
  sregex_iterator currentMatch(str.begin(), str.end(), reg);
  sregex_iterator lastMatch;
  while (currentMatch != lastMatch) {
    smatch match = *currentMatch;
    // cout << match.str() << "\n";
    vec.push_back(match.str());
    currentMatch++;
  }
  cout << endl;
}
int processMulExpression(const string &expr) {
  regex mul_regex(R"(mul\((\d+),\s*(\d+)\))");
  smatch matches;
  if (regex_match(expr, matches, mul_regex)) {
    // Convert the captured strings to integers and multiply
    return stoi(matches[1]) * stoi(matches[2]);
  }
  return 0;
}
int main() {
  // input:
  // xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))
  // take out mul(x,y)
  // multiply togheter
  string fileName = "inputFile";
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
  smatch matches;
  regex reg(R"(mul\(\d+,\s*\d+\))");
  getNumbers(content, reg, matchesR);

  int finalResult = 0; // Initialize to 1 for multiplication
  for (const string &expr : matchesR) {
    cout << expr << " = ";
    int result = processMulExpression(expr);
    cout << result << endl;
    finalResult += result;
  }

  cout << "\nFinal result after multiplying all values: " << finalResult
       << endl;
}
