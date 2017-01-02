#include <config.h>
#include <utility.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

struct room {
  std::vector<std::string> name;
  unsigned int id;
  std::vector<char> checksum;

  static room from_string(std::string str) {
    // example room: aaaaa-bbb-z-y-x-123[abxyz]
    room r;
    auto components = split(str, '-');
    r.name = std::vector<std::string>(components.begin(), components.end() - 1);
    
    // Find and parse the ID
    const auto &id_checksum = components.back();
    std::size_t sep = id_checksum.find('[');
    r.id = std::stod(id_checksum.substr(0, sep));
    
    // Find and copy the checksum string into the checksum character vector
    std::string str_checksum = id_checksum.substr(sep + 1, id_checksum.length() - sep - 2);
    r.checksum.resize(str_checksum.length());
    std::copy(str_checksum.c_str(), str_checksum.c_str() + str_checksum.length(), r.checksum.begin());

    return r;
  }
};

int main(int, char *[]) {
  std::ifstream infile{INPUT_DIR "day04.txt"};
  std::vector<std::string> lines{std::istream_iterator<line>{infile},
                                 std::istream_iterator<line>{}};

  std::vector<room> rooms;
  std::transform(lines.begin(), lines.end(), std::back_inserter(rooms), &room::from_string);

  return 0;
}
