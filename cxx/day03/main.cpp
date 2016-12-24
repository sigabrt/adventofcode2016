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

std::vector<triangle> from_strings(const std::vector<std::string> &strings) {
  std::vector<triangle> triangles;

  std::vector<std::vector<int>> sides;
  std::transform(strings.begin(), strings.end(), std::back_inserter(sides), [](auto s) {
    return split<int>(s);
  });

  for (std::size_t i = 0; i < sides.size(); ++i) {
    triangles.push_back({{sides[i][0], sides[i][3], sides[i][6]}});
    triangles.push_back({{sides[i][1], sides[i][4], sides[i][7]}});
    triangles.push_back({{sides[i][2], sides[i][5], sides[i][8]}});
  }

  return triangles;
}

int main(int, char *[]) {
  std::ifstream infile{INPUT_DIR "day03.txt"};
  std::vector<std::string> lines{std::istream_iterator<line>{infile},
                                 std::istream_iterator<line>{}};

  // Part 1
  std::vector<triangle> triangles;
  std::transform(lines.begin(), lines.end(), std::back_inserter(triangles), &triangle::from_string);

  int num_valid = std::accumulate(triangles.begin(), triangles.end(), 0,
                                  [](int n, const triangle &t) {
                                    return n + (triangle::validate(t) ? 1 : 0);
                                  });
  std::cout << num_valid << " valid triangles in input" << std::endl;

  // Part 2
  infile.clear();
  infile.seekg(0, std::ios::beg);
  std::vector<std::string> line_triples{std::istream_iterator<n_lines<3>>{infile},
                                        std::istream_iterator<n_lines<3>>{}};
  triangles = from_strings(line_triples);

  num_valid = std::accumulate(triangles.begin(), triangles.end(), 0,
                              [](int n, const triangle &t) {
                                return n + (triangle::validate(t) ? 1 : 0);
                              });
  std::cout << num_valid << " valid triangles in input" << std::endl;

  return 0;
}
