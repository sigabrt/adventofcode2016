#include <config.h>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>
#include <vector>

enum direction {
  kNorth = 0,
  kEast,
  kSouth,
  kWest
};

struct command {
  char action;
  int steps;

  static command from_string(const std::string &str) {
    command cmd;
    std::istringstream(str) >> cmd.action >> cmd.steps;
    return cmd;
  }

  // TODO: feels like this could be more concise
  static direction turn(direction start, char action) {
    switch (action) {
      case 'R':
        start = static_cast<direction>(static_cast<int>(start) + 1);
        break;
      case 'L':
        start = static_cast<direction>(static_cast<int>(start) - 1);
        break;
      default:
        break;
    }
    if (start < kNorth) start = kWest;
    if (start > kWest) start = kNorth;
    return start;
  }
};

struct state {
  struct coord {
    int x, y;
  };

  direction dir;
  coord pos;

  static coord move(coord cur, direction dir, int steps) {
    switch (dir) {
      case kNorth:
        return coord{cur.x, cur.y+steps};
      case kEast:
        return coord{cur.x+steps, cur.y};
      case kSouth:
        return coord{cur.x, cur.y-steps};
      case kWest:
        return coord{cur.x-steps, cur.y};
      default:
        return cur;
    }
  }

  static state act(state cur, command cmd) {
    direction new_dir{command::turn(cur.dir, cmd.action)};
    return state{new_dir, move(cur.pos, new_dir, cmd.steps)};
  }
};

int main(int argc, char *argv[]) {
  std::ifstream infile{INPUT_DIR "day01.txt"};
  std::vector<std::string> tokens(std::istream_iterator<std::string>{infile},
                                  std::istream_iterator<std::string>{});
  std::vector<command> commands;
  std::transform(tokens.begin(), tokens.end(), std::back_inserter(commands), &command::from_string);

  // Part 1
  state final_state = std::accumulate(commands.begin(), commands.end(), state{kNorth, {0, 0}}, &state::act);
  std::cout << final_state.pos.x + final_state.pos.y << std::endl;

  return 0;
}
