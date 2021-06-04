#include "config.h"

#include <controller/controller.h>
#include <logger/channels/console_logger.h>
#include <logger/channels/file_logger.h>
#include <logger/logger.h>

#include <chrono>
#include <ctime>

int main() {
  /* Register loggers */
  Logger::get_instance().register_channel(std::make_unique<ConsoleLogger>(
      ConsoleLogger(LogSev::Debug, LogSev::Error)));
  Logger::get_instance().register_channel(std::make_unique<FileLogger>(
      FileLogger(LogSev::Trace, LogSev::Fatal,
                 getenv("HOME") + std::string("/chesslogs/logs.log"))));
  std::time_t now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  Logger::get_instance().log(LogSev::Info,
                             std::string("Starting at ") + std::ctime(&now));
  Logger::get_instance().log(LogSev::Info, "Program launched");
  Logger::get_instance().log(LogSev::Info, "Program terminating");

  return 0;
}
