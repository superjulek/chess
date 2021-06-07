#pragma once

#include "player/ai_player.h"
#include "player/human_player.h"
#include "player/i_player.h"
#include <chess/board/board.h>

#include <memory>
#include <vector>

#include "player/ai_player.h"
#include "player/human_player.h"
#include "player/i_player.h"

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
    Checkmate,
    Check,
    Pat,
  };
  Game(std::unique_ptr<IPlayer> white, std::unique_ptr<IPlayer> black);
  /* For testing mostly */
  Game(std::unique_ptr<IPlayer> white, std::unique_ptr<IPlayer> black,
       std::unique_ptr<Board> board);
  Board::BoardLayout get_board_layout();
  inline Piece::PieceColor get_current_player_color() {
    return board->get_current_player();
  }
  inline size_t get_max_depth() { return past_moves.size(); }
  inline size_t get_current_depth() { return current_depth; }
  void enter_preview();
  void leave_preview();
  inline bool is_preview() { return preview; }
  void step_back(size_t steps);
  void step_forward(size_t steps);
  GameState get_state();
  void next_move();
  std::string game_string();
  /* For testing */
  void make_move(Move move);
  std::unique_ptr<Game> clone_current(std::unique_ptr<IPlayer> white,
                  std::unique_ptr<IPlayer> black);
  inline std::vector<StoredMove> get_past_moves() { return past_moves; }
};
