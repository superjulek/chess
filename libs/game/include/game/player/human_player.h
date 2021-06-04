#pragma once

#include "i_player.h"

class HumanPlayer : public IPlayer {
private:
  // Callback invoked for making a move
  std::function<void(const Board &)> moving_fun;

public:
  inline HumanPlayer(std::function<void(const Board &)> mov_fun)
      : moving_fun(mov_fun) {}
  Move get_move(const Board &board);
};
