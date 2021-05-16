#pragma once

#include <iostream>
#include <map>

struct Coordinates {
  int file;
  int rank;

  static const std::map<int, char> file_map;
  static const std::map<int, char> rank_map;
  static const std::map<char, int> file_map_rev;
  static const std::map<char, int> rank_map_rev;

  Coordinates() = default;
  Coordinates(char file_ch, char rank_ch);
  inline Coordinates(int file_int, int rank_int)
      : file(file_int), rank(rank_int){};
  inline bool operator==(const Coordinates &other) const {
    return this->file == other.file && this->rank == other.rank;
  }
};

std::ostream &operator<<(std::ostream &os, const Coordinates &coords);
