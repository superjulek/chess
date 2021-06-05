#pragma once

#include <game/game.h>

#include <memory>

class Loader {
public:
  void create_new_game(std::unique_ptr<IPlayer> white,
                       std::unique_ptr<IPlayer> black);
  void store_game_to_file(const std::string &path);
  void load_game_from_file(const std::string &path, std::unique_ptr<IPlayer> white,
                       std::unique_ptr<IPlayer> black);
  void start_from_current_preview();
  Game *get_game_ptr();
  bool is_game_loaded();
  inline void drop_game() { game.reset(); }

private:
  std::unique_ptr<Game> game;
};
