#pragma once

#include "i_logger_channel.h"

class ConsoleLogger : public ILoggerChannel {
public:
  ConsoleLogger(Severity min, Severity max);
  void write(const ILoggerChannel::Message &mes) override;
};