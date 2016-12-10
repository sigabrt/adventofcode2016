#include <config.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>
#include <unordered_map>

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

    static std::vector<coord> interpolate(const coord &start, const coord &end) {
      std::vector<coord> results;
      if (start.x != end.x) {
        for (int i = start.x; (start.x - end.x > 0) ? (i >= end.x) : (i <= end.x); (start.x - end.x > 0) ? --i : ++i) {
          results.push_back(coord{i, start.y});
        }
      } else {
        for (int i = start.y; (start.y - end.y > 0) ? (i >= end.y) : (i <= end.y); (start.y - end.y > 0) ? --i : ++i) {
          results.push_back(coord{start.x, i});
        }
      }
      return results;
    }
  };

  direction dir;
  coord pos;

  bool operator<(const state &other) const {
    if (this->pos.x < other.pos.x) return true;
    else if (this->pos.y < other.pos.y) return true;
    return false;
  }

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

  static std::vector<state> interpolate(const state &start, state &end) {
    auto coords = coord::interpolate(start.pos, end.pos);
    std::vector<state> states;
    std::transform(coords.begin(), coords.end(), std::back_inserter(states),
                   [=](coord &c) {
                     return state{start.dir, c};
                   });
    states.back().dir = end.dir;
    return states;
  }
};

int main(int, char *[]) {
  std::ifstream infile{INPUT_DIR "day01.txt"};
  std::vector<std::string> tokens(std::istream_iterator<std::string>{infile},
                                  std::istream_iterator<std::string>{});
  std::vector<command> commands;
  std::transform(tokens.begin(), tokens.end(), std::back_inserter(commands), &command::from_string);

  // Part 1
  state final_state = std::accumulate(commands.begin(), commands.end(), state{kNorth, {0, 0}}, &state::act);
  std::cout << "The Easter Bunny HQ is " << final_state.pos.x + final_state.pos.y << " blocks away" << std::endl;

  // Part 2
  std::vector<state> states = std::accumulate(commands.begin(), commands.end(),
                                              std::vector<state>{state{kNorth, {0, 0}}},
                                              [](std::vector<state> s, command c) {
                                                state new_state = state::act(s.back(), c);
                                                auto walk = state::interpolate(s.back(), new_state);
                                                s.insert(s.end(), std::next(walk.begin()), walk.end());
                                                return s;
                                              });

  std::set<state> state_set;
  state first_duplicate_state;
  std::find_if(states.begin(), states.end(), [&](const state &s) {
    auto insertion_result = state_set.insert(s);
    if (!insertion_result.second) {
      first_duplicate_state = s;
      return true;
    }
    return false;
  });
  std::cout << "The Easter Bunny HQ is " << first_duplicate_state.pos.x + first_duplicate_state.pos.y
            << " blocks away" << std::endl;

  return 0;
}
