#include "channels/console_logger.h"

#include <iostream>

ConsoleLogger::ConsoleLogger(Severity min, Severity max)
    : ILoggerChannel(min, max) {}

void ConsoleLogger::write(const ILoggerChannel::Message &mes) {
  std::cout << mes.sev << std::string(": ") << mes.text << std::endl;
}
