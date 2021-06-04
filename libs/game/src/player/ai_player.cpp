#include "player/ai_player.h"
#include <engine/engine.h>


Move AIPlayer::get_move(const Board &board, bool retry __attribute__((unused))) {
  return Engine::get_instance().get_move(board);
}
