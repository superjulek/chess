#include "board/coordinates.h"

const std::map<int, char> Coordinates::file_map = {
    {0, 'a'}, {1, 'b'}, {2, 'c'}, // NOLINT
    {3, 'd'}, {4, 'e'}, {5, 'f'}, // NOLINT
    {6, 'g'}, {7, 'h'}};          // NOLINT
const std::map<int, char> Coordinates::rank_map = {
    {0, '1'}, {1, '2'}, {2, '3'}, // NOLINT
    {3, '4'}, {4, '5'}, {5, '6'}, // NOLINT
    {6, '7'}, {7, '8'}};          // NOLINT

const std::map<char, int> Coordinates::file_map_rev = {
    {'a', 0}, {'b', 1}, {'c', 2}, // NOLINT
    {'d', 3}, {'e', 4}, {'f', 5}, // NOLINT
    {'g', 6}, {'h', 7}};          // NOLINT
const std::map<char, int> Coordinates::rank_map_rev = {
    {'1', 0}, {'2', 1}, {'3', 2}, // NOLINT
    {'4', 3}, {'5', 4}, {'6', 5}, // NOLINT
    {'7', 6}, {'8', 7}};          // NOLINT

Coordinates::Coordinates(char file_ch, char rank_ch)
    : file(file_map_rev.at(file_ch)), rank(rank_map_rev.at(rank_ch)) {}

std::ostream &operator<<(std::ostream &os, const Coordinates &coords) {
  os << Coordinates::file_map.at(coords.file)
     << Coordinates::rank_map.at(coords.rank);
  return os;
}
