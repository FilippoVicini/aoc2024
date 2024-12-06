#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void read_file(vector<vector<char>> &grid) {
  ifstream infile("input");

  if (!infile) {
    cerr << "Error opening file!" << endl;
    return;
  }

  string line;

  while (getline(infile, line)) {
    vector<char> currentLine;

    for (char c : line) {
      currentLine.push_back(c);
    }

    grid.push_back(currentLine);
  }
}

void getStart(vector<vector<char>> &grid, int &startI, int &startJ) {

  char dir = '^';
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == dir) {
        startI = i;
        startJ = j;
      }
    }
  }
}

int main() {
  vector<vector<char>> grid;
  int startI = 0;
  int startJ = 0;
  read_file(grid);
  getStart(grid, startI, startJ);
  cout << startI;
  cout << startJ;
  int i = startI;
  int j = startJ;
  char dir = '^';
  while (i > 0 && j > 0) {
    char curPos = grid[startI][startJ];
    curPos = 'X';
    startI = startI - 1;
    if (curPos == dir && grid[startI - 1][startJ] != '#') {
      grid[startI][startJ] = 'X';
      grid[startI - 1][startJ] = '^';
    } else if (curPos == dir && grid[startI][startJ] == '#') {
      grid[startI][startJ] = 'X';
      grid[startI][startJ + 1] = '>';
    }
  }
}
