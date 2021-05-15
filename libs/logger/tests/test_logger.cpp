#include <logger/channels/console_logger.h>
#include <logger/channels/file_logger.h>
#include <logger/logger.h>

#include <gtest/gtest.h>

#include <fstream>

TEST(ConsoleLoggerTests, CreateLogger) {
  Logger::get_instance().register_channel(std::make_unique<ConsoleLogger>(
      ConsoleLogger(LogSev::Debug, LogSev::Error)));
  ASSERT_TRUE(true);
  Logger::get_instance().flush_channels();
}

TEST(ConsoleLoggerTests, WriteLogger) {
  std::ostringstream local;
  std::string testing_text = "Testing Log";
  std::string expected_text = "DEBUG: " + testing_text + "\n";

  auto *cout_buff = std::cout.rdbuf();
  std::cout.rdbuf(local.rdbuf());

  Logger::get_instance().register_channel(std::make_unique<ConsoleLogger>(
      ConsoleLogger(LogSev::Debug, LogSev::Error)));
  Logger::get_instance().log(LogSev::Debug, testing_text);
  ASSERT_STREQ(local.str().c_str(), expected_text.c_str());
  Logger::get_instance().flush_channels();
  std::cout.rdbuf(cout_buff);
}

TEST(FileLoggerTests, CreateLogger) {
  Logger::get_instance().register_channel(std::make_unique<FileLogger>(
      FileLogger(LogSev::Debug, LogSev::Error, "testlog.txt")));
  ASSERT_TRUE(true);
  Logger::get_instance().flush_channels();
}

TEST(FileLoggerTests, WriteLogger) {
  std::string testing_text = "Testing Log";
  std::string expected_text = "DEBUG: " + testing_text;
  std::string testing_path = "testlogfile.txt";
  std::string log_read;

  remove(testing_path.c_str());

  Logger::get_instance().register_channel(std::make_unique<FileLogger>(
      FileLogger(LogSev::Debug, LogSev::Error, testing_path)));
  Logger::get_instance().log(LogSev::Debug, testing_text);

  std::ifstream ReadFile(testing_path);
  std::getline(ReadFile, log_read);
  ASSERT_STREQ(log_read.c_str(), expected_text.c_str());
  Logger::get_instance().flush_channels();

  remove(testing_path.c_str());
}

TEST(FileLoggerTests, WriteLoggerSubdir) {
  std::string testing_text = "Testing Log";
  std::string expected_text = "DEBUG: " + testing_text;
  std::string testing_path = "test/testlogfile.txt";
  std::string log_read;

  remove(testing_path.c_str());

  Logger::get_instance().register_channel(std::make_unique<FileLogger>(
      FileLogger(LogSev::Debug, LogSev::Error, testing_path)));
  Logger::get_instance().log(LogSev::Debug, testing_text);

  std::ifstream ReadFile(testing_path);
  std::getline(ReadFile, log_read);
  ASSERT_STREQ(log_read.c_str(), expected_text.c_str());
  Logger::get_instance().flush_channels();

  remove(testing_path.c_str());
}
