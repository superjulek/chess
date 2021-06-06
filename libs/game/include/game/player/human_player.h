#pragma once

#include "i_player.h"

class HumanPlayer : public IPlayer {
private:
  Piece::PieceColor color;
  std::string name;
  // Callback invoked for making a move
  std::function<Move(const Board &, std::string name, bool retry)> moving_fun;

public:
  inline HumanPlayer(
      Piece::PieceColor color, const std::string &name,
      std::function<Move(const Board &, const std::string &name, bool retry)>
          mov_fun)
      : IPlayer(name), color(color), name(name), moving_fun(mov_fun) {}
  Move get_move(const Board &board, bool retry);
  inline virtual Piece::PieceColor get_color() { return color; }
};
