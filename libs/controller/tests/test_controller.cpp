#include <controller/controller.h>

#include <view/viewers/console_viewer.h>

#include <gtest/gtest.h>

#include <iostream>

// Loader

TEST(ControllerTests, DummyTest) {
  Controller my_controller = Controller(std::make_unique<ConsoleViewer>());

  my_controller.start_game(
      std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  my_controller.display_board();
}
