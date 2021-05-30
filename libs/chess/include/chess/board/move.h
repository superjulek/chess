#pragma once

#include "../pieces/piece.h"
#include "coordinates.h"

#include <vector>

struct Move {
  Coordinates from;
  Coordinates to;
};

struct PossibleMove : public Move {
  struct Constrain {
    enum class ConstrainType : int {
      Free,
      TakenByOpponent,
    };
    ConstrainType type;
    Coordinates coords;
  };
  std::vector<Constrain> constrains;
};

/* For keeping in history and replaying board back and forward */
struct StoredMove : public Move {
  // Piece::PieceColor moved_color;
  Piece::PieceID piece_captured;
};
