#pragma once

#include <string>

class ILoggerChannel {
public:
  enum class Severity : int {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Fatal,
  };
  struct Message {
    Severity sev;
    std::string text;
  };
  virtual void write(const Message &mes) = 0;
  virtual ~ILoggerChannel() = default;

private:
  Severity sev_min;
  Severity sev_max;

public:
  inline ILoggerChannel(Severity min, Severity max)
      : sev_min(min), sev_max(max){};
  inline Severity get_sev_min() { return sev_min; }
  inline Severity get_sev_max() { return sev_max; }
};

inline std::ostream &operator<<(std::ostream &os,
                                const ILoggerChannel::Severity &sev) {
  switch (sev) {
  case ILoggerChannel::Severity::Trace:
    os << std::string("TRACE");
    break;
  case ILoggerChannel::Severity::Debug:
    os << std::string("DEBUG");
    break;
  case ILoggerChannel::Severity::Info:
    os << std::string("INFO");
    break;
  case ILoggerChannel::Severity::Warning:
    os << std::string("WARNING");
    break;
  case ILoggerChannel::Severity::Error:
    os << std::string("ERROR");
    break;
  case ILoggerChannel::Severity::Fatal:
    os << std::string("FATAL");
    break;
  default:
    os << std::string("WRONG_LEVEL ");
    break;
  }
  return os;
}
