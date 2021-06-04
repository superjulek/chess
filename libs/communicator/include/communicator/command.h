#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

struct Command {
  struct CommandOption {
    std::string name;
    std::string default_value;
    bool required;
  };
  std::string name;
  std::string description;
  std::vector<CommandOption> options;
  std::map<std::string, std::string> options_map;
  std::function<void(const Command &)> action;
  void parse_options(std::vector<std::string> split_cmd);
  std::string get_prompt() const;
};
