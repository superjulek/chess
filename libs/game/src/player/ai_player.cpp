#include "player/ai_player.h"

Move AIPlayer::get_move(const Board &board __attribute__((unused))) {
  return Move{{'a', '1'}, {'a', '2'}};
}
