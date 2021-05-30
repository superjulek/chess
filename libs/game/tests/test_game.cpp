#include <game/game.h>
#include <game/player/ai_player.h>

#include <gtest/gtest.h>

#include <iostream>

// Game

TEST(GamaTests, DepthPreviewTest) {
  Game game = Game(std::make_unique<AIPlayer>(Piece::PieceColor::White),
                   std::make_unique<AIPlayer>(Piece::PieceColor::Black));
  Board::BoardLayout layout0 = game.get_board_layout();

  ASSERT_EQ(game.get_max_depth(), 0);
  ASSERT_EQ(game.get_current_depth(), 0);

  game.make_move(Move{{'a', '2'}, {'a', '3'}});
  Board::BoardLayout layout1 = game.get_board_layout();

  ASSERT_EQ(game.get_max_depth(), 1);
  ASSERT_EQ(game.get_current_depth(), 0);

  game.make_move(Move{{'b', '7'}, {'b', '5'}});
  Board::BoardLayout layout2 = game.get_board_layout();

  ASSERT_EQ(game.get_max_depth(), 2);
  ASSERT_EQ(game.get_current_depth(), 0);

  game.enter_preview();
  game.step_back(2);
  Board::BoardLayout layout3 = game.get_board_layout();

  ASSERT_EQ(game.get_max_depth(), 2);
  ASSERT_EQ(game.get_current_depth(), 2);
  ASSERT_EQ(layout0, layout3);

  game.step_forward(1);
  Board::BoardLayout layout4 = game.get_board_layout();

  ASSERT_EQ(game.get_max_depth(), 2);
  ASSERT_EQ(game.get_current_depth(), 1);
  ASSERT_EQ(layout1, layout4);

  game.leave_preview();
  Board::BoardLayout layout5 = game.get_board_layout();

  ASSERT_EQ(game.get_max_depth(), 2);
  ASSERT_EQ(game.get_current_depth(), 0);
  ASSERT_EQ(layout2, layout5);
}
