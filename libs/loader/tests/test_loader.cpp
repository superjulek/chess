#include <loader/loader.h>

#include <gtest/gtest.h>

#include <iostream>

// Loader

TEST(LoaderTests, TestStartingGame) {
  Loader my_loader;
  Board start_board;
  my_loader.create_new_game(
      std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  ASSERT_EQ(my_loader.get_game_ptr()->get_board_layout(),
            start_board.get_layout());
  ASSERT_EQ(my_loader.get_game_ptr()->get_current_player_color(),
            Piece::PieceColor::White);
  ASSERT_EQ(my_loader.get_game_ptr()->get_state(), Game::GameState::Normal);
}

TEST(LoaderTests, DropGame) {
  Loader my_loader;
  my_loader.create_new_game(
      std::make_unique<AIPlayer>(Piece::PieceColor::White),
      std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  my_loader.drop_game();
  ASSERT_FALSE(my_loader.is_game_loaded());
}
