#include <controller/controller.h>

#include <view/viewers/console_viewer.h>

#include <gtest/gtest.h>

#include <iostream>

// Controller

TEST(ControllerTests, LoadedTest) {
  Controller my_controller = Controller(std::make_unique<ConsoleViewer>());

  ASSERT_FALSE(my_controller.is_game_loaded());
  my_controller.start_game(
      std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  ASSERT_TRUE(my_controller.is_game_loaded());
}

TEST(ControllerTests, StateTest) {
  Controller my_controller = Controller(std::make_unique<ConsoleViewer>());

  my_controller.start_game(
      std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  ASSERT_EQ(my_controller.get_game_state(), Game::GameState::Normal);
}

TEST(ControllerTests, PlayerTest) {
  Controller my_controller = Controller(std::make_unique<ConsoleViewer>());

  my_controller.start_game(
      std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  ASSERT_EQ(my_controller.get_current_player(), Piece::PieceColor::White);
}

TEST(ControllerTests, PreviewTest) {
  Controller my_controller = Controller(std::make_unique<ConsoleViewer>());

  my_controller.start_game(
      std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  ASSERT_FALSE(my_controller.is_preview());
  my_controller.enter_preview();
  ASSERT_TRUE(my_controller.is_preview());
}
