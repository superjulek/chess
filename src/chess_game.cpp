#include "config.h"
#include <logger/channels/console_logger.h>
#include <logger/logger.h>

int main() {
  Logger::get_instance().register_channel(std::make_unique<ConsoleLogger>(
      ConsoleLogger(LogSev::Dbg, LogSev::Error)));
  Logger::get_instance().log(LogSev::Info, "Program launched");
  return 0;
}
