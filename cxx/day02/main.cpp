#include <config.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

const int GRID_ROWS = 3;
const int GRID_COLS = 3;
const int GRID[GRID_ROWS][GRID_COLS] = {
    {7, 8, 9},
    {4, 5, 6},
    {1, 2, 3},
};

enum class move {
  kUp = 0,
  kRight,
  kDown,
  kLeft
};

struct coord {
  int x, y;

  static coord move(coord c, move m) {
    switch (m) {
      case move::kUp:
        c.y = std::min(c.y + 1, GRID_ROWS-1);
        break;
      case move::kRight:
        c.x = std::min(c.x + 1, GRID_COLS-1);
        break;
      case move::kDown:
        c.y = std::max(c.y - 1, 0);
        break;
      case move::kLeft:
        c.x = std::max(c.x - 1, 0);
        break;
    }
    return c;
  }
};

move move_from_char(char c) {
  switch (c) {
    case 'U':
      return move::kUp;
    case 'R':
      return move::kRight;
    case 'D':
      return move::kDown;
    case 'L':
      return move::kLeft;
    default:
      return move::kUp;
  }
}

std::vector<move> parse_moves(const std::string &line) {
  std::vector<move> moves;
  std::transform(line.begin(), line.end(), std::back_inserter(moves), &move_from_char);
  return moves;
}

int get_code(const std::vector<move> &moves) {
  coord c = std::accumulate(moves.begin(), moves.end(), coord{1, 1}, &coord::move);
  return GRID[c.y][c.x];
}

int main(int, char *[]) {
  std::ifstream infile{INPUT_DIR "day02.txt"};
  std::vector<std::string> lines{std::istream_iterator<std::string>{infile},
                                 std::istream_iterator<std::string>{}};

  std::vector<std::vector<move>> moves;
  std::transform(lines.begin(), lines.end(), std::back_inserter(moves), &parse_moves);

  std::vector<int> code;
  std::transform(moves.begin(), moves.end(), std::back_inserter(code), &get_code);

  std::for_each(code.begin(), code.end(), [](int n) {
    std::cout << n;
  });
  std::cout << std::endl;

  return 0;
}
