#include "config.h"

#include <controller/controller.h>
#include <logger/channels/console_logger.h>
#include <logger/channels/file_logger.h>
#include <logger/logger.h>
#include <runner/runner.h>

int main() {
  Runner main_runner;
  main_runner.run();
  return 0;
}
