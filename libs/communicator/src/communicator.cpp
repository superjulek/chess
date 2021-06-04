#include "communicator.h"

#include <bits/stdc++.h>
#include <exception>
#include <iostream>

std::vector<std::string> split(std::string str) {
  std::istringstream ss(str);
  std::string word;
  std::vector<std::string> ret;
  while (ss >> word) {
    ret.push_back(word);
  }
  return ret;
}

void Communicator::add_command(Command cmd) { commands.push_back(cmd); }

void Communicator::flush_commands() { commands.clear(); }

std::string Communicator::get_prompt() {
  std::string ret = "Possible commands:\n";
  for (const auto &cmd : commands) {
    ret += cmd.get_prompt();
  }
  ret += "Type command (end with ;)\n$";
  return ret;
}

void Communicator::communicate() {

  try {
    std::string given_cmd;
    std::getline(std::cin, given_cmd, ';');
    std::cin.clear();
    auto words = split(given_cmd);
    for (auto &cmd : commands) {
      if (cmd.name == words.at(0)) {
        cmd.parse_options(words);
        std::cout << "Running command " + cmd.name << std::endl;
        cmd.action(cmd);
        return;
      }
    }
    throw std::runtime_error("Command \"" + given_cmd + "\" not found");
  } catch (const std::exception &exc) {
    throw std::runtime_error(std::string("Error running command: ") +
                             exc.what());
  }
}
