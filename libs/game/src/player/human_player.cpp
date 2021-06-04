#include "player/human_player.h"

Move HumanPlayer::get_move(const Board &board,
                           bool retry __attribute__((unused))) {
  // TODO: pass retry info to user
  return moving_fun(board);
}
