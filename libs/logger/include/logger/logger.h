#include "channels/i_logger_channel.h"

#include <memory>
#include <vector>

using LogSev = ILoggerChannel::Severity;
class Logger {
public:
  static Logger &get_instance();
  void register_channel(std::unique_ptr<ILoggerChannel> channel);
  void log(const ILoggerChannel::Message &mes);
  void log(ILoggerChannel::Severity sev, const std::string &text);
  void flush_channels();

private:
  std::vector<std::unique_ptr<ILoggerChannel>> channels;
  Logger() = default;
  ~Logger() = default;
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;
};
