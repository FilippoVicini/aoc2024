#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Using long long to handle larger numbers
long long extractNumbers(const string &expr) {
  size_t start = expr.find('(');
  size_t comma = expr.find(',', start);
  size_t end = expr.find(')', comma);

  if (start == string::npos || comma == string::npos || end == string::npos) {
    return 0;
  }

  string num1_str = expr.substr(start + 1, comma - start - 1);
  string num2_str = expr.substr(comma + 1, end - comma - 1);

  // Remove whitespace
  num1_str.erase(remove_if(num1_str.begin(), num1_str.end(), ::isspace),
                 num1_str.end());
  num2_str.erase(remove_if(num2_str.begin(), num2_str.end(), ::isspace),
                 num2_str.end());

  // Validate numbers
  if (num1_str.empty() || num2_str.empty() ||
      !all_of(num1_str.begin(), num1_str.end(), ::isdigit) ||
      !all_of(num2_str.begin(), num2_str.end(), ::isdigit)) {
    return 0;
  }

  // Using stoll for long long conversion to handle larger numbers
  return stoll(num1_str) * stoll(num2_str);
}

vector<string> findMultiplications(const string &text) {
  vector<string> multiplications;
  size_t pos = 0;

  while ((pos = text.find("mul(", pos)) != string::npos) {
    int parentheses = 1;
    size_t start = pos;
    size_t i = pos + 4; // skip "mul("

    while (i < text.length() && parentheses > 0) {
      if (text[i] == '(')
        parentheses++;
      if (text[i] == ')')
        parentheses--;
      i++;
    }

    if (parentheses == 0) {
      multiplications.push_back(text.substr(start, i - start));
    }

    pos = i;
  }

  return multiplications;
}

int main() {
  string fileName = "inputFile";
  ifstream file(fileName);

  if (!file.is_open()) {
    cerr << "Error: Could not open file " << fileName << endl;
    return 1;
  }

  stringstream buffer;
  buffer << file.rdbuf();
  string content = buffer.str();

  vector<string> multiplications = findMultiplications(content);
  long long total = 0; // Using long long for the total

  cout << "Found expressions:" << endl;
  for (const string &expr : multiplications) {
    long long result = extractNumbers(expr);
    cout << expr << " = " << result << endl;
    total += result;
  }

  cout << "\nTotal sum: " << total << endl;

  return 0;
}
