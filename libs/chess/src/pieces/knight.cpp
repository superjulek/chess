#include "pieces/knight.h"

using namespace Pieces;

const std::array<std::pair<int, int>, 8> Knight::knight_moves = {
    std::make_pair(1, 2),   std::make_pair(1, -2), std::make_pair(-1, 2),
    std::make_pair(-1, -2), std::make_pair(2, 1),  std::make_pair(2, -1),
    std::make_pair(-2, 1),  std::make_pair(-2, -1)};

Knight::Knight(PieceColor color) : Piece(color, PieceID::Knight) {}

std::vector<PossibleMove>
Knight::get_possible_moves(const Coordinates &coords) {

  std::vector<PossibleMove> possible_moves;

  for (const auto &m : Knight::knight_moves) {
    if (coords.file + m.first >= 0 &&
        coords.file + m.first < static_cast<int>(chess_size) &&
        coords.rank + m.second >= 0 &&
        coords.rank + m.second < static_cast<int>(chess_size)) {
      PossibleMove move_knight;
      move_knight.from = coords;
      move_knight.to = {coords.file + m.first, coords.rank + m.second};
      possible_moves.push_back(move_knight);
    }
  }
  return possible_moves;
}

std::unique_ptr<Piece> Knight::clone()
{
  return std::make_unique<Knight> (*this);
}
