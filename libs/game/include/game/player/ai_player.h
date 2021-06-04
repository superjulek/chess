#pragma once

#include "i_player.h"

class AIPlayer : public IPlayer {
private:
  Piece::PieceColor color;

public:
  inline AIPlayer(Piece::PieceColor color) : color(color) {}
  virtual Move get_move(const Board &board, bool retry);
  inline virtual Piece::PieceColor get_color() { return color; }
};
