#pragma once
#pragma once

#include "i_logger_channel.h"

#include <filesystem>

class FileLogger : public ILoggerChannel {
public:
  FileLogger(Severity min, Severity max,
             const std::filesystem::path &logfile_path);
  void write(const ILoggerChannel::Message &mes) override;

private:
  std::filesystem::path logfile_path;
};
