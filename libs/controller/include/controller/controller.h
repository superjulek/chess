#pragma once

#include <view/i_view.h>
#include <loader/loader.h>

#include <memory>

class Controller {
public:
  Controller(std::unique_ptr<IView> concrete_viewer);
  // Actions
  void display_board();
  void start_game(std::unique_ptr<IPlayer> white,
                  std::unique_ptr<IPlayer> black);
  void enter_preview();
  void leave_preview();
  // Queries for state
  void next_move();
  bool is_game_loaded();
  Game::GameState get_game_state();
  Piece::PieceColor get_current_player();
  bool is_preview();

private:
  Loader loader;
  std::unique_ptr<IView> viewer;
};
