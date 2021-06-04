#include "command.h"

#include <stdexcept>

void Command::parse_options(std::vector<std::string> split_cmd) {
  for (const auto &opt : options) {
    bool found = false;
    for (int i = 0; i < (int)split_cmd.size(); ++i) {
      if (split_cmd.at(i) == opt.name) {
        if ((i + 1) < (int)split_cmd.size()) {
          options_map.insert({opt.name, split_cmd.at(i + 1)});
          found = true;
          break;
        }
        throw std::runtime_error("No value given for last option " + opt.name);
      }
    }
    if (!found) {
      if (!opt.required) {
        options_map.insert({opt.name, opt.default_value});
      } else {
        throw std::runtime_error("No value for required option " + opt.name);
      }
    }
  }
}

std::string Command::get_prompt() const {
  std::string ret = "\t\"" + name + "\" : " + description + "\n";
  for (const auto &opt : options) {
    ret += "\t\t" + opt.name;
    if (opt.required) {
      ret += " required\n";
    } else {
      ret += " default: " + opt.default_value + "\n";
    }
  }
  return ret;
}
