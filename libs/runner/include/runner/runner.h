#pragma once

#include <communicator/communicator.h>
#include <controller/controller.h>

class Runner {
private:
  void register_logger();
  Communicator get_start_communicator();
  Communicator get_preview_communicator();
  Communicator get_gaming_communicator(Game::GameState state);
  std::function<Move(const Board &board, const std::string &name, bool retry)>
  get_user_prompting_fun();
  Controller controller;

public:
  Runner();
  void run();
};