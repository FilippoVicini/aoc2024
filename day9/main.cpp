#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void read_file(vector<int> &longline) {
  fstream myfile("input.txt", ios_base::in);
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

void convert(vector<int> &longline, vector<int> &v) {
  for (int i = 0; i < longline.size(); i++) {
    if (i % 2 == 1) {
      v.insert(v.end(), longline[i], -1);
    } else {
      v.insert(v.end(), longline[i], i / 2);
    }
  }
}

void compacting(vector<int> &v) {
  int i = 0, j = v.size() - 1;
  while (i < j) {
    if (v[i] == -1 && v[j] != -1) {
      std::swap(v[i], v[j]);
      continue;
    }

    if (v[i] != -1) {
      i++;
    }

    if (v[j] == -1) {
      j--;
    }
  }
}

long long countRes(const vector<int> &v) {
  long long ans = 0;
  for (int i = 0; i < v.size() && v[i] != -1; i++) {
    ans += i * v[i];
  }
  return ans;
}

int main() {

  vector<int> line;
  read_file(line);
  vector<int> newVec;

  convert(line, newVec);
  compacting(newVec);
  cout << countRes(newVec);

  return 0;
}
