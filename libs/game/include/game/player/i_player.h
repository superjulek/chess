#pragma once

#include <chess/board/board.h>

#include <functional>
#include <string>

class IPlayer {
public:
  virtual Move get_move(const Board &board) = 0;
  virtual Piece::PieceColor get_color() = 0;
  virtual ~IPlayer() = default;
};
