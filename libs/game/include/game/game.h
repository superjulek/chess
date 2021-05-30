#pragma once

#include "player/i_player.h"

#include <chess/board/board.h>

#include <memory>
#include <vector>

class Game {
private:
  std::vector<StoredMove> past_moves;
  size_t current_depth;
  bool preview;
  std::unique_ptr<Board> board;
  std::unique_ptr<IPlayer> player_white;
  std::unique_ptr<IPlayer> player_black;

public:
  enum class GameState {
    Normal,
    Won,
    Pat,
  };
  Game(std::unique_ptr<IPlayer> white, std::unique_ptr<IPlayer> black);
  Board::BoardLayout get_board_layout();
  inline size_t get_max_depth() { return past_moves.size(); }
  inline size_t get_current_depth() { return current_depth; }
  void enter_preview();
  void leave_preview();
  void step_back(size_t steps);
  void step_forward(size_t steps);
  GameState get_state();
  void next_move();
  /* For testing */
  void make_move(Move move);
};
