#include "loader.h"

void Loader::create_new_game(std::unique_ptr<IPlayer> white,
                             std::unique_ptr<IPlayer> black) {
  game.reset(new Game(std::move(white), std::move(black)));
}

void Loader::start_from_current_preview() {
  auto cloned = game->clone_current();
  game.reset();
  game = std::move(cloned);
}

void Loader::store_game_to_file(const std::string &path
                                __attribute__((unused))) {
  throw std::runtime_error("Saving game not implemented");
}

void Loader::load_game_from_file(const std::string &path
                                 __attribute__((unused))) {
  throw std::runtime_error("Saving game not implemented");
}

Game *Loader::get_game_ptr() {
  if (game) {
    return game.get();
  }
  throw std::runtime_error("Game not loaded");
}
