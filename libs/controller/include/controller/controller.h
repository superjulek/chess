#pragma once

#include <loader/loader.h>
#include <view/i_view.h>

#include <memory>

class Controller {
public:
  Controller(std::unique_ptr<IView> concrete_viewer);
  // Actions
  void display_board();
  inline void display_text(const std::string &text) {
    viewer->display_text(text);
  };
  void start_game(std::unique_ptr<IPlayer> white,
                  std::unique_ptr<IPlayer> black);
  void enter_preview();
  void leave_preview();
  void abandon_game();
  void save_game(const std::string &path);
  void load_game(const std::string &path);
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
