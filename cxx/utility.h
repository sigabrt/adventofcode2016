#pragma once
#include <numeric>
#include <string>
#include <sstream>
#include <vector>

struct line {
  std::string data;

  operator std::string() const {
    return data;
  }
};

template<unsigned int N>
struct n_lines {
  static constexpr unsigned int num_lines = N;
  std::vector<std::string> data;

  operator std::string() const {
    return std::accumulate(data.begin(), data.end(), std::string(),
                           [](std::string acc, const std::string &s) {
                             return acc + "\n" + s;
                           });
  }
};

std::istream& operator>>(std::istream& stream, line& data) {
  std::getline(stream, data.data);
  return stream;
}

template<unsigned int N>
std::istream& operator>>(std::istream& stream, n_lines<N>& data) {
  data.data.clear();
  std::string line;
  for (unsigned int i = 0; i < data.num_lines; ++i) {
    std::getline(stream, line);
    data.data.push_back(line);
  }
  return stream;
}

template <typename T>
std::vector<T> split(const std::string &str) {
  std::vector<T> strings;
  std::istringstream stream(str);
  T tmp;
  while (!stream.eof()) {
    stream >> tmp;
    strings.push_back(tmp);
  }
  return strings;
}

std::vector<std::string> split(const std::string &str, char delim) {
  std::istringstream input(str);
  std::vector<std::string> strings;
  for (std::string line; std::getline(input, line, delim);) {
    strings.push_back(line);
  }
  return strings;
}

template <typename InIter, typename OutIter, typename Fn>
void flatmap(InIter begin, InIter end, OutIter out, Fn fn) {
  for (; begin != end; ++begin) {
    auto y = fn(*begin);
    std::copy(std::begin(y), std::end(y), out);
  }
}
