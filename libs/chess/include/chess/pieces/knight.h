#pragma once

#include "piece.h"

namespace Pieces {

class Knight : public Piece {
public:
  Knight(PieceColor color);
  virtual std::vector<PossibleMove>
  get_possible_moves(const Coordinates &coords) override;
  const static std::array<std::pair<int, int>, 8> knight_moves;
};
} // namespace Pieces
