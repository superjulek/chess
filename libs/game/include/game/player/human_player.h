#pragma once

#include "i_player.h"

class HumanPlayer : public IPlayer {
private:
  Piece::PieceColor color;
  std::string name;
  // Callback invoked for making a move
  std::function<Move(const Board &)> moving_fun;

public:
  inline HumanPlayer(Piece::PieceColor color, const std::string &name,
                     std::function<Move(const Board &)> mov_fun)
      : color(color), name(name), moving_fun(mov_fun) {}
  Move get_move(const Board &board, bool retry);
  inline virtual Piece::PieceColor get_color() { return color; }
};
