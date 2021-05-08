#include <logger/channels/console_logger.h>
#include <logger/logger.h>

#include <gtest/gtest.h>

TEST(ConsoleLoggerTests, CreateLogger) {
  Logger::get_instance().register_channel(std::make_unique<ConsoleLogger>(
      ConsoleLogger(LogSev::Dbg, LogSev::Error)));
  ASSERT_TRUE(true);
  Logger::get_instance().flush_channels();
}

TEST(ConsoleLoggerTests, WriteLogger) {
  std::ostringstream local;
  std::string testing_text = "Testing Log";
  std::string expected_text = "DBG: " + testing_text + "\n";

  auto *cout_buff = std::cout.rdbuf();
  std::cout.rdbuf(local.rdbuf());

  Logger::get_instance().register_channel(std::make_unique<ConsoleLogger>(
      ConsoleLogger(LogSev::Dbg, LogSev::Error)));
  Logger::get_instance().log(LogSev::Dbg, testing_text);
  ASSERT_STREQ(local.str().c_str(), expected_text.c_str());
  Logger::get_instance().flush_channels();
  std::cout.rdbuf(cout_buff);
}
