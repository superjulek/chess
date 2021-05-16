#include "pieces/empty.h"

using namespace Pieces;

Empty::Empty()
    : Piece(PieceColor::White, PieceID::Empty) {} // Don't care about color

std::vector<PossibleMove> Empty::get_possible_moves(const Coordinates &coords
                                                    __attribute__((unused))) {
  std::vector<PossibleMove> possible_moves;
  return possible_moves;
}
