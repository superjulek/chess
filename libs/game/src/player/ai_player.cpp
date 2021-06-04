#include "player/ai_player.h"
#include <engine/engine.h>

Move AIPlayer::get_move(const Board &board, bool retry)
{
  if (!retry)
  {
    return Engine::get_instance().get_move(board);
  }

  throw std::logic_error("Bad AI computation");
}
