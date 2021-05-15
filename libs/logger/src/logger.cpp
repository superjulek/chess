#include "logger.h"

Logger &Logger::get_instance() {
  static Logger instance;
  return instance;
}

void Logger::register_channel(std::unique_ptr<ILoggerChannel> channel) {
  channels.push_back(std::move(channel));
}

void Logger::log(const ILoggerChannel::Message &mes) {
  for (const auto &logger : channels) {
    ILoggerChannel::Severity min_sev = logger->get_sev_min();
    ILoggerChannel::Severity max_sev = logger->get_sev_max();
    if (mes.sev >= min_sev && mes.sev <= max_sev) {
      logger->write(mes);
    }
  }
}

void Logger::log(ILoggerChannel::Severity sev, const std::string &text)
{
  this->log({sev, text});
}

void Logger::flush_channels()
{
  channels.clear();
}
