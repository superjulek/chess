#pragma once

#include "bishop.h"
#include "piece.h"
#include "rook.h"

namespace Pieces {

class Queen : private Rook, private Bishop, virtual public Piece {
public:
  Queen(PieceColor color);
  virtual std::vector<PossibleMove>
  get_possible_moves(const Coordinates &coords) override;
};
} // namespace Pieces
