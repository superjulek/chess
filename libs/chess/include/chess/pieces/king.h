#pragma once

#include "piece.h"

namespace Pieces {

class King : public Piece {
public:
  King(PieceColor color);
  virtual std::vector<PossibleMove>
  get_possible_moves(const Coordinates &coords) override;
};
} // namespace Pieces
