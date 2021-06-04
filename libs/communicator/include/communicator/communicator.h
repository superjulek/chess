#pragma once

#include "command.h"

class Communicator {
public:
  void communicate();
  void add_command(Command cmd);
  void flush_commands();
  std::string get_prompt();

private:
  std::vector<Command> commands;
};
