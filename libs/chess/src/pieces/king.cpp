#include "pieces/king.h"

using namespace Pieces;

King::King(PieceColor color) : Piece(color, PieceID::King) {}

std::vector<PossibleMove> King::get_possible_moves(const Coordinates &coords) {

  std::vector<PossibleMove> possible_moves;

  for (int rank_step = -1; rank_step <= 1; rank_step++) {
    for (int file_step = -1; file_step <= 1; file_step++) {
      if (coords.file + file_step < static_cast<int>(chess_size) &&
          coords.rank + rank_step < static_cast<int>(chess_size) &&
          coords.file + file_step >= 0 && coords.rank + rank_step >= 0) {
        if (file_step != 0 || rank_step != 0) {
          PossibleMove move_king;
          move_king.from = coords;
          move_king.to = {coords.file + file_step, coords.rank + rank_step};
          possible_moves.push_back(move_king);
        }
      }
    }
  }
  return possible_moves;
}
