#include <config.h>
#include <utility.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

struct triangle {
  int sides[3];

  static triangle from_string(const std::string &str) {
    triangle t;
    std::istringstream(str) >> t.sides[0] >> t.sides[1] >> t.sides [2];
    return t;
  }

  static bool validate(const triangle &t) {
    return !(t.sides[0] + t.sides[1] <= t.sides[2] ||
             t.sides[1] + t.sides[2] <= t.sides[0] ||
             t.sides[0] + t.sides[2] <= t.sides[1]);
  }
};

int main(int, char *[]) {
  std::ifstream infile{INPUT_DIR "day03.txt"};
  std::vector<std::string> lines(std::istream_iterator<line>{infile},
                                 std::istream_iterator<line>{});
  std::vector<triangle> triangles;
  std::transform(lines.begin(), lines.end(), std::back_inserter(triangles), &triangle::from_string);

  int num_valid = std::accumulate(triangles.begin(), triangles.end(), 0,
                                  [](int n, const triangle &t) {
                                    return n + (triangle::validate(t) ? 1 : 0);
                                  });
  std::cout << num_valid << " valid triangles in input" << std::endl;
  return 0;
}
