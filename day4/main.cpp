
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static constexpr std::array<char, 4> wordFind{'X', 'M', 'A', 'S'};
static constexpr std::array<int, 8> pivotsX{1, 1, 0, -1, -1, -1, 0, 1};
static constexpr std::array<int, 8> pivotsY{0, 1, 1, 1, 0, -1, -1, -1};

std::vector<std::vector<char>> read_file() {
  std::ifstream infile("input");
  std::vector<std::vector<char>> rows;

  for (std::string line; std::getline(infile, line);) {
    std::istringstream ss(line);
    std::vector<char> row;

    char value{0};
    while (ss >> value) {
      row.push_back(value);
    }

    rows.push_back(std::move(row));
  }

  return rows;
}

bool isVal(const std::vector<std::vector<char>> &word_search, int start_x,
           int start_y, int dir_x, int dir_y) {
  int dim_y = word_search.size();
  int dim_x = word_search.at(0).size();

  int x = start_x;
  int y = start_y;

  for (size_t i = 1; i < wordFind.size(); i++) {
    x += dir_x;
    y += dir_y;

    if (x < 0 || y < 0 || x >= dim_x || y >= dim_y) {
      return false;
    }

    if (word_search.at(y).at(x) != wordFind.at(i)) {
      return false;
    }
  }

  return true;
}

int main() {
  const auto wordArr = read_file();

  int xmas_count{0};

  for (size_t y = 0; y < wordArr.size(); y++) {
    for (size_t x = 0; x < wordArr.at(y).size(); x++) {
      if (wordArr.at(y).at(x) == wordFind.at(0)) {
        for (size_t i = 0; i < pivotsX.size(); i++) {
          bool xmas_found = isVal(wordArr, x, y, pivotsX.at(i), pivotsY.at(i));

          if (xmas_found)
            xmas_count++;
        }
      }
    }
  }

  std::cout << xmas_count << '\n';
}
