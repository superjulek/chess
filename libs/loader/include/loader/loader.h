#pragma once

#include <game/game.h>

#include <memory>

class Loader {
public:
  void create_new_game(std::unique_ptr<IPlayer> white, std::unique_ptr<IPlayer> black);
  void store_game_to_file(const std::string &path);
  void load_game_from_file(const std::string &path);
  void start_from_current_preview();
  Game *get_game_ptr();

private:
  std::unique_ptr<Game> game;
};
