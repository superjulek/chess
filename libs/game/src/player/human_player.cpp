#include "player/human_player.h"

Move HumanPlayer::get_move(const Board &board,
                           bool retry){
  // TODO: pass retry info to user
  return moving_fun(board, this->player_name, retry);
}
