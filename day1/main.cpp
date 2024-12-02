#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  string fileName = "input";
  string myText;
  vector<int> firstColumn;
  vector<int> secondColumn;
  vector<int> result;
  string first, second;

  ifstream in(fileName);
  if (!in) {
    cerr << "Error: Could not open file " << fileName << endl;
    return 1;
  }

  while (getline(in, myText)) {
    stringstream ss(myText);
    int first, second;

    if (ss >> first >> second) {
      firstColumn.push_back(first);
      secondColumn.push_back(second);
    } else {
      cerr << "Error: Failed to parse line: " << myText << endl;
    }
  }

  for (int i = 0; i < firstColumn.size(); i++) {
    int count = 0;
    for (int j = 0; j < secondColumn.size(); j++) {
      if (firstColumn[i] == secondColumn[j]) {
        count++;
      }
    }
    result.push_back(firstColumn[i] * count);
  }
  int solution = 0;

  for (int i = 0; i < firstColumn.size(); i++) {
    solution += result[i];
    cout << "result " << result[i] << endl;
  }
  cout << solution;
}

/* PART 1
int main() {
  string fileName = "input";
  string myText;
  vector<int> firstColumn;
  vector<int> secondColumn;
  vector<int> result;
  string first, second;

  ifstream in(fileName);
  if (!in) {
    cerr << "Error: Could not open file " << fileName << endl;
    return 1;
  }

  while (getline(in, myText)) {
    stringstream ss(myText);
    int first, second;

    if (ss >> first >> second) { // Extract and convert to int in one step
      firstColumn.push_back(first);
      secondColumn.push_back(second);
    } else {
      cerr << "Error: Failed to parse line: " << myText << endl;
    }
  }

  int sum = 0;
  sort(firstColumn.begin(), firstColumn.end());
  sort(secondColumn.begin(), secondColumn.end());
  for (int i = 0; i < firstColumn.size(); i++) {
    int num = abs(firstColumn[i] - secondColumn[i]);
    result.push_back(num);
  }
  for (int i = 0; i < result.size(); i++) {
    sum = sum + result[i];
    cout << "value" << result[i] << endl;
  }
  cout << sum;
}
*/
