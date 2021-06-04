#include "controller.h"

#include <view/viewers/console_viewer.h>

Controller::Controller(std::unique_ptr<IView> concrete_viewer)
    : viewer(std::move(concrete_viewer)) {}

void Controller::start_game(std::unique_ptr<IPlayer> white,
                            std::unique_ptr<IPlayer> black) {
  loader.create_new_game(std::move(white), std::move(black));
}

void Controller::display_board() {
  viewer->display_board(loader.get_game_ptr()->get_board_layout());
}

bool Controller::is_game_loaded() { return loader.is_game_loaded(); }

Game::GameState Controller::get_game_state() {
  if (!is_game_loaded()) {
    throw std::runtime_error("Game not loaded");
  }
  return loader.get_game_ptr()->get_state();
}

Piece::PieceColor Controller::get_current_player() {
  if (!is_game_loaded()) {
    throw std::runtime_error("Game not loaded");
  }
  return loader.get_game_ptr()->get_current_player_color();
}

void Controller::enter_preview() {
  if (!is_game_loaded()) {
    throw std::runtime_error("Game not loaded");
  }
  loader.get_game_ptr()->enter_preview();
}

void Controller::leave_preview() {
  if (!is_game_loaded()) {
    throw std::runtime_error("Game not loaded");
  }
  loader.get_game_ptr()->leave_preview();
}

bool Controller::is_preview() {
  if (!is_game_loaded()) {
    throw std::runtime_error("Game not loaded");
  }
  return loader.get_game_ptr()->is_preview();
}

void Controller::next_move() {
  if (!is_game_loaded()) {
    throw std::runtime_error("Game not loaded");
  }
  loader.get_game_ptr()->next_move();
}

void Controller::abandon_game() {
  if (!is_game_loaded()) {
    throw std::runtime_error("Game not loaded");
  }
  loader.drop_game();
}

void Controller::save_game(const std::string &path) {
  if (!is_game_loaded()) {
    throw std::runtime_error("Game not loaded");
  }
  loader.store_game_to_file(path);
}
void Controller::load_game(const std::string &path) {
  if (is_game_loaded()) {
    throw std::runtime_error("Game already loaded, abandon first");
  }

  loader.load_game_from_file(path);
}
