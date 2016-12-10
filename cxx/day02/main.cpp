#include <config.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

const int P1_GRID_ROWS = 3;
const int P1_GRID_COLS = 3;
const char P1_GRID[P1_GRID_ROWS][P1_GRID_COLS] = {
    {'7', '8', '9'},
    {'4', '5', '6'},
    {'1', '2', '3'},
};

const int P2_GRID_ROWS = 5;
const int P2_GRID_COLS = 5;
const char P2_GRID[P2_GRID_ROWS][P2_GRID_COLS] = {
    { 0 ,  0 , 'D',  0 ,  0 },
    { 0 , 'A', 'B', 'C',  0 },
    {'5', '6', '7', '8', '9'},
    { 0 , '2', '3', '4',  0 },
    { 0 ,  0 , '1',  0 ,  0 },
};

enum class move {
  kUp,
  kRight,
  kDown,
  kLeft
};

struct coord {
  int x, y;

  template<int rows, int cols>
  static coord perform_move(coord c, move m) {
    switch (m) {
      case move::kUp:
        c.y = std::min(c.y + 1, rows-1);
        break;
      case move::kRight:
        c.x = std::min(c.x + 1, cols-1);
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

  template<int rows, int cols>
  static coord perform_move(coord c, move m, const char grid[rows][cols]) {
    coord new_coord = perform_move<rows, cols>(c, m);
    if (grid[new_coord.y][new_coord.x] == 0) {
      return c;
    }
    return new_coord;
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

template<int rows, int cols>
char get_code(const std::vector<move> &moves, coord start, const char grid[rows][cols]) {
  coord c = std::accumulate(moves.begin(), moves.end(), start,
                            [&](coord c, move m) {
                              return coord::perform_move<rows, cols>(c, m, grid);
                            });
  return grid[c.y][c.x];
}

int main(int, char *[]) {
  std::ifstream infile{INPUT_DIR "day02.txt"};
  std::vector<std::string> lines{std::istream_iterator<std::string>{infile},
                                 std::istream_iterator<std::string>{}};

  std::vector<std::vector<move>> moves;
  std::transform(lines.begin(), lines.end(), std::back_inserter(moves), &parse_moves);

  // Part 1
  std::vector<char> code;
  std::transform(moves.begin(), moves.end(), std::back_inserter(code),
                 [](const std::vector<move> &m) {
                   return get_code<P1_GRID_ROWS, P1_GRID_COLS>(m, coord{1, 1}, P1_GRID);
                 });

  std::for_each(code.begin(), code.end(), [](char c) {
    std::cout << c;
  });
  std::cout << std::endl;

  // Part 2
  code.clear();
  std::transform(moves.begin(), moves.end(), std::back_inserter(code),
                 [](const std::vector<move> &m) {
                   return get_code<P2_GRID_ROWS, P2_GRID_COLS>(m, coord{2, 2}, P2_GRID);
                 });

  std::for_each(code.begin(), code.end(), [](char c) {
    std::cout << c;
  });
  std::cout << std::endl;

  return 0;
}
