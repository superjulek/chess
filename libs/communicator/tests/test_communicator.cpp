#include <communicator/communicator.h>

#include <gtest/gtest.h>

#include <iostream>

// Coordinates

TEST(CommunicatorTests, EmptyCom) {
  Communicator my_com;
  const std::string expected =
      "Possible commands:\nType command (end with ;)\n$";
  ASSERT_EQ(my_com.get_prompt(), expected);
}

TEST(CommunicatorTests, ExmCom) {
  Communicator my_com;
  my_com.add_command({
      .name = "TestCommand",
      .description = "Test Description",
      .options = {{
          .name = "-option",
          .default_value = "def",
          .required = true,
      }},
      .options_map = {},
      .action = [&](const Command &cmd __attribute__((unused))) {},
  });
  const std::string expected =
      "Possible commands:\n\t\"TestCommand\" : Test Description\n\t\t-option "
      "required\nType command (end with ;)\n$";
  ASSERT_EQ(my_com.get_prompt(), expected);
}

TEST(CommunicatorTests, TestAction) {

  bool test = false;
  Command com = {
      .name = "TestCommand",
      .description = "Test Description",
      .options = {{
          .name = "-option",
          .default_value = "def",
          .required = true,
      }},
      .options_map = {},
      .action = [&](const Command &cmd
                    __attribute__((unused))) { test = true; },
  };
  com.action(com);
  ASSERT_TRUE(test);
}
