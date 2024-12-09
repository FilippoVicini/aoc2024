#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void read_file(vector<int> &longline) {
  fstream myfile("input", ios_base::in);
  if (!myfile.is_open()) {
    cerr << "Error: Could not open the file 'input'." << endl;
    return;
  }

  char ch;
  while (myfile >> ch) {
    if (isdigit(ch)) {
      longline.push_back(ch - '0');
    }
  }

  myfile.close();
}

void convert(vector<int> &longline, vector<char> &newVec) {
  int count = 0;

  for (int i = 0; i < longline.size(); i++) {
    if (i % 2 != 0) {
      for (int j = 0; j < longline[i]; j++) {
        newVec.push_back('.');
      }
    } else {
      for (int j = 0; j < longline[i]; j++) {
        newVec.push_back('0' + count);
      }
      count++;
    }
  }

  for (int i = 0; i < newVec.size(); i++) {
    cout << newVec[i];
  }
  cout << endl;
}

void compacting(vector<char> &newVec, vector<char> &resVec) {
  int size = newVec.size();
  resVec.resize(size, '.');
  size_t lastNumIndex = size - 1; // Changed to size_t
  int validCount = 0;

  for (int i = 0; i < newVec.size(); i++) {
    if (newVec[i] != '.') {
      validCount++;
    }
  }

  while (lastNumIndex < newVec.size() &&
         newVec[lastNumIndex] == '.') { // Added size check
    if (lastNumIndex == 0)
      break; // Prevent underflow
    lastNumIndex--;
  }

  for (int i = 0; i < size; i++) {
    if (newVec[i] != '.') {
      resVec[i] = newVec[i];
    } else {
      if (lastNumIndex >= i) {
        while (lastNumIndex >= i && newVec[lastNumIndex] == '.') {
          if (lastNumIndex == 0)
            break; // Prevent underflow
          lastNumIndex--;
        }
        if (lastNumIndex >= i) {
          resVec[i] = newVec[lastNumIndex];
          if (lastNumIndex > 0)
            lastNumIndex--; // Prevent underflow
        } else {
          resVec[i] = '.';
        }
      } else {
        resVec[i] = '.';
      }
    }
  }

  for (int i = validCount; i < newVec.size(); i++) {
    resVec[i] = '.';
  }

  for (char c : resVec) {
    cout << c;
  }
  cout << endl;
}

int countRes(vector<char> resVec) {
  float mul = 0;
  for (int i = 0; i < resVec.size(); i++) {
    if (resVec[i] != '.') {
      mul += i * (resVec[i] - '0'); // Convert char to int
    }
  }
  return static_cast<int>(mul);
}

int main() {

  vector<int> line;
  read_file(line);
  vector<char> newVec;
  vector<char> resVec;

  if (line.empty()) {
    cout << "No data read from the file." << endl;
    return 0;
  }

  for (int i = 0; i < line.size(); i++) {
    cout << line[i] << " ";
  }

  cout << endl;
  convert(line, newVec);
  cout << endl;
  compacting(newVec, resVec);
  cout << countRes(resVec);
  return 0;
}
