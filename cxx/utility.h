#pragma once
#include <string>

struct line {
  std::string data;

  operator std::string() const {
    return data;
  }
};

std::istream& operator>>(std::istream& str, line& data) {
  std::getline(str, data.data);
  return str;
}
