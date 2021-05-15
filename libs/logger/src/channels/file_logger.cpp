#include "channels/file_logger.h"

#include <fstream>

FileLogger::FileLogger(Severity min, Severity max,
                       const std::filesystem::path &logfile_path)
    : ILoggerChannel(min, max), logfile_path(logfile_path) {
  auto parent = logfile_path.parent_path();
  if (!parent.empty()) {
    std::filesystem::create_directories(parent);
  }
}

void FileLogger::write(const ILoggerChannel::Message &mes) {
  std::ofstream file;
  file.open(logfile_path, std::ios::app);
  file << mes.sev << std::string(": ") << mes.text << std::endl;
  file.close();
}
