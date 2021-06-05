#include "loader.h"
#include <fstream>
#include <iostream>

void Loader::create_new_game(std::unique_ptr<IPlayer> white,
                             std::unique_ptr<IPlayer> black) {
  game.reset(new Game(std::move(white), std::move(black)));
}

void Loader::start_from_current_preview() {
  auto cloned = game->clone_current();
  game.reset();
  game = std::move(cloned);
}

void Loader::store_game_to_file(const std::string &path)
{
  std::ofstream myfile(path);
  std::string game_string = game->game_string();
  myfile << game_string;
  myfile.close();
}

void Loader::load_game_from_file(const std::string &path)
{
  std::ifstream myfile;
  myfile.open(path);
  std::string file_content;
  if(!myfile)
  {
    throw std::runtime_error("Unable to open file");
  }
  while(!myfile.eof())
  {
    myfile>>file_content;
  }
  std::vector<StoredMove> past_moves;
  while(file_content.size())
  {
    Move mv = move_from_string(file_content.substr(0, 4));
    past_moves.push_back({mv, Piece::PieceID::Empty});
    file_content.erase(0, 4);
  }
  game->set_past_moves(past_moves);
}

Game *Loader::get_game_ptr() {
  if (game) {
    return game.get();
  }
  throw std::runtime_error("Game not loaded");
}

bool Loader::is_game_loaded() { return (game != nullptr); }
