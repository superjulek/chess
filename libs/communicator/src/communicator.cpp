#include "communicator.h"

#include <algorithm>
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
  ret += std::accumulate(commands.begin(), commands.end(), std::string(""),
                         [](const std::string &s, const Command &cmd) {
                           return s + cmd.get_prompt();
                         });
  ret += "Type command (end with ;)\n$";
  return ret;
}

void Communicator::communicate() {

  try {
    std::string given_cmd;
    std::getline(std::cin, given_cmd, ';');
    std::cin.clear();
    auto words = split(given_cmd);
    auto cmd =
        std::find_if(commands.begin(), commands.end(), [&](const Command &com) {
          return com.name == words.at(0);
        });
    if (cmd != commands.end()) {
      cmd->parse_options(words);
      std::cout << "Running command " + cmd->name << std::endl;
      cmd->action(*cmd);
      return;
    }
    throw std::runtime_error("Command \"" + given_cmd + "\" not found");
  } catch (const std::exception &exc) {
    throw std::runtime_error(std::string("Running command failed: ") +
                             exc.what());
  }
}
