#pragma once

#include "piece.h"

namespace Pieces {

class Rook : public virtual Piece {
public:
  Rook(PieceColor color);
  virtual std::vector<PossibleMove>
  get_possible_moves(const Coordinates &coords) override;
  std::unique_ptr<Piece> clone() override;
};
} // namespace Pieces
